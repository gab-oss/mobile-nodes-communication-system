cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)
project(TIN)

enable_testing()

#Link header directories
#include_directories(${PROJECT_NAME} PUBLIC include/models include/controllers include/views)

#Find sources
file(GLOB_RECURSE sources src/*.cpp)
#file(GLOB_RECURSE sources_test tests/*.cpp)

#Set targets
add_executable(${PROJECT_NAME} ${sources})

#Link libraries
#target_link_libraries(${PROJECT_NAME} sfml-window sfml-system sfml-graphics)

#Link test libraries
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

get_filename_component(main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ABSOLUTE)
list(REMOVE_ITEM sources ${main})

foreach (testSrc ${sources_test})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${testSrc} NAME_WE)

    #Add compile target
    add_executable(${testName} ${testSrc} ${sources})

    #link to Boost libraries AND your targets and dependencies
    target_link_libraries(${testName} ${Boost_LIBRARIES})
    #target_link_libraries(${testName} sfml-window sfml-system sfml-graphics)
    #target_include_directories(${testName} PUBLIC include/models include/controllers include/views)

    #I like to move testing binaries into a testBin directory
    set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

    #Finally add it to test execution -
    #Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName})
endforeach (testSrc)