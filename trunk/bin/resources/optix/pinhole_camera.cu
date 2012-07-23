

#include <Optix/optix_world.h>
#include "helpers.h"

using namespace optix;

struct PerRayData_radiance
{
  float3 result;
  float  importance;
  int    depth;
};

struct PerRayData_shadow
{
  float attenuation;
};

rtDeclareVariable(float3,        eye, , );
rtDeclareVariable(float3,        U, , );
rtDeclareVariable(float3,        V, , );
rtDeclareVariable(float3,        W, , );
rtDeclareVariable(float3,        bad_color, , );
rtDeclareVariable(float,         scene_epsilon, , );

rtBuffer<uchar4, 2>   g_buffer_diffuse_read;
rtBuffer<float4, 2>   g_buffer_position_read;
rtBuffer<float4, 2>   g_buffer_normal_read;

rtBuffer<uchar4, 2>   g_buffer_diffuse_write;
rtBuffer<float4, 2>   g_buffer_position_write;
rtBuffer<float4, 2>   g_buffer_normal_write;

rtDeclareVariable(rtObject,      top_object, , );
rtDeclareVariable(unsigned int,  radiance_ray_type, , );

rtDeclareVariable(uint2, launch_index, rtLaunchIndex, );
rtDeclareVariable(uint2, launch_dim,   rtLaunchDim, );

RT_PROGRAM void pinhole_camera()
{
  float2 d = make_float2(launch_index) / make_float2(launch_dim) * 2.f - 1.f;
  float3 ray_origin = eye;
  float3 ray_direction = normalize(d.x*U + d.y*V + W);
  
  optix::Ray ray = optix::make_Ray(ray_origin, ray_direction, radiance_ray_type, scene_epsilon, RT_DEFAULT_MAX);

  PerRayData_radiance prd;
  prd.importance = 1.f;
  prd.depth = 0;

  rtTrace(top_object, ray, prd);

  // overwrite
  //g_buffer_diffuse[launch_index] = make_color( prd.result );

	//g_buffer_diffuse[launch_index].w = static_cast<unsigned char>(prd.result.x*255.f);
	//g_buffer_position[launch_index].w = prd.result.y;
  g_buffer_diffuse_write[launch_index].x = 0; //make_color( prd.result );//make_float3(0.f, 0.f, 1.f) );
  g_buffer_position_write[launch_index] = g_buffer_position_read[launch_index];
  g_buffer_normal_write[launch_index] = g_buffer_normal_read[launch_index];
}
