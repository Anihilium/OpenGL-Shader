#include <LowRenderer/Mesh.hpp>

namespace LowRenderer
{
	Mesh::Mesh(Resources::Model* model, int* shaderProgram, Resources::Texture* texture, Resources::Texture* normalMap, Resources::Texture* heightMap, float heightScale, float minLayers, float maxLayers) :
		mModel(model), mShaderProgram(shaderProgram), mTexture(texture), mNormalMap(normalMap), mHeightMap(heightMap), HeightScale(heightScale), MinLayers(minLayers), MaxLayers(maxLayers)
	{}
	
	void Mesh::Draw(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights, bool isOutLine,Vec4 colorOutLine)
	{
		if (!mTexture || mTexture->State != Resources::ResourceState::RS_INIT || !mModel || mModel->State != Resources::ResourceState::RS_INIT)
			return;

		for (Resources::Subobject& sub : mModel->mSubobjects)
		{
			glBindVertexArray(sub.VAO);
			glUseProgram(*mShaderProgram);

			if(mTexture)
				SetInt("tex", mTexture->texID);

			if (mNormalMap)
				SetInt("normalMap", mNormalMap->texID);

			if (mHeightMap)
			{
				SetInt("heightMap", mHeightMap->texID);
				SetFloat("heightScale", HeightScale);
				SetFloat("minLayers", MinLayers);
				SetFloat("maxLayers", MaxLayers);
			}

			SetMat4("mvp", MVPmat);
			SetMat4("model", ModelMatrix);

			SetVec3("viewPos", cam.Position);

			SetBool("isOutLine", isOutLine);
			SetVec4("outLineColor", colorOutLine);
			SetInt("dirLightInUse", dirLights.size());
			for (int i = 0; i < dirLights.size(); ++i)
			{
				std::string uniformName = "dirLights[";
				uniformName += std::to_string(i);
				SetVec4((uniformName + "].ambient").c_str(), dirLights[i].AmbientColor);
				SetVec4((uniformName + "].diffuse").c_str(), dirLights[i].DiffuseColor);
				SetVec4((uniformName + "].specular").c_str(), dirLights[i].SpecularColor);
				SetVec3((uniformName + "].direction").c_str(), dirLights[i].Direction);
			}

			SetInt("pointLightInUse", pointLights.size());
			for (int i = 0; i < pointLights.size(); ++i)
			{
				std::string uniformName = "pointLights[";
				uniformName += std::to_string(i);
				SetVec4((uniformName + "].ambient").c_str(), pointLights[i].AmbientColor);
				SetVec4((uniformName + "].diffuse").c_str(), pointLights[i].DiffuseColor);
				SetVec4((uniformName + "].specular").c_str(), pointLights[i].SpecularColor);
				SetVec3((uniformName + "].position").c_str(), pointLights[i].Position);
				SetFloat((uniformName + "].constant").c_str(), pointLights[i].AttenuationValues.x);
				SetFloat((uniformName + "].linear").c_str(), pointLights[i].AttenuationValues.y);
				SetFloat((uniformName + "].quadratic").c_str(), pointLights[i].AttenuationValues.z);
			}

			SetInt("spotLightInUse", spotLights.size());
			for (int i = 0; i < spotLights.size(); ++i)
			{
				std::string uniformName = "spotLights[";
				uniformName += std::to_string(i);
				SetVec4((uniformName + "].ambient").c_str(), spotLights[i].AmbientColor);
				SetVec4((uniformName + "].diffuse").c_str(), spotLights[i].DiffuseColor);
				SetVec4((uniformName + "].specular").c_str(), spotLights[i].SpecularColor);
				SetVec3((uniformName + "].position").c_str(), spotLights[i].Position);
				SetVec3((uniformName + "].direction").c_str(), spotLights[i].Direction);
				SetFloat((uniformName + "].constant").c_str(), spotLights[i].AttenuationValues.x);
				SetFloat((uniformName + "].linear").c_str(), spotLights[i].AttenuationValues.y);
				SetFloat((uniformName + "].quadratic").c_str(), spotLights[i].AttenuationValues.z);
				SetFloat((uniformName + "].innerCutOff").c_str(), spotLights[i].InnerCutOff);
				SetFloat((uniformName + "].outerCutOff").c_str(), spotLights[i].OuterCutOff);
			}
		
			glDrawElements(GL_TRIANGLES, (GLsizei)sub.IndexBuffer.size(), GL_UNSIGNED_INT, 0);
		}
	}

	void Mesh::SetBool(const char* name, bool value)
	{
		glUniform1i(glGetUniformLocation(*mShaderProgram, name), (int)value);
	}
	// ------------------------------------------------------------------------
	void Mesh::SetInt(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(*mShaderProgram, name), value);
	}
	// ------------------------------------------------------------------------
	void Mesh::SetFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(*mShaderProgram, name), value);
	}
	// ------------------------------------------------------------------------
	void Mesh::SetVec2(const char* name, const Vec2& value)
	{
		glUniform2fv(glGetUniformLocation(*mShaderProgram, name), 1, &value.x);
	}
	// ------------------------------------------------------------------------
	void Mesh::SetVec3(const char* name, const Vec3& value)
	{
		glUniform3fv(glGetUniformLocation(*mShaderProgram, name), 1, &value.x);
	}
	// ------------------------------------------------------------------------
	void Mesh::SetVec4(const char* name, const Vec4& value)
	{
		glUniform4fv(glGetUniformLocation(*mShaderProgram, name), 1, &value.x);
	}
	// ------------------------------------------------------------------------
	void Mesh::SetMat4(const char* name, const Mat4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(*mShaderProgram, name), 1, GL_TRUE, &mat.mat[0][0]);
	}
}