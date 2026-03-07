// color_support.h

#pragma once

#ifndef COLOR_SUPPORT_H
#define COLOR_SUPPORT_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"

/// <summary>
/// Frees memory that was previously allocated.
/// </summary>
/// <param name="p">Pointer to the memory block to free.</param>
/// <returns>This function does not return a value.</returns>
COLORS_DEV_API void FreeAllocPtr(void* p);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif