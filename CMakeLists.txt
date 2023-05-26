cmake_minimum_required(VERSION 3.20)

project(GRIN CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(PARSING_SRC_FILES
#   src/parsing.cpp
#   src/parsing.hpp
# )
# add_executable(parsing ${PARSING_SRC_FILES} src/parsing.cpp)

set(MAIN_SRC_FILES
  src/main.cpp
)
add_executable(main ${MAIN_SRC_FILES} src/main.cpp)