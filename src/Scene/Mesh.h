#pragma once

#include "SceneNode.h"

#include "../Render/VAO.h"
#include "../Render/VBO.h"
#include "../Render/IBO.h"

#include <glm/glm.hpp>
#include <memory>

namespace Scene
{
	class Mesh;
	typedef std::shared_ptr<Mesh> MeshPtr;

	class Mesh : public SceneNode
	{
	public:
		Mesh( const Mesh &copy );

		Mesh(const Render::VAOPtr &vao, const Render::VBOPtr &vbo, const Render::IBOPtr &ibo);
		
		Mesh::Mesh(const std::vector<glm::vec3> &vertices, 
	       const std::vector<glm::vec3> &normals, 
	       const std::vector<glm::vec2> &tex_coords, 
		   const std::vector<unsigned int> &indices);

		void render(const Render::ShaderPtr &active_program) override;
	
		Render::VAOPtr getVao() { return vao; }
		Render::VBOPtr getVbo() { return vbo; }
		Render::IBOPtr getIbo() { return ibo; }
	protected:
		
		Render::VAOPtr vao;
		Render::VBOPtr vbo;
		Render::IBOPtr ibo;
	};
}