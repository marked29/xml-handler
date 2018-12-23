#include "PrimeNumberCounter.h"

PrimeNumberCounter::PrimeNumberCounter(const std::vector<std::pair<int, int>>& intervals) : m_Intervals(intervals)
{
}

size_t PrimeNumberCounter::GetIntervalAmount() const
{
	return m_Intervals.size();
}

void PrimeNumberCounter::PrimeNumbers(std::pair<int, int>& intervals)
{
	int flag{ 0 };

	while (intervals.first < intervals.second)
	{
		flag = 0;
		for (int i = 2; i <= intervals.first / 2; ++i)
		{
			if (intervals.first % i == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			m_Mtx.lock();
			m_Result.insert(intervals.first);
			m_Mtx.unlock();
		}
		++intervals.first;
	}
}

std::set<int> PrimeNumberCounter::GetResult() const
{
	return m_Result;
}
