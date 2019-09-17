#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __builtin_trap();
#define glCall(x) clearError();x;ASSERT(checkError(#x, __FILE__, __LINE__));


void clearError();

bool checkError(const char* function, const char* file, int line);