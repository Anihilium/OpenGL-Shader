#pragma once

namespace Resources
{
	enum class ResourceState
	{
		RS_NOT_LOADED,
		RS_LOADING,
		RS_LOADED,
		RS_INIT
	};

	class IResource
	{
	protected:
		const char* path;

	public:
		ResourceState State;

	public:
		virtual ~IResource() {};
		virtual void LoadData() = 0;
		virtual void OpenGLInit() = 0;
	};
}
