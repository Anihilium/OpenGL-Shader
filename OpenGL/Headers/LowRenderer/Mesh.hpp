#pragma once
#include <LowRenderer/Camera.hpp>
#include <Resources/Model.hpp>
#include <Maths/Vec2.hpp>
#include <Maths/Vec3.hpp>
#include <Maths/Vec4.hpp>
#include <Maths/Mat4.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <LowRenderer/Light.hpp>
#include <string>
#include <Resources/Texture.hpp>

using namespace Core::Maths;

namespace LowRenderer
{
	class Mesh
	{
	public:
		Mat4 ModelMatrix;
		Mat4 MVPmat;
		float HeightScale;
		float MinLayers;
		float MaxLayers;
		int* mShaderProgram;

	private:
		Resources::Texture* mTexture;
		Resources::Texture* mNormalMap;
		Resources::Texture* mHeightMap;
		Resources::Model* mModel;

	public:
		Mesh(Resources::Model* model = nullptr, int* shaderProgram = nullptr, Resources::Texture* texture = nullptr, Resources::Texture* normalMap = nullptr, Resources::Texture* heightMap = nullptr, float heightScale = 0.05f, float minLayers = 256.f, float maxLayers = 512.f);
		void Draw(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights, bool isOutLine, Vec4 colorOutLine);

	private:
		void SetBool(const char* name, bool value);
		void SetInt(const char* name, int value);
		void SetFloat(const char* name, float value);
		void SetVec2(const char* name, const Vec2& value);
		void SetVec3(const char* name, const Vec3& value);
		void SetVec4(const char* name, const Vec4& value);
		void SetMat4(const char* name, const Mat4& mat);
	};
}