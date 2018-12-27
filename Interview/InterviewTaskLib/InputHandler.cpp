#include "InputHandler.h"

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

	m_IntervalContainer.reserve(info.size() / 2);
	for (size_t i = 0; i < info.size(); i += 2)
	{
		m_IntervalContainer.push_back({ stoi(info[i]), stoi(info[i + 1]) });
	}
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
	return m_IntervalContainer;
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
