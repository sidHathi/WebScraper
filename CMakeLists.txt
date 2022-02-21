cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)

# set the project name
project(WebScraper)

# add the executable
add_executable(WebScraper main.cpp)
add_library(HelloWorld HelloWorld.hpp HelloWorld.cpp)

add_subdirectory(Scraper)

add_subdirectory(StockTracker)

target_include_directories(WebScraper PUBLIC Scraper)
target_include_directories(WebScraper PUBLIC StockTracker)

target_link_libraries(WebScraper PUBLIC HelloWorld Scraper stocktracker)
