cmake_minimum_required(VERSION 3.20)

project(GRIN CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# copy this format to add more individual build files
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

add_library(token_objects OBJECT
  src/token.hpp
  src/token.cpp
  src/location.hpp
  src/location.cpp
)

add_library(lexing_objects OBJECT
  src/lexing.hpp
  src/lexing.cpp
)

add_library(parsing_objects OBJECT
  src/parsing.hpp
  src/parsing.cpp
)

add_library(preprocessing_objects OBJECT
  src/preprocessing.hpp
  src/preprocessing.cpp
)

add_library(arithmetic_objects OBJECT
  src/arithmetic.hpp
  src/arithmetic.cpp
)


find_package(GTest)
if (GTest_FOUND)
    add_library(gtestmain OBJECT
      gtest/gtestmain.cpp
    )
    target_include_directories(gtestmain PUBLIC src ${GTEST_INCLUDE_DIRS})
    target_link_libraries(gtestmain PUBLIC ${GTEST_LIBRARIES})

    add_executable(token_gtests
      gtest/token_gtests.cpp
      $<TARGET_OBJECTS:token_objects>
    )
    target_link_libraries(token_gtests PRIVATE gtestmain)
    
    add_executable(lexing_gtests
      gtest/lexing_gtests.cpp
      $<TARGET_OBJECTS:token_objects>
      $<TARGET_OBJECTS:lexing_objects>
    )
    target_link_libraries(lexing_gtests PRIVATE gtestmain)
    
    add_executable(parsing_gtests
      gtest/parsing_gtests.cpp
      $<TARGET_OBJECTS:token_objects>
      $<TARGET_OBJECTS:lexing_objects>
      $<TARGET_OBJECTS:parsing_objects>
    )
    target_link_libraries(parsing_gtests PRIVATE gtestmain)

    add_executable(preprocessing_gtests
      gtest/preprocessing_gtests.cpp
      $<TARGET_OBJECTS:lexing_objects>
      $<TARGET_OBJECTS:parsing_objects>
      $<TARGET_OBJECTS:preprocessing_objects>
      $<TARGET_OBJECTS:token_objects>
    )
    target_link_libraries(preprocessing_gtests PRIVATE gtestmain)

    add_executable(arithmetic_gtests
      gtest/arithmetic_gtests.cpp
      $<TARGET_OBJECTS:arithmetic_objects>
      $<TARGET_OBJECTS:token_objects>
    )
    target_link_libraries(arithmetic_gtests PRIVATE gtestmain)
    # copy this format to add more gtests
    # add_executable(parsing_gtests
    #     gtest/parsing_gtests.cpp
    # )
    # target_link_libraries(parsing_gtests PRIVATE gtestmain)

endif()

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