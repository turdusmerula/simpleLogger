#include <gtest/gtest.h>
#include <gtest_extend.h>

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <memory>

extern std::string connection ;

// The fixture for testing class Database.
class TestLogger : public ::testing::Test
{
public:
	static void SetUpTestCase()
	{
	}

	static void TearDownTestCase()
	{
	}

	virtual void SetUp()
	{
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown()
	{
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Foo.
} ;

class User ;


TEST_F(TestLogger, TestLog) {
	LOG_TRACE() << "this is a trace message";
	LOG_TRACE("test") << "this is a trace message";

	LOG_DEBUG() << "this is a debug message";
	LOG_DEBUG("test") << "this is a debug message";

	LOG_WARNING() << "this is a warning message";
	LOG_WARNING("test") << "this is a warning message";

	LOG_ERROR() << "this is an error message";
	LOG_ERROR("test") << "this is an error message";

	LOG_FATAL() << "this is a fatal error message";
	LOG_FATAL("test") << "this is a fatal error message";
}

TEST_F(TestLogger, TestThreadLog) {
	std::vector<std::shared_ptr<std::thread>> threads ;

	for(int i=0 ; i<10 ; i++)
	{
		threads.push_back(std::make_shared<std::thread>(
			[&]() {
				for(int j=0 ; j<100 ; j++)
				{
					LOG_TRACE() << "this is a trace message";
					LOG_TRACE("test") << "this is a trace message";

					LOG_INFO() << "this is an info message";
					LOG_INFO("test") << "this is an info message";

					LOG_DEBUG() << "this is a debug message";
					LOG_DEBUG("test") << "this is a debug message";

					LOG_WARNING() << "this is a warning message";
					LOG_WARNING("test") << "this is a warning message";

					LOG_ERROR() << "this is an error message";
					LOG_ERROR("test") << "this is an error message";

					LOG_FATAL() << "this is a fatal error message";
					LOG_FATAL("test") << "this is a fatal error message";
				}
			})
		) ;
	}

	for(auto thread : threads)
		thread->join() ;
}
