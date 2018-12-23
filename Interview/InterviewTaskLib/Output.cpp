#include "Output.h"

Output::Output(const std::string fileName) :
	m_OutFile(fileName),
	m_Indent{ 0 },
	m_OpenTags{ 0 },
	m_OpenElements{ 0 }
{
}

Output::~Output()
{
	if (m_OutFile.is_open())
	{
		m_OutFile.close();
	}
}

void Output::WriteOpenTag(const std::string & openTag)
{
	if (!(m_OutFile.is_open()))
	{
		throw std::exception("File is not opened");
	}
	for (size_t i = 0; i < m_Indent; i++)
	{
		m_OutFile << "\t";
	}
	m_TempOpenTag.resize(m_OpenTags + 1);
	m_OutFile << "<" << openTag << ">\n";
	m_TempOpenTag[m_OpenTags] = openTag;
	m_Indent++;
	m_OpenTags++;
}

void Output::WriteCloseTag()
{
	if (!(m_OutFile.is_open()))
	{
		throw std::exception("File is not opened");
	}
	m_Indent-- ;
	for (int i = 0; i < m_Indent; i++) {
		m_OutFile << "\t";
	}
	m_OutFile << "</" << m_TempOpenTag[m_OpenTags - 1] << ">\n";
	m_TempOpenTag.resize(m_OpenTags - 1);
	m_OpenTags--;

}

void Output::WriteStartElementTag(const std::string & elementTag)
{
	if (!(m_OutFile.is_open()))
	{
		throw std::exception("File is closed");
	}
	for (int i = 0; i < m_Indent; i++) {
		m_OutFile << "\t";
	}
	m_TempElementTag.resize(m_OpenElements + 1);
	m_TempElementTag[m_OpenElements] = elementTag;
	m_OpenElements += 1;
	m_OutFile << "<" << elementTag;
}

void Output::WriteEndElementTag()
{
	if (!(m_OutFile.is_open()))
	{
		throw std::exception("File is closed");
	}
	m_OutFile << "</" << m_TempElementTag[m_OpenElements - 1] << ">\n";
	m_TempElementTag.resize(m_OpenElements - 1);
	m_OpenElements -= 1;
}

void Output::WriteString(const std::string & input)
{
	if (!(m_OutFile.is_open()))
	{
		throw std::exception("File is closed");
	}
	m_OutFile << ">" << input;
}
