#pragma once

#include "../core/types.h"

namespace pixel {

// 键盘按键码（简化版，基于 SDL）
enum class KeyCode : i32 {
    Unknown = 0,
    A = 'a', B = 'b', C = 'c', D = 'd', E = 'e', F = 'f', G = 'g',
    H = 'h', I = 'i', J = 'j', K = 'k', L = 'l', M = 'm', N = 'n',
    O = 'o', P = 'p', Q = 'q', R = 'r', S = 's', T = 't', U = 'u',
    V = 'v', W = 'w', X = 'x', Y = 'y', Z = 'z',
    
    Num0 = '0', Num1 = '1', Num2 = '2', Num3 = '3', Num4 = '4',
    Num5 = '5', Num6 = '6', Num7 = '7', Num8 = '8', Num9 = '9',
    
    Space = ' ',
    Return = '\r',
    Escape = '\x1B',
    Tab = '\t',
    Backspace = '\b',
    
    Up, Down, Left, Right,
    
    LShift, RShift,
    LCtrl, RCtrl,
    LAlt, RAlt,
    
    F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, F11, F12,
};

// 鼠标按键
enum class MouseButton : i32 {
    Left = 1,
    Middle = 2,
    Right = 3,
};

} // namespace pixel
