# Level Preview 工具
# 用于预览和调试关卡

add_executable(level_preview
    main.cpp
)

target_link_libraries(level_preview PRIVATE engine)
target_include_directories(level_preview PRIVATE ${CMAKE_SOURCE_DIR}/engine)
