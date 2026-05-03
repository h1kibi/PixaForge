add_executable(game
    main.cpp
    player_state.h
    player_physics.h
    player_physics.cpp
)

target_link_libraries(game
    PRIVATE
        pixaforge
)

set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
