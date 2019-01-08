#pragma once
#include "Input.h"
#include "Output.h"
#include "InputHandler.h"
#include "PrimeNumberCounter.h"
#include "ThreadPool.h"

class XmlHandlerInterface
{
	std::string m_Input;
	std::string m_Output;
public:
	XmlHandlerInterface();
	~XmlHandlerInterface();

	void WorkFlow();

};

