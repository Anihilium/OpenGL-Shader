#include <DataStructure/GameObject.hpp>

namespace DataStructure
{
	GameObject::GameObject(const Physics::Transform& transform, const LowRenderer::Mesh& mesh, Physics::Collider* col) :
		Transform(transform), Mesh(mesh), Collider(col)
	{}
}