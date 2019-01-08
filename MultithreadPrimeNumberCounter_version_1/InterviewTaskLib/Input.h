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
	Input(const std::string & m_fileName);
	Input(const Input&) = delete;
	Input operator=(const Input&) = delete;
	~Input();
	void GetFile();
	std::string GetBuffer() const;
	
};

