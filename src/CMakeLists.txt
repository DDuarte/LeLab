add_subdirectory(LeEngine)

set(LE_ENGINE_LIBRARIES LeEngine)
set(LE_ENGINE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/LeEngine)

add_subdirectory(LeServer)
add_subdirectory(LeClient)
add_subdirectory(LeTests)

