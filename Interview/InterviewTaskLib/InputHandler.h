#pragma once
#include <vector>
#include <string>
#include <regex>
#include <exception>
#include <set>

class InputHandler
{
private:
	std::string m_InputBuffer;
	std::vector<std::pair<int, int>> m_ResultIntervals;

	std::vector<std::pair<int, int>> m_MergeInterval(std::vector<std::pair<int, int>>& intervals);
	void m_StructureFormer(const std::vector<std::string> &info);

public:
	InputHandler() = default;
	InputHandler(const std::string & input);
	void ParseInput();
	std::vector<std::pair<int,int>> GetResult() const;


	std::string ResultToString(const std::set<int> & res);

};

