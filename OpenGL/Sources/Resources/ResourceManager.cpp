#include <Resources/ResourceManager.hpp>

namespace Resources
{
	void ResourceManager::Delete(const std::string rsrcName)
	{
		delete mResourceMap[rsrcName];
		mResourceMap.erase(rsrcName);
	}

	void ResourceManager::Clear()
	{
		if (mResourceMap.size() < 1)
			return;

		for (auto it = mResourceMap.begin(); it != mResourceMap.end(); ++it)
		{
			delete it->second;
		}
		mResourceMap.clear();
	}
}