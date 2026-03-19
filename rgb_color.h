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
COLORS_DEV_API colors_dev_color32 RgbToRgbDec(RgbColor rgb);

/// <summary>
/// Converts an RGB color to a 32-bit ARGB color with full opacity.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>A 32-bit ARGB color value with the alpha channel set to fully opaque.</returns>
COLORS_DEV_API colors_dev_color32 RgbToArgbDec(RgbColor rgb);

/// <summary>
/// Converts an RGB color to linear color space.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The color converted to linear color space as a 32-bit color value.</returns>
COLORS_DEV_API LinearColor RgbToLinear(RgbColor clr);

/// <summary>
/// Converts a linear color to an RGB color.
/// </summary>
/// <param name="lClr">The linear color to convert.</param>
/// <returns>The converted RGB color.</returns>
COLORS_DEV_API RgbColor LinearToRgb(LinearColor lClr);

/// <summary>
/// Converts a color value from sRGB color space to linear color space.
/// </summary>
/// <param name="srgb">The color value in sRGB color space to convert.</param>
/// <returns>The converted color value in linear color space.</returns>
COLORS_DEV_API colors_dev_float64 SrgbToLinear(colors_dev_float64 srgb);

/// <summary>
/// Converts a color value from linear color space to sRGB color space.
/// </summary>
/// <param name="linear">The color value in linear color space to convert.</param>
/// <returns>The color value converted to sRGB color space.</returns>
COLORS_DEV_API colors_dev_float64 LinearToSrgb(colors_dev_float64 linear);


// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif