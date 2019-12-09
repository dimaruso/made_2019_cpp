#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t _poolSize) :
	stop(false),
	poolSize(_poolSize)
{
	for (size_t i = 0; i < poolSize; ++i)
	threads.emplace_back
	(
		[this]
		{
			while (true)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(this->Lock);
					this->condition.wait(lock,
						[this] { return this->stop || !this->tasks.empty(); });
					if (this->stop && this->tasks.empty())
						return;
					task = std::move(this->tasks.front());
					this->tasks.pop();
				}
				task();
			}
		}
	);
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(Lock);
		stop = true;
		poolSize = 0;
	}
	condition.notify_all();
	for (std::thread &thread : threads)
		thread.join();
}