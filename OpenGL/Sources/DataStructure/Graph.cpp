#include <DataStructure\Graph.hpp>
#include <iostream>

namespace DataStructure
{
	void Graph::Destroy()
	{
		for (GameObject* obj : Objects)
		{
			if (obj->Collider)
				delete obj->Collider;
			delete obj;
		}
		Objects.clear();
		RootChildren.clear();
	}

	void UpdateNode(SceneNode& curNode, LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights, bool isOutLine, Vec4 colorOutLine)
	{
		Physics::Transform& transform = curNode.Object->Transform;
		curNode.LocalTransform = Mat4::CreateTransformationMatrix(transform.Position, transform.Scale, transform.Rotation);
		curNode.WorldTransform = curNode.Parent->WorldTransform * curNode.LocalTransform;
		curNode.Object->Mesh.ModelMatrix = curNode.WorldTransform;
		curNode.Object->Mesh.MVPmat = cam.ViewProjectionMatrix * curNode.WorldTransform;
		curNode.Object->Mesh.Draw(cam, dirLights, pointLights, spotLights, isOutLine, colorOutLine);
		for (SceneNode& node : curNode.Children)
			UpdateNode(node, cam, dirLights, pointLights, spotLights, isOutLine, colorOutLine);
	}

	void Graph::Update(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights, bool isOutLine, Vec4 colorOutLine)
	{
		for (SceneNode& node: RootChildren)
		{
			Physics::Transform& transform = node.Object->Transform;
			node.WorldTransform = Mat4::CreateTransformationMatrix(transform.Position, transform.Scale, transform.Rotation);
			node.Object->Mesh.ModelMatrix = node.WorldTransform;
			node.Object->Mesh.MVPmat = cam.ViewProjectionMatrix * node.WorldTransform;
			node.Object->Mesh.Draw(cam, dirLights, pointLights, spotLights, isOutLine, colorOutLine);
			for (SceneNode& child : node.Children)
				UpdateNode(child, cam, dirLights, pointLights, spotLights, isOutLine, colorOutLine);
		}
	}

	void Graph::Update(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights)
	{
		for (SceneNode& node : RootChildren)
		{
			Physics::Transform& transform = node.Object->Transform;
			node.WorldTransform = Mat4::CreateTransformationMatrix(transform.Position, transform.Scale, transform.Rotation);
			node.Object->Mesh.ModelMatrix = node.WorldTransform;
			node.Object->Mesh.MVPmat = cam.ViewProjectionMatrix * node.WorldTransform;
			node.Object->Mesh.Draw(cam, dirLights, pointLights, spotLights, false, Vec4(0));
			for (SceneNode& child : node.Children)
				UpdateNode(child, cam, dirLights, pointLights, spotLights, false, Vec4(0));
		}
	}
}
