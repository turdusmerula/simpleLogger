project(simpleLogger-lib)

find_package(Boost 1.58 COMPONENTS log log_setup date_time thread REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DMULTI_THREADED)

include_directories(
	${Boost_INCLUDE_DIR}
	..
    )

LINK_DIRECTORIES(
    ${Boost_LIBRARY_DIRS}
)

FILE(GLOB sources 
    *.cpp
    )
    
FILE(GLOB headers 
    src/*.h
    )

add_library(${PROJECT_NAME} SHARED ${sources})

target_link_libraries(${PROJECT_NAME} 
    pthread

    ${Boost_LIBRARIES} 

    dl
    )
