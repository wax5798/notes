# 基本语法规则
- 变量使用${ }方式取值
- command(arg1 arg2 ...) 指令参数使用括弧括起来，参数之间使用空格或分号分开
- 指令大小写无关，参数和变量是大小写相关的

# 一个简单的例子
我们先以一个简单的例子作为开始。这个例子中包含了大多数常用的指令。另外一些常用的指令会在后面做补充
## 目录结构
     
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
## 源码
### ./CMakeLists.txt 

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

*PROJECT(projectname [CXX] [C] [Java])*
> 定义工程名称，并指定工程支持的语言。
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

    add_subdirectory(src)
    add_subdirectory(lib)

### ./src/lib/CMakeLists.txt

    set(SRC_LIST hello.c)
    # set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/lib)
    # add_library(libhello ${SRC_LIST})
    add_definitions(-DLIBHELLO_BUILD)
    add_library(hello_shared SHARED ${SRC_LIST})
    set_target_properties(hello_shared PROPERTIES OUTPUT_NAME "hello")
    set_target_properties(hello_shared PROPERTIES VERSION 1.2 SOVERSION 1)

    add_library(hello_static STATIC ${SRC_LIST})
    set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")

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

    set(LIB_LIST hello.so)
    set(SRC_LIST main.c)
    # set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/bin)
    add_executable(hello ${SRC_LIST})
    target_link_libraries(hello ${LIB_LIST})

*ADD_EXECUTABLE(target source ...)*
> 生成一个名为 *target* 的可执行文件

*TARGET_LINK_LIBRARIES(dir1 dir2 ...)*
> 添加非标准的共享库搜索路径

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
在工程下创建build目录，进入build目录，运行 `cmake ../`，此时会在build目录下生成Makefile以及一些中间文件
如果需要看到make构建的详细过程，可以使用make VERBOSE=1 命令来进行构建
