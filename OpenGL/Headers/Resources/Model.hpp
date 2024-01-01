#pragma once
#include <iostream>
#include <LowRenderer/Camera.hpp>
#include <LowRenderer/Light.hpp>
#include <Resources/Subobject.hpp>
#define DEBUG
#include <Debug/Assertion.hpp>

using namespace Core::Maths;

namespace Resources
{
	class Model : public IResource
	{
	public:
		std::vector<Subobject> mSubobjects;

	public:
		Model(const char* p_path = "");
		~Model();
		void Draw(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights);
		void LoadData() override;
		void OpenGLInit() override;
	};
}