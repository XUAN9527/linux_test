#[[这是一个 CMakeLists.txt 文件
这是一个 CMakeLists.txt 文件]]

cmake_minimum_required(VERSION 3.0)
project(test)
# 定义变量
# 静态库生成的路径
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 测试程序生成的路径
set(EXEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 头文件目录
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
# 静态库的名字
set(CALC_LIB calc)
set(SORT_LIB sort)
# 可执行程序的名字
set(APP_NAME_1 test1)
set(APP_NAME_2 test2)
# 添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)


#[[ 静态库方法
# 包含静态库路径,链接静态库
#link_directories(${PROJECT_SOURCE_DIR}/lib)
#link_libraries(calc)
add_executable(app ${SRC_LIST})
]]

#[[ 动态库方法
# 指定要链接的动态库的路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(app ${SRC_LIST})
# 指定要链接的动态库
target_link_libraries(app calc)
]]



