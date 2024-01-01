#include <Resources/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>
#include <iostream>

namespace Resources
{
	static unsigned int ID = 1;

	Texture::Texture(const char* p_path)
	{
		path = p_path;
		State = ResourceState::RS_NOT_LOADED;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mTexture);

		glDeleteSamplers(1, &mSampler);
	}

	void Texture::LoadData()
	{
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(path, &width, &height, &nrChannels, 0);
	}

	void Texture::OpenGLInit()
	{
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);

		format = nrChannels == 3 ? GL_RGB : GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		glGenSamplers(1, &mSampler);
		glSamplerParameteri(mSampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(mSampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glSamplerParameteri(mSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(mSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameterf(mSampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

		GLint max = 0;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

		texID = ID;
		glBindTextureUnit(texID, mTexture);
		glBindSampler(texID, mSampler);
		++ID;
	}
}