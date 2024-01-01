#include <Resources/Shader.hpp>

namespace Resources
{
	Shader::Shader(const char* p_path)
	{
		mVertexShader = glCreateShader(GL_VERTEX_SHADER);
		mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		mShaderProgram = new int;
		*mShaderProgram = glCreateProgram();
		path = p_path;
		State = ResourceState::RS_NOT_LOADED;
	}

	void Shader::LoadData()
	{
		std::string vertexPath(path), fragmentPath(path);
		int i;
		for (i = 0; path[i] != ':'; ++i)
			vertexPath[i] = path[i];
		vertexPath[i] = '\0';
		++i;
		int tmp = i;
		for (; path[i] != '\0'; ++i)
			fragmentPath[i - tmp] = path[i];
		fragmentPath[i - tmp] = '\0';
		SetVertexShader(vertexPath.c_str());
		SetFragmentShader(fragmentPath.c_str());
	}

	bool Shader::SetVertexShader(const char* path)
	{
		FILE* file;
		fopen_s(&file, path, "r");
		if (!file)
			return false;

		char curChar = fgetc(file);

		while (curChar != EOF)
		{
			mVertexShaderSource += curChar;
			curChar = fgetc(file);
		}

		fclose(file);

		return true;
	}
	
	bool Shader::SetFragmentShader(const char* path)
	{
		FILE* file;
		fopen_s(&file, path, "r");
		if (!file)
			return false;

		char curChar = fgetc(file);

		while (curChar != EOF)
		{
			mFragmentShaderSource += curChar;
			curChar = fgetc(file);
		}

		fclose(file);

		return true;
	}

	void Shader::CompileVertexShader()
	{
		const char* vtxSrc = mVertexShaderSource.c_str();

		glShaderSource(mVertexShader, 1, &vtxSrc, NULL);
		glCompileShader(mVertexShader);

		// check for shader compile errors
		glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &mSuccess);
		if (!mSuccess)
		{
			glGetShaderInfoLog(mVertexShader, 512, NULL, mInfoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << mInfoLog << std::endl;
		}
	}

	void Shader::CompileFragmentShader()
	{
		const char* fgmtSrc = mFragmentShaderSource.c_str();


		glShaderSource(mFragmentShader, 1, &fgmtSrc, NULL);
		glCompileShader(mFragmentShader);

		// check for shader compile errors
		glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &mSuccess);
		if (!mSuccess)
		{
			glGetShaderInfoLog(mFragmentShader, 512, NULL, mInfoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << mInfoLog << std::endl;
		}
	}

	void Shader::OpenGLInit()
	{
		CompileVertexShader();
		CompileFragmentShader();
		ASSERT(Link(), "Error while linking the shaders");
	}

	bool Shader::Link()
	{
		// link shaders
		glAttachShader(*mShaderProgram, mVertexShader);
		glAttachShader(*mShaderProgram, mFragmentShader);
		glLinkProgram(*mShaderProgram);

		// check for linking errors
		glGetProgramiv(*mShaderProgram, GL_LINK_STATUS, &mSuccess);
		if (!mSuccess) {
			glGetProgramInfoLog(*mShaderProgram, 512, NULL, mInfoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << mInfoLog << std::endl;
			return false;
		}
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragmentShader);

		return true;
	}
}