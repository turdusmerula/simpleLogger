project(simpleLogger-tests)

find_package(Boost 1.58 COMPONENTS log log_setup date_time filesystem system thread program_options REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR};${ROOT_PATH})
add_definitions(-DMULTI_THREADED)

include_directories(
	${Boost_INCLUDE_DIR}
	src
	${ROOT_PATH}/src
)

FILE(GLOB sources 
    src/main.cpp
    )

FILE(GLOB headers 
    src/*.hpp
    )

LINK_DIRECTORIES(
    ${Boost_LIBRARY_DIRS} 
    )

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} 
	gtest
	gtest_main
	pthread
 
    simpleLogger-lib

    ${Boost_LIBRARIES} 
    )

enable_testing()
add_test(tests Build/bin/${PROJECT_NAME})
