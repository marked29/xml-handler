#include "ThreadPool.h"

void ThreadPool::Start(const size_t &threadCount)
{
	for (size_t i = 0; i < threadCount; i++)
	{
		m_Threads.emplace_back([=]
		{
			while (true)
			{
				std::function<void()> Task;
				{
					std::unique_lock<std::mutex> lock{ m_EventMtx };
					m_EventVar.wait(lock, [=] {return m_Stopping || !m_Tasker.empty(); });
					if (m_Stopping && m_Tasker.empty())
						break;
					
					Task = std::move(m_Tasker.front());
					m_Tasker.pop();

				}
				Task();
			}
		});
	}
}

ThreadPool::ThreadPool(size_t threadCount)
{
	Start(threadCount);
}

ThreadPool::~ThreadPool()
{
	Destroy();
}

void ThreadPool::Post(std::function<void()>&& task)
{
	{
		std::unique_lock<std::mutex> lock{ m_EventMtx };
		m_Tasker.emplace(std::move(task));
	}
	m_EventVar.notify_one();
}

void ThreadPool::Destroy() noexcept
{
	{
		std::unique_lock<std::mutex> lock{ m_EventMtx };
		m_Stopping = true;
	}
	m_EventVar.notify_all();
	for (auto &thread : m_Threads)
	{
		thread.join();
	}
	m_Threads.clear();
}
