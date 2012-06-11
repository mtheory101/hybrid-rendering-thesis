#include <optix/optix.h>
#include <optix/optix_math.h>
rtDeclareVariable(float3,          background_light, , ); // horizon color
rtDeclareVariable(float3,          background_dark, , );  // zenith color
rtDeclareVariable(float3,          up, , );               // global up vector
rtDeclareVariable(optix::Ray, ray, rtCurrentRay, );

struct PerRayData_radiance
{
  float3 result;
  float importance;
  int depth;
};

rtDeclareVariable(PerRayData_radiance, prd_radiance, rtPayload, );

RT_PROGRAM void miss()
{
	const float t = max(dot(ray.direction,up), 0.0f);
	prd_radiance.result = lerp(background_light, background_dark,t);
}
