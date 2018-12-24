#include "pch.h"
#include "InterviewTaskLib/PrimeNumberCounter.h"
#include "InterviewTaskLib/Input.h"
#include "InterviewTaskLib/InputHandler.h"
#include "InterviewTaskLib/Output.h"
#include "InterviewTaskLib/PrimeNumberCounter.h"
#include "InterviewTaskLib/ThreadPool.h"
#include <algorithm>

TEST(PrimeNumberCounter, DefaultConstruction) {

	PrimeNumberCounter primeCounter;
	EXPECT_EQ(0, primeCounter.GetIntervalAmount());
}

TEST(PrimeNumberCounter, ExplicitConstruction) {

	std::vector<std::pair<int, int>> intervals;
	intervals.push_back({ 100,200 });
	intervals.push_back({ 500,888 });

	PrimeNumberCounter primeCounter(intervals);
	EXPECT_EQ(2, primeCounter.GetIntervalAmount());
}

TEST(PrimeNumberCounter, ExplicitEmptyConstruction) {

	std::vector<std::pair<int, int>> intervals;

	PrimeNumberCounter primeCounter(intervals);
	EXPECT_EQ(0, primeCounter.GetIntervalAmount());
}

TEST(PrimeNumberCounter, EmptyResult) {

	std::vector<std::pair<int, int>> intervals;
	PrimeNumberCounter primeCounter(intervals);
	auto var = primeCounter.GetResult();

	EXPECT_TRUE(var.empty());
}

TEST(PrimeNumberCounter, CorrectIntervalInput) {
		
	PrimeNumberCounter primeCounter;
	primeCounter.PrimeNumbers(std::make_pair(0,10));
		
	auto var = primeCounter.GetResult();
	std::vector<int> primeNum = { 2,3,5,7 };
		
	EXPECT_TRUE(std::equal(var.begin(),var.end(),primeNum.begin(),primeNum.end()));
}

TEST(PrimeNumberCounter, SwappedIntervalInput) {

	PrimeNumberCounter primeCounter;
	primeCounter.PrimeNumbers(std::make_pair(10, 0));

	auto var = primeCounter.GetResult();
	std::vector<int> primeNum = { 2,3,5,7 };

	EXPECT_TRUE(std::equal(var.begin(), var.end(), primeNum.begin(), primeNum.end()));
}

TEST(PrimeNumberCounter, EqualIntervalInput) {

	PrimeNumberCounter primeCounter;
	primeCounter.PrimeNumbers(std::make_pair(2, 2));

	auto var = primeCounter.GetResult();
	std::vector<int> primeNum = { 2,3,5,7 };

	EXPECT_FALSE(std::equal(var.begin(), var.end(), primeNum.begin(), primeNum.end()));
}

TEST(InputHandler, DefaultConstructing)
{
	InputHandler Handler;
	EXPECT_TRUE((Handler.GetResult()).empty());
}

TEST(InputHandler, DefaultConstructingSplitting)
{
	InputHandler Handler;
	EXPECT_THROW({
	try
	{
		Handler.Split("\\D");
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("Input is empty", e.what());
		throw;
	}
	}, std::exception);
}

TEST(InputHandler, DefaultConstructingResult)
{
	InputHandler Handler;
	EXPECT_TRUE((Handler.GetResult()).empty());
}

TEST(InputHandler, DefaultConstructingEmptyResultToString)
{
	InputHandler Handler;
	std::set<int> uniqueNums;
	
	EXPECT_THROW({
		try
		{
			Handler.ResultToString(uniqueNums);
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("Input value is empty", e.what());
			throw;
		}
	}, std::exception);
}

TEST(InputHandler, DefaultConstructingResultToString)
{
	InputHandler Handler;
	std::set<int> uniqueNums{2,3,4,5,6};
	std::string str = Handler.ResultToString(uniqueNums);
	std::string str1 = "2 3 4 5 6 ";

	EXPECT_STREQ( str1.c_str(),str.c_str() );
}

TEST(InputHandler, ExplicitConstructingEmptyString)
{
	InputHandler Handler("");
	EXPECT_TRUE((Handler.GetResult()).empty());
}

TEST(InputHandler, ExplicitConstructingEmptyStringSplit)
{
	InputHandler Handler("");
	EXPECT_THROW({
		try
		{
			Handler.Split("\\D");
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("Input is empty", e.what());
			throw;
		}
	}, std::exception);
}

TEST(InputHandler, ExplicitConstructingSplit)
{
	InputHandler Handler("asd");
	EXPECT_THROW({
		try
		{
			Handler.Split("\\D");
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("Empty input", e.what());
			throw;
		}
		}, std::exception);
}
TEST(InputHandler, ExplicitConstructingNotEvenSplit)
{
	InputHandler Handler("asd1");
	EXPECT_THROW({
		try
		{
			Handler.Split("\\D");
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("Couldn't be sliced into pairs", e.what());
			throw;
		}
		}, std::exception);
}

TEST(InputHandler, ExplicitConstructingBadSplit)
{
	InputHandler Handler("1231");
	EXPECT_THROW({
		try
		{
			Handler.Split("\\D");
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("Couldn't be sliced into pairs", e.what());
			throw;
		}
		}, std::exception);
}

