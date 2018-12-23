#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>

class Input
{
private:
	std::string m_FileName;
	std::string m_Buffer;
	std::ifstream m_InFile;

public:
	Input() = default;
	explicit Input(const Input&) = delete;
	Input(const std::string & m_fileName);
	~Input();
	Input operator=(const Input&) = delete;
	void GetFile();
	std::string GetBuffer() const;
	
};

