cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

# set the project name
project(WebScraper)

# add the executable
add_executable(WebScraper main.cpp)

add_subdirectory(Scraper)

target_include_directories(WebScraper PUBLIC Scraper)

target_link_libraries(WebScraper PUBLIC HelloWorld Scraper)

add_library(HelloWorld HelloWorld.hpp HelloWorld.cpp)

