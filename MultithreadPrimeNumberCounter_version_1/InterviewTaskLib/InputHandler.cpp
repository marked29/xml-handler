#include "InputHandler.h"

std::vector<std::pair<int, int>> InputHandler::m_MergeInterval(std::vector<std::pair<int, int>>& intervals)
{
	if (intervals.empty())
	{
		throw std::exception("Vector is empty");
	}


	std::vector<std::pair<int, int>> result;
	sort(intervals.begin(), intervals.end());
	std::pair<int, int> current = intervals[0];

	for (auto & elem : intervals)
	{
		if (current.second > elem.first)
		{
			current.second = std::max(current.second, elem.second);
		}
		else
		{
			result.push_back(current);
			current = elem;
		}
	}
	result.push_back(current);
	return result;
}

void InputHandler::m_StructureFormer(const std::vector<std::string>& info)
{
	if (!(info.size() % 2 == 0))
	{
		throw std::exception("Couldn't be sliced into pairs");
	}
	if (info.empty())
	{
		throw std::exception("Empty input");
	}

	std::vector<std::pair<int, int>> IntervalContainer;
	IntervalContainer.reserve(info.size() / 2);
	for (size_t i = 0; i < info.size(); i += 2)
	{
		IntervalContainer.push_back({ stoi(info[i]), stoi(info[i + 1]) });
	}
	m_ResultIntervals = m_MergeInterval(IntervalContainer);
}

InputHandler::InputHandler(const std::string & input) : m_InputBuffer(input)
{
}

void InputHandler::ParseInput()
{
	if (m_InputBuffer.empty())
	{
		throw std::exception("Input is empty");
	}

	std::regex re("\\D");
	std::sregex_token_iterator first{ m_InputBuffer.begin(), m_InputBuffer.end(), re, -1 },
							   last;

	std::vector<std::string> splitted(first, last);
	splitted.erase(std::remove(splitted.begin(), splitted.end(), ""), splitted.end());

	m_StructureFormer(splitted);
}

std::vector<std::pair<int,int>> InputHandler::GetResult() const
{
	return m_ResultIntervals;
}

std::string InputHandler::ResultToString(const std::set<int>& res)
{
	if (res.empty())
	{
		throw std::exception("Input value is empty");
	}

	std::string handler("");
	for (auto &elem : res)
	{
		handler += std::to_string(elem) + " ";
	}
	return handler;
}
