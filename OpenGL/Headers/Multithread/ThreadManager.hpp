#pragma once
#include <thread>
#include <queue>
#include <list>
#include <vector>
#include <cstdarg>
#include <atomic>
#include <Resources/IResource.hpp>

namespace Multithread
{
	class ThreadManager
	{
	private:
		std::vector<std::thread> mThreadPool;
		std::atomic<int> mIsLoadingQueueAvailable = 0;
		bool mStop = false;

	public:
		std::queue<Resources::IResource*> RsrcToLoadQueue;
		std::list<Resources::IResource*> RsrcToInitList;
		std::atomic<int> IsOpenGLListAvailable = 0;

	public:
		void Init();
		void Destroy();

	private:
		void TaskLoop();
	};
}