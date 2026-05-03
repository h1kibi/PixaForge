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

# Copy assets to output directory
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets_raw
        $<TARGET_FILE_DIR:game>/assets_raw
    COMMENT "Copying assets to output directory"
)
