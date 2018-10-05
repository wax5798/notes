最近看到好多开源项目的编译配置文件都是使用CMake写的，于是花些时间学习，并做备忘整理
这篇文档以一个简单的项目为例，对CMake的常用命令进行介绍
主要包括了包含头文件路径、生成库、生成二进制文件等功能。不包括安装、测试等功能

# 一些语法规则
- 变量使用 ${ } 方式取值
- 系统环境变量使用 $ENV{ } 方式取值
- command(arg1 arg2 ...) 指令参数使用括弧括起来，参数之间使用空格或分号分开
- 指令大小写无关，参数和变量是大小写相关的

# 一个简单的例子
## 目录结构
``` 
.
├── CMakeLists.txt
├── include
│   └── hello.h
└── src
    ├── CMakeLists.txt
    ├── lib
    │   ├── CMakeLists.txt
    │   └── hello.c
    └── src
        ├── CMakeLists.txt
        └── main.c
```
## 源码
### ./CMakeLists.txt 
```
cmake_minimum_required(VERSION 3.9)

project(HELLO)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIBRARY_DIR ${PROJECT_BINARY_DIR}/output/libs)
set(BIN_DIR ${PROJECT_BINARY_DIR}/output/bin)

include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY_DIR})

MESSAGE(STATUS "##PROJECT_SOURCE_DIR is " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "##PROJECT_BINARY_DIR is " ${PROJECT_BINARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
set(LIBRARY_OUTPUT_PATH ${LIBRARY_DIR})

add_subdirectory(src)
```

*CMAKE_MINIMUM_REQUIRED(VERSION version [FATAL_ERROR])*
> 指定此CMakefiles.txt支持的最小CMake版本
> 这条指令建议添加到顶层的CMakefiles.txt中

*PROJECT(projectname [CXX] [C] [Java])*
> 定义工程名称，如果名称中有空格，需要使用引号括起来
> 如果需要还可以指定工程支持的语言。
> 这个指令隐式定义了两个cmake变量： `<projectname>_BINARY_DIR`以及`<projectname>_SOURCE_DIR`，前者指向编译路径，后者为工程路径
> 同时cmake系统预定义了`PROJECT_BINARY_DIR`和`PROJECT_SOURCE_DIR`变量，分别与`<projectname>_BINARY_DIR`与`<projectname>_SOURCE_DIR`一致

*SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])*
> 设置变量

*INCLUDE_DIRECTORIES([AFTER|BEFORE] [SYSTEM] dir1 dir2 ...)*
> 添加头文件搜索路径。路径之间使用空格分隔。如果路径中包含空格，可使用双引号括起来
> 可以通过AFTER或者BEFORE参数，来控制添加的路径在已有路径的前面还是后面

*LINK_DIRECTORIES(dir1 dir2 ...)*
> 添加非标准的共享库搜索路径

*MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)*
> 向终端输出信息。
> `SEND_ERROR`产生错误，生成过程被跳过; `STATUS`输出前缀为-的信息; `FATAL_ERROR`立即终止所有cmake过程

*EXECUTABLE_OUTPUT_PATH*和*LIBRARY_OUTPUT_PATH*
> 指定最终生成的二进制文件存放的位置(不包含中间文件)

*ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])*
> 向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制文件存放位置
> `EXCLUDE_FROM_ALL` 参数含义是将这个目录从编译过程中排除

### ./src/CMakeLists.txt
```
add_subdirectory(src)
add_subdirectory(lib)
```

### ./src/lib/CMakeLists.txt
```
set(SRC_LIST hello.c)
# set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/lib)
# add_library(libhello ${SRC_LIST})
add_definitions(-DLIBHELLO_BUILD)
add_library(hello_shared SHARED ${SRC_LIST})
set_target_properties(hello_shared PROPERTIES OUTPUT_NAME "hello")
set_target_properties(hello_shared PROPERTIES VERSION 1.2 SOVERSION 1)

add_library(hello_static STATIC ${SRC_LIST})
set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")
```

*ADD_DEFINITIONS(-Ddef1 -Ddef2 ...)*
> 向C/C++编译器添加编译参数, 参数之间用空格分隔
> 也可以使用 *CMAKE_C_FLAGS* 或 *CMAKE_CXX_FLAGS* 为 C/C++ 设置编译选项

*ADD_LIBRARY(libname [SHARED|STATIC|MODULE] [EXCLUDE_FROM_ALL] source1 source2 ... sourceN)*
> 生成一个库文件
> 在不支持dyld的系统中，MODULE被当作SHARED对待

*SET_TARGET_PROPERTIES(target1 target2 ... PROPERTIES prop1 value1 prop2 value2 ...)*
> 用来设置输出的名称，对于动态库，还可以用来指定动态库版本或API版本
> 它对应的指令是: *GET_TARGET_PROPERTY(VAR target property)*

### ./src/src/CMakeLists.txt
``` 
set(LIB_LIST hello.so)
set(SRC_LIST main.c)
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/bin)
add_executable(hello ${SRC_LIST})
target_link_libraries(hello ${LIB_LIST})
```

*ADD_EXECUTABLE(target source ...)*
> 生成一个名为 *target* 的可执行文件
> CMake会自动处理依赖关系，所以source中不需要列出头文件
> PS: CMake是根据同名来查询头文件的？如果这样，非同名头文件是否应该被添加到source？

*TARGET_LINK_LIBRARIES(target library...)*
> 给target指定一个或多个链接库。
> 如果target是一个可执行目标，则它会与这些库链接
> 如果target是一个库，则它与其他库的依赖关系会被记录下来。当其他目标需要链接到这个target时，以来关系会被解析

### ./include/hello.h

``` c
#ifndef _HELLO_H
#define _HELLO_H

#if defined _WIN32
    #if LIBHELLO_BUILD
        #define LIBHELLO_API __declspec(dllexport)
    #else
        #define LIBHELLO_API __declspec(dllimport)
    #endif
#else
    #define LIBHELLO_API
#endif
LIBHELLO_API void hello();

#endif
```

### ./src/lib/hello.c
``` c
#include <stdio.h>
#include <stdlib.h>

void hello()
{
    printf("hello\n");
}
```


### ./src/src/main.c
``` c
#include <stdio.h>
#include <stdlib.h>

#include "hello.h"

int main(int argc, char *argv[])
{
    hello();

    return 0;
}
```

## 构建工程
构建命令 `# cmake -G <generator name> <path-to-source>`
> `-G <generator name>`告诉CMake应该产生什么类型的项目文件

注意事项
> 在工程下创建build目录，进入build目录，运行 `cmake -G "Unix Makefiles" ../`，此时会在build目录下生成Makefile以及一些中间文件
> 切忌在工程目录下执行`cmake -G "Unix Makefiles" ./`，因为这样会在工程目录下生成Makefile和一些中间文件，这些文件不能通过命令清理
> 如果需要看到make的详细过程，可以使用make VERBOSE=1 命令来进行编译


