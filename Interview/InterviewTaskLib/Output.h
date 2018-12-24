#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
class Output
{
private:	
	std::ofstream m_OutFile;
	int m_Indent;
	int m_OpenTags;
	int m_OpenElements;
	std::vector<std::string> m_TempOpenTag;
	std::vector<std::string> m_TempElementTag;

	void m_Check();

public:
	Output() = default;
	explicit Output(const std::string fileName);
	Output(const Output&) = delete;
	Output operator=(const Output&) = delete;
	~Output();

	void WriteOpenTag(const std::string &openTag);
	void WriteCloseTag();
	void WriteStartElementTag(const std::string &elementTag);
	void WriteEndElementTag();
	void WriteString(const std::string &input);
};

