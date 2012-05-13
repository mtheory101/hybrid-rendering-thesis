#pragma once

#include <GL3/gl3w.h>

#include <Eigen\Eigen>

#include <memory>
#include <vector>
#include <string>

namespace Render
{
	class Material;
	typedef std::shared_ptr<Material> MaterialPtr;
	
	struct MaterialParams
	{
		Eigen::Vector3f ambient, diffuse, specular;
		float phong_pow;
		float transparency;
		float index_of_refraction;
		MaterialParams(Eigen::Vector3f ambient, Eigen::Vector3f diffuse, Eigen::Vector3f specular, float phong_pow, float transparency, float index_of_refraction)
			: ambient(ambient), diffuse(diffuse), specular(specular), phong_pow(phong_pow), transparency(transparency), index_of_refraction(index_of_refraction)
		{}
	};

	class Material
	{
	public:
		Material(const MaterialParams &params);
		~Material();

		void bind();
		void unbind();

	private:
		Eigen::Vector3f ambient, diffuse, specular;
		float phong_pow;
		float transparency;
		float index_of_refraction;
	};
}
