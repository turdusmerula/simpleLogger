#include <iostream>
#include <fstream>

#include <gtest/gtest.h>
#include <gtest_extend.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <simpleLogger.h>

#include <TestLogger.hpp>

int main(int argc, char* argv[])
{
	// decode command line
	boost::program_options::options_description desc("Options") ;
	::testing::InitGoogleTest(&argc, argv) ;

	try {
		// parse command line
	    desc.add_options()
	      ("help", "Print help messages")
		  ;

	    boost::program_options::variables_map vm ;
	    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm) ;

	    if(vm.count("help")){
	        std::cout << desc ;
			::testing::InitGoogleTest(&argc, argv) ;
	        exit(1) ;
	    }

	} catch(std::exception& e) {
		std::cerr << "Usage " << desc << std::endl ;
		return 1 ;
	}

	::testing::InitGoogleTest(&argc, argv) ;
	return RUN_ALL_TESTS() ;
}
