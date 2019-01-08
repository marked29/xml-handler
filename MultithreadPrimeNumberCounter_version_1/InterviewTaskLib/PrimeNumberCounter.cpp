#include "PrimeNumberCounter.h"



void PrimeNumberCounter::CalcAndAccumulatePrimes(std::pair<int, int>& intervals)
{
	bool flag = false;
	if (intervals.first > intervals.second)
	{
		std::swap(intervals.first, intervals.second);
	}

	while (intervals.first < intervals.second)
	{
		flag = false;
		for (int i = 2; i <= intervals.first / 2; ++i)
		{
			if (intervals.first % i == 0 )
			{
				flag = true;
				break;
			}
		}
		if (flag == false && intervals.first != 0 && intervals.first != 1)
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
