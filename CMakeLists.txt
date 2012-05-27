project (RTEST)

add_library(rtest rtest.cpp)

include_directories(${RTEST_SOURCE_DIR})

add_subdirectory (examples)
