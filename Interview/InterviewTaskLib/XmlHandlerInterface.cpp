#include "XmlHandlerInterface.h"



XmlHandlerInterface::XmlHandlerInterface() 
{
	std::cout << "Set input file: ";
	std::cin >> m_Input;
	std::cout << "Set output file: ";
	std::cin >> m_Output;
}


XmlHandlerInterface::~XmlHandlerInterface()
{
}

void XmlHandlerInterface::WorkFlow()
{
	try
	{
		Input fileHandler(m_Input);
		fileHandler.GetFile();
		InputHandler handler(fileHandler.GetBuffer());
		handler.ParseInput("\\D");
		auto var = handler.GetResult();

		PrimeNumberCounter primeCounter;
		{
			ThreadPool pool{ var.size() };
			for (auto & elem : var)
			{
				pool.Post([&]() { primeCounter.CalcAndAccumulatePrimes(elem); });
			}
			pool.Destroy();
		}

		Output fileWriter(m_Output);
		fileWriter.WriteOpenTag("root");
		fileWriter.WriteStartElementTag("primary");
		fileWriter.WriteString(handler.ResultToString(primeCounter.GetResult()));
		fileWriter.WriteEndElementTag();
		fileWriter.WriteCloseTag();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
