#pragma once
#include <Resources/IResource.hpp>
#include <unordered_map>
#include <iostream>

namespace Resources
{
	class ResourceManager
	{
	private:
		std::unordered_map<std::string, IResource*> mResourceMap;

	public:
		static ResourceManager* GetInstance()
		{
			static ResourceManager* singleton = nullptr;
			if (singleton == nullptr)
				singleton = new ResourceManager{};
			return singleton;
		}

		template<typename T>
		T* Create(const std::string rsrcName, const char* path)
		{
			T* rsc = new T(path);
			mResourceMap[rsrcName] = (IResource*)rsc;
			return rsc;
		}

		template<typename T>
		T* Create(const std::string rsrcName, T* rsrcPtr)
		{
			mResourceMap[rsrcName] = (IResource*)rsrcPtr;
			return rsrcPtr;
		}

		template<typename T>
		T* Get(const std::string rsrcName)
		{
			IResource* rsrc = mResourceMap[rsrcName];
			if (rsrc)
				return reinterpret_cast<T*>(rsrc);
			else
				return nullptr;
		}

		void LoadResource()
		{
			for (auto it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
			{
				it->second->LoadData();
				it->second->OpenGLInit();
				it->second->State = Resources::ResourceState::RS_INIT;
			}
		}

		int Size() { return mResourceMap.size(); }

		void Delete(const std::string rsrcName);

		void Clear();

	private:
		ResourceManager() {};
	};
}