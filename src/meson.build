# 进入子目录，获取依赖对象
subdir('cmsis')
subdir('driver')
subdir('config')
subdir('app')

# 添加依赖
src_dep = declare_dependency(
    dependencies : [cmsis_dep, driver_dep, config_dep, app_dep], # 传递依赖链
)