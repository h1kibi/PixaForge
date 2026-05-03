# PixaForge Engine

一个专门用于 2D 像素风闯关游戏的轻量高性能运行时。

## 技术栈

- **语言**: C++20
- **平台层**: SDL3
- **渲染**: SDL_Renderer / OpenGL（可切换）
- **关卡**: LDtk（优先）/ Tiled（后续兼容）
- **调试 UI**: Dear ImGui
- **构建**: CMake

## 项目结构

```
PixaForge/
├─ engine/          引擎核心
│  ├─ core/         基础设施（类型、数学、日志）
│  ├─ platform/     平台抽象（SDL3）
│  ├─ renderer/     2D 渲染系统
│  ├─ input/        Action-based 输入系统
│  ├─ world/        Entity + Component 系统
│  ├─ collision/    AABB + Tile 碰撞
│  ├─ level/        关卡加载（LDtk/Tiled）
│  ├─ gameplay/     游戏行为系统
│  ├─ assets/       资源管理
│  └─ online/       在线服务接口
├─ game/            游戏代码
├─ tools/           工具（asset_builder, level_preview）
├─ assets_raw/      原始资源
├─ assets_build/    构建后的资源
├─ third_party/     第三方库
└─ docs/            文档
```

## 快速开始

### 1. 安装依赖

推荐使用 vcpkg：

```bash
vcpkg install sdl3 imgui
```

### 2. 构建

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

### 3. 运行

```bash
./bin/game
```

## 核心特性

- 虚拟分辨率 + 整数倍缩放
- Pixel-perfect 摄像机
- Sprite Batch / Tilemap Batch
- 自研 AABB + Tile 碰撞
- Action-based 输入系统
- LDtk 关卡导入
- 固定时间步（60Hz）
- 行为系统（Entity + Behavior）

## 开发路线

- [x] 项目结构
- [x] Milestone 0: 窗口和主循环
- [x] Milestone 1: 渲染一个角色
- [x] Milestone 2: 输入和移动
- [x] Milestone 3: 平台跳跃手感
- [x] Milestone 3.5: 手感调校
- [ ] Milestone 4: LDtk 关卡
- [ ] Milestone 5: 完整一关 demo

## 许可证

待定
