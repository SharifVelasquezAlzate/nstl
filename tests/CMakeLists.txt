cmake_minimum_required(VERSION 3.14)

project(nstl_tests)

include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES "./**/*.cpp")

add_library(test_utils STATIC utils.cpp)
target_include_directories(test_utils
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

foreach (TEST_SOURCE ${TEST_SOURCES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/tests" "${TEST_SOURCE}")

    string(REPLACE ".cpp" "" EXE_NAME "${REL_PATH}")
    string(REPLACE "/" "_" TARGET_NAME "${EXE_NAME}")

    add_executable(${TARGET_NAME} ${TEST_SOURCE})

    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/${EXE_NAME}/.."
    )

    target_link_libraries(${TARGET_NAME}
        GTest::gtest_main
        nstl
        test_utils
    )

    gtest_discover_tests(${TARGET_NAME})


    get_filename_component(FEATURE "${REL_PATH}" DIRECTORY)

    list(APPEND FEATURE_${FEATURE}_SOURCES ${TEST_SOURCE})

    list(APPEND ALL_FEATURES ${FEATURE})
endforeach()

list(REMOVE_DUPLICATES ALL_FEATURES)

foreach(FEATURE ${ALL_FEATURES})
    add_executable(${FEATURE} ${FEATURE_${FEATURE}_SOURCES})

    set_target_properties(${FEATURE} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/${FEATURE}"
    )

    target_link_libraries(${FEATURE}
        GTest::gtest_main
        nstl
        test_utils
    )

    gtest_discover_tests(${FEATURE})
endforeach()
