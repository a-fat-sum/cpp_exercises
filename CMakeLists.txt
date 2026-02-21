cmake_minimum_required(VERSION 3.10)

project(SimpleCppProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Collections)
add_subdirectory(ExemplarCollections)
add_subdirectory(IllustrationTools)

add_executable(SimpleCppProject main.cpp)
target_link_libraries(SimpleCppProject PRIVATE Collections)
#target_link_libraries(SimpleCppProject PRIVATE ExemplarCollections)
