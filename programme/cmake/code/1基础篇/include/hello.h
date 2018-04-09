/*************************************************************************
  > File Name: hello.h
  > Author: wan xiangjun
  > Mail: 
  > Created Time: 2017年07月06日 星期四 09时17分10秒
 ************************************************************************/

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
