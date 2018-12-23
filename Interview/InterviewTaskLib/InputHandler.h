#pragma once
#include <vector>
#include <string>
#include <regex>
#include <exception>

class InputHandler
{
private:
	std::string m_InputBuffer;
	std::vector<std::pair<int, int>> m_IntervalContainer;
	void m_StructureFormer(const std::vector<std::string> &info);

public:
	InputHandler() = default;
	InputHandler(const std::string & input);
	void Split(const std::string & regex);
	std::vector<std::pair<int,int>> GetResult() const;

};

