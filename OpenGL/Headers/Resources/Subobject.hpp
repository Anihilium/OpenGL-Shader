#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <Resources/IResource.hpp>
#include <Maths/Vec2.hpp>
#include <Maths/Vec3.hpp>

using namespace Core::Maths;

namespace Resources
{
	struct Vertex
	{
		Vec3 Position;
		Vec3 Normal;
		Vec2 TextureUV;
		Vec3 Tangent;
	};

	class Subobject
	{
	public:
		unsigned int VAO;
		std::vector<uint32_t> IndexBuffer;
		std::vector<Vertex> VertexBuffer;

	private:
		unsigned int mVBO, mEBO;

	public:
		Subobject();
		~Subobject();
		void SetBuffers();
	};
}