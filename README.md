simpleLogger
============

A simple logger based on Boost.Log v2. It shows how to create a custom global logger, 
add a sink with two backends and a filter, add attributes and formats the log message.
It also provides some convenience macros for easy usage. 

app.cpp demonstrates how simpleLogger can be used: just include simpleLogger.h, 
link the simpleLogger library and use the LOG_* macros to write the logs.

Its tested and builds on Linux + GCC 4.9 and Clang 3.6.

see also http://gernotklingler.com/blog/simple-customized-logger-based-boost-log-v2/

Build
=====

Boost 1.58 minimum needed, if you don't have it installed on your system path you can 
set the BOOST_ROOT venv to use a custom install path

  BOOST_ROOT=/opt/boost_1_59_0 ./build

Test
====

You can run tests with

  ./build test