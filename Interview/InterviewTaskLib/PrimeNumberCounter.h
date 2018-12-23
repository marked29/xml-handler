#pragma once
#include <iostream>
#include <mutex>
#include <vector>
#include <set>

class PrimeNumberCounter
{
private:
	std::set<int> m_Result;
	std::mutex m_Mtx;
	std::vector<std::pair<int, int>> m_Intervals;
public:
	explicit PrimeNumberCounter(const std::vector<std::pair<int, int>> & intervals);
	size_t GetIntervalAmount() const;
	void PrimeNumbers(std::pair<int, int> &intervals);
	std::set<int> GetResult() const;
};

