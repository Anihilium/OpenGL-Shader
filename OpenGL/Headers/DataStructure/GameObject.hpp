#pragma once
#include <LowRenderer/Mesh.hpp>
#include <Physics/Transform.hpp>
#include <Physics/Collider.hpp>

namespace DataStructure
{
	class GameObject
	{
	public:
		Physics::Transform Transform;
		LowRenderer::Mesh Mesh;
		Physics::Collider* Collider;
		Vec3 Velocity;

	public:
		GameObject(const Physics::Transform& transform = Physics::Transform(), const LowRenderer::Mesh& mesh = LowRenderer::Mesh(), Physics::Collider* col = nullptr);
	};
}