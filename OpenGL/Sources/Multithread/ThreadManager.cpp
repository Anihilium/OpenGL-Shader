#include <Multithread/ThreadManager.hpp>

namespace Multithread
{
	void ThreadManager::Init()
	{
		mStop = false;
		for (int i = 0; i < 5; ++i)
			mThreadPool.push_back(std::thread(&ThreadManager::TaskLoop, this));
	}

	void ThreadManager::Destroy()
	{
		mStop = true;
		for (std::thread& thread : mThreadPool)
			thread.join();
		mThreadPool.clear();
	}

	void ThreadManager::TaskLoop()
	{
		while (!mStop)
		{
			if (!RsrcToLoadQueue.empty() && mIsLoadingQueueAvailable.load() == 0)
			{
				int tmpAccessValue = ++mIsLoadingQueueAvailable;
				if (tmpAccessValue == 1)
				{
					if (RsrcToLoadQueue.empty())
						continue;

					Resources::IResource* rsrc = RsrcToLoadQueue.front();

					RsrcToLoadQueue.pop();

					mIsLoadingQueueAvailable.store(0);

					rsrc->State = Resources::ResourceState::RS_LOADING;
					rsrc->LoadData();
					rsrc->State = Resources::ResourceState::RS_LOADED;

					while(tmpAccessValue != 1){
						if (IsOpenGLListAvailable.load() == 0)
							tmpAccessValue = ++IsOpenGLListAvailable;
					}

					RsrcToInitList.push_back(rsrc);

					IsOpenGLListAvailable.store(0);
				}
			}
		}
	}
}