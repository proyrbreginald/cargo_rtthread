project('pdmcu', 'c', default_options : ['c_std=gnu17'])

# 进入 src 目录，执行其中的 meson.build
subdir('src')

# 声明编译器参数
common_c_args = [
    '-mcpu=cortex-m4',      # 替换为你的MCU核心，如 cortex-m3, cortex-m0plus
    '-mthumb',              # 使用Thumb指令集
    '-mfloat-abi=hard',     # 如果你的MCU有FPU，可改为 'hard'
    '-ffunction-sections',  # 优化，未使用的函数不链接
    '-fdata-sections',      # 优化，未使用的数据不链接
    '-Wall',                # 开启常用警告
    '-Wextra',              # 开启额外警告
    '-Os',                  # 优化代码体积
    '-g',                   # 保留调试信息
    '-Wno-main',            # 忽略 main 函数警告
]

common_link_args = [
    '-mcpu=cortex-m4',
    '-mthumb',
    '-mfloat-abi=hard',
    '-Wl,--gc-sections',            # 删除未使用的段
    '-Wl,-Map=output.map',          # 生成内存映射文件（相对 build 目录）
    '-Wl,--no-warn-rwx-segments',   # 裸机系统忽略 RWX 段警告（Cortex-M 无 MMU 强制执行）
    # '-nostartfiles',              # 不使用标准启动文件，使用自己的
]

# 声明可执行文件
executable('pdmcu',
    c_args : common_c_args,
    link_args : common_link_args,
    dependencies : src_dep, # 传递依赖链
)