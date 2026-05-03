// Level Preview 工具
// 用法: level_preview <level.ldtk>

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: level_preview <level.ldtk>" << std::endl;
        return 1;
    }

    std::string level_path = argv[1];

    std::cout << "Level Preview" << std::endl;
    std::cout << "Level: " << level_path << std::endl;

    // TODO: 实现关卡预览
    // 1. 创建窗口
    // 2. 加载 LDtk 关卡
    // 3. 渲染 tilemap
    // 4. 显示碰撞层
    // 5. 显示触发器
    // 6. 显示摄像机边界

    std::cout << "Level preview not implemented yet." << std::endl;
    return 0;
}
