#include "Input.h"

Input::Input(const std::string & m_fileName) : m_Buffer(""), m_InFile(m_fileName)
{
	this->m_FileName = m_fileName;
}

Input::~Input()
{
	if (m_InFile.is_open())
		m_InFile.close();
}

void Input::GetFile()
{
	char reader;
	if (!m_InFile.is_open())
	{
		throw std::exception("File could not be opened");
	}

	while (m_InFile.get(reader))
	{
		m_Buffer += reader;
	}
}

std::string Input::GetBuffer() const
{
	return m_Buffer;
}

