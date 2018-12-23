#include <iostream>
#include "InterviewTaskLib/Input.h"
#include "InterviewTaskLib/InputHandler.h"
#include "InterviewTaskLib/Output.h"
#include "InterviewTaskLib/PrimeNumberCounter.h"
#include "InterviewTaskLib/ThreadPool.h"

int main()
{

	std::string filename = "intervals.xml";

	Input fileHandler(filename);
	fileHandler.GetFile();
	InputHandler handler(fileHandler.GetBuffer());
	handler.Split("\\D");
	auto var = handler.GetResult();

	PrimeNumberCounter primeCounter(var);
	{
		ThreadPool pool{ primeCounter.GetIntervalAmount() };
		for (auto & elem : var)
		{
			pool.Post([&]() { primeCounter.PrimeNumbers(elem); });
		}
		pool.Destroy();
	}

	Output fileWriter("Hello.xml");
	fileWriter.WriteOpenTag("root");
	fileWriter.WriteStartElementTag("primary");
	fileWriter.WriteString(handler.ResultToString(primeCounter.GetResult()));
	fileWriter.WriteEndElementTag();
	fileWriter.WriteCloseTag();
	
	system("pause");
	return 0;
}