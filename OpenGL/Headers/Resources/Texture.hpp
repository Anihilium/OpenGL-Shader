#pragma once
#include <Resources/IResource.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Resources
{
	extern unsigned int ID;
	class Texture : public IResource
	{
	public:
		unsigned int texID;

	private:
		GLuint mTexture;
		GLuint mSampler;
		int width;
		int height;
		int nrChannels;
		int format;
		unsigned char* data;

	public:
		Texture(const char* path);
		~Texture();
		void LoadData() override;
		void OpenGLInit();
	};
}
