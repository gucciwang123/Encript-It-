#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

#define _ENCODE_ 0
#define _DECODE_ 1

#ifdef BFE_debug
#define console(a) std::cout << a << std::endl
#define stop system("pause")
#endif
#ifdef BFE_release
#define console(a)
#define stop
#endif

