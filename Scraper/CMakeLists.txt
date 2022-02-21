
find_library(libCPR cpr NAMES lcpr)

find_library(libGumbo gumbo NAMES lgumbo)

find_path(cprIncludeDir cpr/cpr.h)

find_path(gumboIncludeDir gumbo.h)

add_library(gumbo SHARED IMPORTED /opt/homebrew/lib/libgumbo.dylib)
set_property(TARGET gumbo PROPERTY
             IMPORTED_LOCATION "/opt/homebrew/lib/libgumbo.dylib")

add_library(cpr SHARED IMPORTED /opt/homebrew/lib/libcpr.dylib)
set_property(TARGET cpr PROPERTY
             IMPORTED_LOCATION "/opt/homebrew/lib/libcpr.dylib")
             
add_library(Scraper Scraper.hpp Scraper.cpp)

target_include_directories(Scraper PUBLIC "/opt/homebrew/include")
target_link_directories(Scraper PUBLIC "/opt/homebrew/lib/")

target_link_libraries(Scraper PUBLIC cpr)

target_link_libraries(Scraper PUBLIC gumbo)

