#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <Resources/IResource.hpp>
#include <Debug/Assertion.hpp>

namespace Resources
{
	class Shader : public IResource
	{
	private:
		int mVertexShader;
		int mFragmentShader;
		int* mShaderProgram;

		std::string mVertexShaderSource;
		std::string mFragmentShaderSource;

		int mSuccess;
		char mInfoLog[512];

	public:
		Shader(const char* path);
		~Shader() { delete mShaderProgram; };
		void LoadData() override;
		void OpenGLInit() override;
		bool SetVertexShader(const char* path);
		bool SetFragmentShader(const char* path);
		void CompileVertexShader();
		void CompileFragmentShader();
		bool Link();
		int* GetShaderProgram() { return mShaderProgram; }

	};
}