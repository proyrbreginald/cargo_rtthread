# cargo_rtthread

基于 Meson 构建系统的 RT-Thread 项目。

## 快速开始

```bash
# 1. 配置（指定交叉编译文件）
meson setup build --cross-file cross_file.txt

# 2. 编译
meson compile -C build
```

---

## Meson 常用命令参考

### 项目配置

```bash
# 基本配置（生成 builddir）
meson setup build

# 指定交叉编译文件
meson setup build --cross-file cross_file.txt

# 指定原生编译文件（用于交叉编译中的构建机器工具）
meson setup build --native-file native_file.ini

# 重新配置（复用已有 builddir）
meson setup build --reconfigure

# 清除配置并重新生成
meson setup build --wipe

# 指定安装前缀
meson setup build --prefix=/usr/local

# 设置编译选项
meson setup build -Doption=value
meson setup build -Dbuildtype=debug     # debug, release, debugoptimized, minsize
```

### 编译与构建

```bash
# 编译（等同于 make/ninja）
meson compile -C build

# 指定编译目标（只编译某个可执行文件或库）
meson compile -C build executable_name

# 并行编译（-j 指定并行数）
meson compile -C build -j4

# 显示详细的编译命令
meson compile -C build -v

# 清理构建产物
meson compile -C build --clean
```

### 安装

```bash
# 安装到前缀目录
meson install -C build

# 安装到指定目录
meson install -C build --destdir /tmp/install
```

### 测试

```bash
# 运行所有测试
meson test -C build

# 运行特定测试
meson test -C build test_name

# 重复测试直到失败（找 flaky test）
meson test -C build --repeat=100

# 打印详细输出
meson test -C build -v
```

### 依赖与内省

```bash
# 列出所有依赖
meson introspect --dependencies build

# 查看项目选项及其默认值
meson introspect --projectinfo build

# 查看所有构建目标
meson introspect --targets build

# 查看构建选项
meson introspect --buildoptions build

# 查看安装路径
meson introspect --installdata build

# 查看依赖关系图（JSON）
meson introspect --scan-dependencies .
```

### 子项目与 Wrap

```bash
# 更新 wrap 依赖
meson wrap update

# 列出所有 wrap 包
meson wrap list

# 安装一个新的 wrap 包
meson wrap install <package_name>
```

### 其他实用命令

```bash
# 格式化 meson.build 文件
meson format -i src/meson.build

# 显示版本
meson --version

# 查看帮助
meson help
meson setup --help
meson compile --help
```

---

## 常用 Meson 选项 (`-D`)

| 选项 | 值示例 | 说明 |
|------|--------|------|
| `buildtype` | `debug` / `release` / `debugoptimized` / `minsize` | 构建类型 |
| `optimization` | `0` / `g` / `s` / `2` / `3` | 优化等级 |
| `debug` | `true` / `false` | 是否包含调试符号 |
| `b_lto` | `true` / `false` | 启用 LTO（链接时优化） |
| `b_pie` | `true` / `false` | 生成位置无关可执行文件 |
| `b_sanitize` | `address` / `undefined` / `thread` / `memory` | 启用 sanitizer |
| `warning_level` | `0` / `1` / `2` / `3` | 警告级别 |
| `c_std` | `gnu17` / `c11` / `c99` | C 语言标准 |
| `cpp_std` | `c++17` / `c++20` / `gnu++17` | C++ 语言标准 |
| `prefix` | `/usr` / `/usr/local` | 安装前缀 |

---

## 完整工作流示例

```bash
# 1. 配置
meson setup build --cross-file cross_file.txt -Dbuildtype=debug

# 2. 查看依赖
meson introspect --dependencies build

# 3. 编译
meson compile -C build

# 4. 查看目标信息
meson introspect --targets build

# 5. 清理并重新配置
meson setup build --wipe
meson setup build --cross-file cross_file.txt
```