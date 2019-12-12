#pragma once
#include <future>
#include <mutex>
#include <functional>
#include <queue>

class ThreadPool 
{
public:
	explicit ThreadPool(size_t _poolSize);
	~ThreadPool();

	// pass arguments by value
	template<class Func, class... Args>
	auto exec(Func func, Args... args)->std::future<decltype(func(args...))>;
	
	const size_t size() const noexcept {return poolSize;}
private:
	size_t poolSize;
	std::mutex Lock;
	std::condition_variable condition;
	std::atomic<bool> stop;

	std::vector< std::thread > threads;
	std::queue< std::function<void()> > tasks;
};

template<class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args)-> std::future<decltype(func(args...))>
{
	using return_type = decltype( func(args...) );
	auto task = std::make_shared< std::packaged_task<return_type()> >
		( std::bind(func, args...) );
	std::future<return_type> future = task->get_future();
	{
		std::unique_lock<std::mutex> lock(Lock);
		if (stop)
			throw std::runtime_error("No available thread");
		tasks.emplace([task](){ (*task)(); });
	}
	condition.notify_one();
	return future;
}