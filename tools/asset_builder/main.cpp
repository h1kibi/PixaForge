// Asset Builder 工具
// 用法: asset_builder <source_dir> <output.pak>

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: asset_builder <source_dir> <output.pak>" << std::endl;
        return 1;
    }

    std::string source_dir = argv[1];
    std::string output_path = argv[2];

    std::cout << "Asset Builder" << std::endl;
    std::cout << "Source: " << source_dir << std::endl;
    std::cout << "Output: " << output_path << std::endl;

    // TODO: 实现资源打包逻辑
    // 1. 扫描源目录
    // 2. 处理纹理（Aseprite CLI 导出）
    // 3. 处理关卡（LDtk 解析）
    // 4. 处理音频
    // 5. 打包成 .pak 文件

    std::cout << "Asset building not implemented yet." << std::endl;
    return 0;
}
