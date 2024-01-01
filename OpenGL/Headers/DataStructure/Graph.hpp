#pragma once
#include <vector>
#include <Maths/Mat4.hpp>
#include <DataStructure/GameObject.hpp>
#include <LowRenderer/Light.hpp>
#include <LowRenderer/Camera.hpp>

namespace DataStructure
{
	struct SceneNode
	{
		GameObject* Object;
		Mat4 WorldTransform;
		Mat4 LocalTransform;
		SceneNode* Parent;
		std::vector<SceneNode> Children;
	};

	class Graph
	{
	public:
		std::vector<SceneNode> RootChildren;
		std::vector<GameObject*> Objects;

	public:
		void Destroy();
		void Update(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights);
		void Update(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights, bool isOutLine, Vec4 colorOutLine);
	};
}