cmake_minimum_required(VERSION 3.12)
project(chemestryDB)

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCE_FILES main.cpp)

# Add header files
include_directories(BackEnd)

# Add executable
add_executable(main ${SOURCE_FILES})
target_link_libraries(main mysqlcppconn)

# Add additional dependencies if needed
# target_link_libraries(YourExecutableName ...)
