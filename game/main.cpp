#include <iostream>
#include <memory>

// 引擎头文件
#include "core/types.h"
#include "core/math.h"
#include "core/log.h"
#include "core/assert.h"
#include "core/time.h"
#include "core/handle.h"

// 游戏状态
struct GameState {
    bool running = true;
    pixel::f32 accumulator = 0.0f;
};

// 主入口
int main(int argc, char* argv[]) {
    using namespace pixel;

    PE_LOG_INFO("Pixel Engine v{}.{}", 0, 1);
    PE_LOG_INFO("Initializing...");

    GameState game;

    // TODO: 初始化窗口
    // TODO: 初始化渲染器
    // TODO: 初始化输入系统
    // TODO: 初始化音频系统
    // TODO: 加载资源
    // TODO: 加载关卡

    PE_LOG_INFO("Engine initialized successfully");

    // 主循环
    Timer timer;
    timer.reset();

    while (game.running) {
        f32 dt = timer.tick();
        game.accumulator += dt;

        // TODO: 处理输入
        // platform.poll_events();

        // 固定时间步更新
        while (game.accumulator >= time::FIXED_DT) {
            // TODO: 输入快照
            // input.begin_frame();

            // TODO: 游戏逻辑更新
            // world.fixed_update(time::FIXED_DT);
            // collision.step(world, time::FIXED_DT);
            // gameplay.fixed_update(world, time::FIXED_DT);

            // TODO: 输入结束
            // input.end_frame();

            game.accumulator -= time::FIXED_DT;
        }

        // 插值因子（用于平滑渲染）
        f32 alpha = game.accumulator / time::FIXED_DT;

        // TODO: 渲染
        // renderer.begin_frame();
        // renderer.draw_world(world, camera, alpha);
        // debug.draw();
        // renderer.end_frame();

        // 临时：退出条件
        // game.running = !platform.should_close();
    }

    PE_LOG_INFO("Shutting down...");

    // TODO: 清理资源

    return 0;
}
