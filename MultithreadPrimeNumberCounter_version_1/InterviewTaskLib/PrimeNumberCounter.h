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
public:
	PrimeNumberCounter() = default;
	void CalcAndAccumulatePrimes(std::pair<int, int> &intervals);
	std::set<int> GetResult() const;
};

