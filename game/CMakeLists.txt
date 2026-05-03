find_package(SDL3 CONFIG REQUIRED)

add_executable(game main.cpp)

target_link_libraries(game
    PRIVATE
        pixaforge
        SDL3::SDL3
)

set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
