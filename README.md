# Bee2D Game Engine

Bee2D 是一个基于 SDL 和 Lua 的轻量级游戏引擎框架，为开发者提供简单易用的游戏开发接口。它封装了图形渲染、窗口管理和事件处理等核心功能，通过 Lua 脚本驱动游戏逻辑。

## 核心特性

- **Lua 脚本驱动**：使用 Lua 脚本定义游戏行为
- **事件回调系统**：
  - `bee.load()` - 初始化游戏资源
  - `bee.update(dt)` - 游戏逻辑更新
  - `bee.draw()` - 渲染游戏画面
  - 键盘事件 (`keydown`, `keyup`)
  - 鼠标事件 (`mousedown`, `mouseup`, `mousemove`)
- **2D 图形绘制**：
  - 点、线、矩形（空心/填充）
  - 圆形（空心/填充）
  - 颜色控制（前景色/背景色）
- **窗口管理**：
  - 获取/设置窗口尺寸
  - 固定帧率渲染（默认 60 FPS）

## 快速开始

1. **安装依赖**：
```bash
# Ubuntu/Debian
sudo apt install libsdl2-dev liblua5.3-dev

# macOS (Homebrew)
brew install sdl2 lua
```

2. **编译引擎**：
```bash
gcc main.c bee.c -o game -lSDL2 -llua
```

3. **创建 Lua 脚本 (main.lua)**：
```lua
function bee.load()
    bee.graphics.setBackgroundColor(40, 40, 60)
end

function bee.update(dt)
    -- 更新游戏逻辑
end

function bee.draw()
    bee.graphics.setColor(255, 200, 50)
    bee.graphics.circle(400, 300, 100, "fill")
end
```

4. **运行游戏**：
```bash
./game
```

## API 参考

### 图形绘制
```lua
-- 设置前景色 (RGB/A)
bee.graphics.setColor(r, g, b [, a])

-- 设置背景色
bee.graphics.setBackgroundColor(r, g, b [, a])

-- 绘制点
bee.graphics.point(x, y)

-- 绘制线
bee.graphics.line(x1, y1, x2, y2)

-- 绘制矩形 (mode: "line" 或 "fill")
bee.graphics.rect(x, y, width, height [, mode])

-- 绘制圆形
bee.graphics.circle(x, y, radius [, mode])
```

### 窗口管理
```lua
-- 获取窗口尺寸
width, height = bee.window.getSize()

-- 设置窗口尺寸
bee.window.setSize(width, height)
```

### 输入事件
```lua
-- 键盘按下
function bee.keydown(scancode)
    -- scancode 对应 SDL 键值
end

-- 鼠标移动
function bee.mousemove(x, y, button)
    -- button: 1(左), 2(中), 3(右)
end
```

## 项目结构
```
├── bee.h          # 引擎头文件
├── bee.c          # 引擎核心实现
├── main.c         # 程序入口
└── main.lua       # 游戏脚本示例
```

## 示例应用

创建简单的点击生成圆效果：
```lua
local circles = {}

function bee.mousedown(x, y, button)
    if button == 1 then  -- 左键
        table.insert(circles, {x = x, y = y, r = 0})
    end
end

function bee.update(dt)
    for _, circle in ipairs(circles) do
        circle.r = circle.r + 100 * dt
    end
end

function bee.draw()
    bee.graphics.setColor(120, 220, 120)
    for _, circle in ipairs(circles) do
        bee.graphics.circle(circle.x, circle.y, circle.r, "line")
    end
end
```

## 贡献指南

欢迎提交 Issue 和 Pull Request！请确保：
- 代码符合现有风格
- 新增功能提供测试用例
- 文档保持同步更新