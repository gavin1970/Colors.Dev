// color_support.c
#include "color_support.h"
#include <objbase.h>            // For free

COLORS_DEV_API void FreeAllocPtr(void* p) { if(p)free(p); }