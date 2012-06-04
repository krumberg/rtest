add_executable(
    skip_prefixes
    skip_prefixes.cpp
)
target_link_libraries(skip_prefixes rtest)

add_executable(
    prefixes
    prefixes.cpp
)
target_link_libraries(prefixes rtest)
