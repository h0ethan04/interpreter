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

set(EXECUTABLE
  main
)


set(MAIN_SRC_FILES
  src/main.cpp
)
add_executable(main ${MAIN_SRC_FILES} src/main.cpp)

# set(BOOST_REQUIRED_COMPONENTS
#     filesystem
# )
# set(BOOST_MIN_VERSION 1.74.0) # or whatever you need!
# # Here you can either append or set a root to look into
# # In general, **don't do that**! Your boost build and installation
# # should come with the correct CMake configure scripts to automate this!
# # If you set it here, the people trying to build your code on a different
# # machine **WILL** hate you.
# # set(BOOST_ROOT "/Volumes/Code/boost_1_79_0")
# find_package(
#     Boost ${BOOST_MIN_VERSION} REQUIRED
#     COMPONENTS ${BOOST_REQUIRED_COMPONENTS}
# )
# target_link_libraries(${EXECUTABLE} PUBLIC  
#     Boost::filesystem
# )
# target_include_directories(${EXECUTABLE} PRIVATE include)