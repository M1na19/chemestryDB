cmake_minimum_required(VERSION 3.12)
project(chemestryDB)

set(CMAKE_CXX_STANDARD 11)


# Add header files
include_directories(BackEnd)

# Add executable
add_executable(main.cpp
        BackEnd/Api/notes.h)
target_link_libraries(main mysqlcppconn)

add_executable(test ./BackEnd/Logic/test.cpp)
add_executable(reset reseter.cpp)
target_link_libraries(reset mysqlcppconn)
target_link_libraries(test mysqlcppconn)

# Add additional dependencies if needed
# target_link_libraries(YourExecutableName ...)
