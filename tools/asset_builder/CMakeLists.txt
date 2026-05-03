# Asset Builder 工具
# 命令行工具，用于打包资源

add_executable(asset_builder
    main.cpp
)

target_link_libraries(asset_builder PRIVATE engine)
target_include_directories(asset_builder PRIVATE ${CMAKE_SOURCE_DIR}/engine)
