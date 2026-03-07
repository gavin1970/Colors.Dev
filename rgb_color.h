// rgb_color.h

#pragma once

#ifndef RGB_COLOR_H
#define RGB_COLOR_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "color_types.h"
#include <stdint.h>             // For uint32_t type

typedef uint32_t colors_dev_color32;

/// <summary>
/// Converts an RGB color to its hexadecimal string representation.
/// </summary>
/// <param name="clr">The RGB color to convert.</param>
/// <param name="includeAlpha">Flag indicating whether to include the alpha channel in the output (non-zero to include, zero to exclude).</param>
/// <returns>A pointer to a null-terminated string containing the hexadecimal representation of the RGB color. The caller is responsible for managing the memory of the returned string.</returns>
COLORS_DEV_API char* RgbToRgbHex(RgbColor clr, unsigned int includeAlpha);

/// <summary>
/// Converts an RGB color to a 32-bit RGBA color value in decimal format.
/// </summary>
/// <param name="clr">The RGB color to convert.</param>
/// <returns>A 32-bit RGBA color value representing the input RGB color.</returns>
COLORS_DEV_API colors_dev_color32 RgbToRgbDec(RgbColor clr);

/// <summary>
/// Converts an RGB color to a 32-bit ARGB color with full opacity.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>A 32-bit ARGB color value with the alpha channel set to fully opaque.</returns>
COLORS_DEV_API colors_dev_color32 RgbToArgbDec(RgbColor rgb);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif