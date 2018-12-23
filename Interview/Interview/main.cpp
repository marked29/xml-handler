#include <iostream>
#include "InterviewTaskLib/Input.h"
#include "InterviewTaskLib/InputHandler.h"
#include "InterviewTaskLib/Output.h"
#include "InterviewTaskLib/PrimeNumberCounter.h"
#include "InterviewTaskLib/ThreadPool.h"

int main()
{
	Output instance("Hello.xml");
	instance.WriteOpenTag("root");
	instance.WriteStartElementTag("primary");
	instance.WriteString("1 2 3 5 7 ");
	instance.WriteEndElementTag();
	instance.WriteCloseTag();
	
	system("pause");
	return 0;
}