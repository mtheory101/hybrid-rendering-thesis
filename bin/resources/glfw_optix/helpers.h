
/*
 * Copyright (c) 2008 - 2010 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and proprietary
 * rights in and to this software, related documentation and any modifications thereto.
 * Any use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation is strictly
 * prohibited.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
 * AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
 * SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
 * BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
 * INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES
 */

#pragma once

#include <optixu/optixu_math_namespace.h>

// Convert a float3 in [0,1)^3 to a uchar4 in [0,255]^4 -- 4th channel is set to 255
#ifdef __CUDACC__
__device__ __inline__ optix::uchar4 make_color(const optix::float3& c)
{
    return optix::make_uchar4( static_cast<unsigned char>(__saturatef(c.z)*255.99f),  /* B */
                               static_cast<unsigned char>(__saturatef(c.y)*255.99f),  /* G */
                               static_cast<unsigned char>(__saturatef(c.x)*255.99f),  /* R */
                               255u);                                                 /* A */
}
#endif

// Sample Phong lobe relative to U, V, W frame
__host__ __device__ __inline__ optix::float3 sample_phong_lobe( optix::float2 sample, float exponent, 
                                                                optix::float3 U, optix::float3 V, optix::float3 W )
{
  const float power = expf( logf(sample.y)/(exponent+1.0f) );
  const float phi = sample.x * 2.0f * (float)M_PIf;
  const float scale = sqrtf(1.0f - power*power);
  
  const float x = cosf(phi)*scale;
  const float y = sinf(phi)*scale;
  const float z = power;

  return x*U + y*V + z*W;
}

// Sample Phong lobe relative to U, V, W frame
__host__ __device__ __inline__ optix::float3 sample_phong_lobe( const optix::float2 &sample, float exponent, 
                                                                const optix::float3 &U, const optix::float3 &V, const optix::float3 &W, 
                                                                float &pdf, float &bdf_val )
{
  const float cos_theta = powf(sample.y, 1.0f/(exponent+1.0f) );

  const float phi = sample.x * 2.0f * M_PIf;
  const float sin_theta = sqrtf(1.0f - cos_theta*cos_theta);
  
  const float x = cosf(phi)*sin_theta;
  const float y = sinf(phi)*sin_theta;
  const float z = cos_theta;

  const float powered_cos = powf( cos_theta, exponent );
  pdf = (exponent+1.0f) / (2.0f*M_PIf) * powered_cos;
  bdf_val = (exponent+2.0f) / (2.0f*M_PIf) * powered_cos;  

  return x*U + y*V + z*W;
}

// Get Phong lobe PDF for local frame
__host__ __device__ __inline__ float get_phong_lobe_pdf( float exponent, const optix::float3 &normal, const optix::float3 &dir_out, 
                                                         const optix::float3 &dir_in, float &bdf_val)
{  
  using namespace optix;

  float3 r = -reflect(dir_out, normal);
  const float cos_theta = fabs(dot(r, dir_in));
  const float powered_cos = powf(cos_theta, exponent );

  bdf_val = (exponent+2.0f) / (2.0f*M_PIf) * powered_cos;  
  return (exponent+1.0f) / (2.0f*M_PIf) * powered_cos;
}

// Create ONB from normal.  Resulting W is parallel to normal
__host__ __device__ __inline__ void create_onb( const optix::float3& n, optix::float3& U, optix::float3& V, optix::float3& W )
{
  using namespace optix;

  W = normalize( n );
  U = cross( W, optix::make_float3( 0.0f, 1.0f, 0.0f ) );

  if ( fabs( U.x ) < 0.001f && fabs( U.y ) < 0.001f && fabs( U.z ) < 0.001f  )
    U = cross( W, make_float3( 1.0f, 0.0f, 0.0f ) );

  U = normalize( U );
  V = cross( W, U );
}

// Create ONB from normalized vector
__device__ __inline__ void create_onb( const optix::float3& n, optix::float3& U, optix::float3& V)
{
  using namespace optix;

  U = cross( n, make_float3( 0.0f, 1.0f, 0.0f ) );

  if ( dot( U, U ) < 1e-3f )
    U = cross( n, make_float3( 1.0f, 0.0f, 0.0f ) );

  U = normalize( U );
  V = cross( n, U );
}

// Compute the origin ray differential for transfer
__host__ __device__ __inline__ optix::float3 differential_transfer_origin(optix::float3 dPdx, optix::float3 dDdx, float t, optix::float3 direction, optix::float3 normal)
{
  float dtdx = -optix::dot((dPdx + t*dDdx), normal)/optix::dot(direction, normal);
  return (dPdx + t*dDdx)+dtdx*direction;
}