TEST(InputHandler, ExplicitConstructingCorrectSplit)
{
	InputHandler Handler("asd1asd10");
	Handler.Split("\\D");
	auto var = Handler.GetResult();
	EXPECT_EQ(1, var[0].first);
}

TEST(InputHandler, ExplicitConstructingUnhandledInput)
{
	InputHandler Handler("sadsdad1aadasdad2asdasd3dvfdsf4");
	EXPECT_TRUE((Handler.GetResult()).empty());
}


TEST(Input, DefaultConstructing)
{
	Input File;
	EXPECT_THROW({
		try
		{
			File.GetFile();
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("File could not be opened", e.what());
			throw;
		}
	}, std::exception);
}

TEST(Input, DefaultConstructingGetBuffer)
{
	Input File;
	EXPECT_TRUE((File.GetBuffer()).empty());
}

TEST(Input, NotExistingFileExplicitConstructingGetBuffer)
{
	Input File("Helloworld.cpp");
	EXPECT_TRUE((File.GetBuffer()).empty());
}

TEST(Input, NotExistingFileExplicitConstructingGetInfo)
{
	Input File("Helloworld.cpp");
	EXPECT_THROW({
		try
		{
			File.GetFile();
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("File could not be opened", e.what());
			throw;
		}
	}, std::exception);
}
TEST(Input, ExistingFileExplicitConstructingGetInfo)
{
	Input File("Test.txt");
	File.GetFile();
	std::string s = "Hello ,World;";
	EXPECT_STREQ(s.c_str(), (File.GetBuffer()).c_str());
}

TEST(Output, DefaultConstructionWritting)
{
	Output File;
	EXPECT_THROW({
		try
		{
			File.WriteString("Some Text");
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("File is not opened", e.what());
			throw;
		}
	}, std::exception);
}

TEST(Output, DefaultConstructionOpenTag)
{
	Output File;
	EXPECT_THROW({
		try
		{
			File.WriteOpenTag("Tag");
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("File is not opened", e.what());
			throw;
		}
	}, std::exception);
}

TEST(Output, DefaultConstructionCloseTag)
{
	Output File;
	EXPECT_THROW({
		try
		{
			File.WriteCloseTag();
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("File is not opened", e.what());
			throw;
		}
	}, std::exception);
}

TEST(Output, DefaultConstructionStartTag)
{
	Output File;
	EXPECT_THROW({
		try
		{
			File.WriteStartElementTag("SomeTag");
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("File is not opened", e.what());
			throw;
		}
	}, std::exception);
}

TEST(Output, DefaultConstructionEndTag)
{
	Output File;
	EXPECT_THROW({
		try
		{
			File.WriteEndElementTag();
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("File is not opened", e.what());
			throw;
		}
	}, std::exception);
}

TEST(Output, ExplicitConstructionWritting)
{
	{
		Output File("TestFile.txt");
		File.WriteString("Some Text");
	}
	Input Reader("TestFile.txt");
	Reader.GetFile();

	EXPECT_STREQ(">Some Text", Reader.GetBuffer().c_str());
}

TEST(Output, ExplicitConstructionEmptyWritting)
{
	{
		Output File("TestFile.txt");
		File.WriteString("");
	}
	Input Reader("TestFile.txt");
	Reader.GetFile();

	EXPECT_STREQ(">", Reader.GetBuffer().c_str());
}

TEST(Output, ExplicitConstructionOpenTag)
{
	{
		Output File("TestFile.txt");
		File.WriteOpenTag("Tag");
	}
	Input Reader("TestFile.txt");
	Reader.GetFile();

	EXPECT_STREQ("<Tag>\n", Reader.GetBuffer().c_str());
}


TEST(Output, ExplicitConstructionEmptyOpenTag)
{
	{
		Output File("TestFile.txt");
		File.WriteOpenTag("");
	}
	Input Reader("TestFile.txt");
	Reader.GetFile();

	EXPECT_STREQ("<>\n", Reader.GetBuffer().c_str());
}


TEST(Output, ExplicitConstructionCloseTag)
{
	
	Output File("TestFile.txt");
	
	EXPECT_THROW({
		try
		{
			File.WriteCloseTag();
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("No open tags found", e.what());
			throw;
		}
	}, std::exception);
}

TEST(Output, ExplicitConstructionStartTag)
{
	{
		Output File("TestFile.txt");
		File.WriteStartElementTag("SomeTag");
	}
	Input Reader("TestFile.txt");
	Reader.GetFile();

	EXPECT_STREQ("<SomeTag", Reader.GetBuffer().c_str());
}

TEST(Output, ExplicitConstructionEmptyStartTag)
{
	{
		Output File("TestFile.txt");
		File.WriteStartElementTag("");
	}
	Input Reader("TestFile.txt");
	Reader.GetFile();

	EXPECT_STREQ("<", Reader.GetBuffer().c_str());
}

TEST(Output, ExplicitConstructionEndTag)
{

	Output File("TestFile.txt");

	EXPECT_THROW({
		try
		{
			File.WriteEndElementTag();
		}
		catch (const std::exception& e)
		{
			EXPECT_STREQ("No open element tags found", e.what());
			throw;
		}
		}, std::exception);
}