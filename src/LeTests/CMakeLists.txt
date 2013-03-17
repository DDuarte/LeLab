add_executable(LeTests
    main.cpp
    vector_tests.cpp
)

include_directories(LeTests ${GTEST_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/src ${Boost_INCLUDE_DIR})

target_link_libraries(LeTests ${LE_ENGINE_LIBRARIES} ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG})
