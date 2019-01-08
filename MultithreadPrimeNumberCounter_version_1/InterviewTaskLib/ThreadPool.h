#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
#include <thread>

class ThreadPool
{
private:
	size_t m_threadCount;
	std::queue<std::function<void()>> m_Tasker;

	std::vector<std::thread> m_Threads;
	std::condition_variable m_EventVar;
	std::mutex m_EventMtx;
	bool m_Stopping = false;

	void Start(const size_t & threadCount);

public:
	explicit ThreadPool(size_t threadCount);
	~ThreadPool();
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool operator=(const ThreadPool &) = delete;

	void Post(std::function<void()> && task);
	void Destroy() noexcept;
};

