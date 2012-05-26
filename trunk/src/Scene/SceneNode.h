#pragma once

#include "../Render/Uniform.h"
#include "../Render/Sampler.h"
#include "../Render/Tex2D.h"
#include "../Render/Tex2DArray.h"
#include "../Render/Material.h"
#include "../Render/Shader.h"

#include <glm/glm.hpp>

#include <memory>

namespace Scene
{
	class SceneNode;
	typedef std::shared_ptr<SceneNode> SceneNodePtr;

	class SceneNode
	{
	public:
		SceneNode();

		virtual void render(const Render::ShaderPtr &active_program) = 0;

		void setMVP(const Render::UniformPtr &mvp) { this->mvp = mvp; }
		void setMV(const Render::UniformPtr &mv) { this->mv = mv; }
		void setN_WRI(const Render::UniformPtr &n_wri) { this->n_wri = n_wri; }

		void setModelMatrix(const glm::mat4 &model) { this->model = model; }
		virtual void setPosition(const glm::vec3 &position) { this->position = position; }

		void setTexture(const Render::Tex2DPtr &tex, const Render::UniformPtr &uniform, const Render::SamplerPtr &sampler);
		void setTexture(const Render::Tex2DArrayPtr &tex_array, const Render::UniformPtr &uniform, const Render::SamplerPtr &sampler);
		void setMaterial(const Render::MaterialPtr &material) { this->material = material; }

	protected:
		Render::UniformPtr mvp;
		Render::UniformPtr mv;
		Render::UniformPtr n_wri;

		Render::Tex2DPtr tex;
		Render::Tex2DArrayPtr tex_array;
		Render::UniformPtr tex_uniform;
		Render::SamplerPtr tex_sampler;

		Render::MaterialPtr material;

		glm::mat4 model;
		glm::vec3 position; // TODO remove position, now that we have a mat4?
	};
}