// Compute the direction ray differential for a pinhole camera
__host__ __device__ __inline__ optix::float3 differential_generation_direction(optix::float3 d, optix::float3 basis)
{
  float dd = optix::dot(d,d);
  return (dd*basis-optix::dot(d,basis)*d)/(dd*sqrtf(dd));
}

// Compute the direction ray differential for reflection
__host__ __device__ __inline__ 
optix::float3 differential_reflect_direction(optix::float3 dPdx, optix::float3 dDdx, optix::float3 dNdP, 
                                             optix::float3 D, optix::float3 N)
{
  using namespace optix;

  float3 dNdx = dNdP*dPdx;
  float dDNdx = dot(dDdx,N) + dot(D,dNdx);
  return dDdx - 2*(dot(D,N)*dNdx + dDNdx*N);
}

// Compute the direction ray differential for refraction
__host__ __device__ __inline__ 
optix::float3 differential_refract_direction(optix::float3 dPdx, optix::float3 dDdx, optix::float3 dNdP, 
                                             optix::float3 D, optix::float3 N, float ior, optix::float3 T)
{
  using namespace optix;

  float eta;
  if(dot(D,N) > 0.f) {
    eta = ior;
    N = -N;
  } else {
    eta = 1.f / ior;
  }

  float3 dNdx = dNdP*dPdx;
  float mu = eta*dot(D,N)-dot(T,N);
  float TN = -sqrtf(1-eta*eta*(1-dot(D,N)*dot(D,N)));
  float dDNdx = dot(dDdx,N) + dot(D,dNdx);
  float dmudx = (eta - (eta*eta*dot(D,N))/TN)*dDNdx;
  return eta*dDdx - (mu*dNdx+dmudx*N);
}

// Color space conversions
__host__ __device__ __inline__ optix::float3 Yxy2XYZ( const optix::float3& Yxy )
{
  return optix::make_float3(  Yxy.y * ( Yxy.x / Yxy.z ),
                              Yxy.x,
                              ( 1.0f - Yxy.y - Yxy.z ) * ( Yxy.x / Yxy.z ) );
}

__host__ __device__ __inline__ optix::float3 XYZ2rgb( const optix::float3& xyz)
{
  const float R = optix::dot( xyz, optix::make_float3(  3.2410f, -1.5374f, -0.4986f ) );
  const float G = optix::dot( xyz, optix::make_float3( -0.9692f,  1.8760f,  0.0416f ) );
  const float B = optix::dot( xyz, optix::make_float3(  0.0556f, -0.2040f,  1.0570f ) );
  return optix::make_float3( R, G, B );
}

__host__ __device__ __inline__ optix::float3 Yxy2rgb( optix::float3 Yxy )
{
  using namespace optix;

  // First convert to xyz
  float3 xyz = make_float3( Yxy.y * ( Yxy.x / Yxy.z ),
                            Yxy.x,
                            ( 1.0f - Yxy.y - Yxy.z ) * ( Yxy.x / Yxy.z ) );

  const float R = dot( xyz, make_float3(  3.2410f, -1.5374f, -0.4986f ) );
  const float G = dot( xyz, make_float3( -0.9692f,  1.8760f,  0.0416f ) );
  const float B = dot( xyz, make_float3(  0.0556f, -0.2040f,  1.0570f ) );
  return make_float3( R, G, B );
}

__host__ __device__ __inline__ optix::float3 rgb2Yxy( optix::float3 rgb)
{
  using namespace optix;

  // convert to xyz
  const float X = dot( rgb, make_float3( 0.4124f, 0.3576f, 0.1805f ) );
  const float Y = dot( rgb, make_float3( 0.2126f, 0.7152f, 0.0722f ) );
  const float Z = dot( rgb, make_float3( 0.0193f, 0.1192f, 0.9505f ) );

  // convert xyz to Yxy
  return make_float3( Y, 
                      X / ( X + Y + Z ),
                      Y / ( X + Y + Z ) );
}

__host__ __device__ __inline__ optix::float3 tonemap( const optix::float3 &hdr_value, float Y_log_av, float Y_max)
{
  using namespace optix;

  float3 val_Yxy = rgb2Yxy( hdr_value );
  
  float Y        = val_Yxy.x; // Y channel is luminance
  const float a = 0.04f;
  float Y_rel = a * Y / Y_log_av;
  float mapped_Y = Y_rel * (1.0f + Y_rel / (Y_max * Y_max)) / (1.0f + Y_rel);

  float3 mapped_Yxy = make_float3( mapped_Y, val_Yxy.y, val_Yxy.z ); 
  float3 mapped_rgb = Yxy2rgb( mapped_Yxy ); 

  return mapped_rgb;
}

