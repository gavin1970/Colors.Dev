// hsl_space.h

#pragma once

#ifndef HSL_SPACE_H
#define HSL_SPACE_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "color_types.h"

/// <summary>
/// Converts an RGB color to its HSL (Hue, Saturation, Lightness) equivalent.
/// </summary>
/// <param name="rgb">RGB Color</param>
/// <returns>HSL struct</returns>
COLORS_DEV_API HslSpace RgbToHsl(RgbColor rgb);

/// <summary>
/// Converts HSL to RGB Color.  -- NOTICE: There are 16,777,216 colors and only 3,600,000 HSL possible values.  
/// This means HSL to RGB will only convert to one of it's possible colors and will not convert to them all.
/// </summary>
/// <param name="hsv">HSV struct</param>
/// <returns>RGB Color</returns>
COLORS_DEV_API RgbColor HslToRgb(HslSpace hsl);

/// <summary>
/// Gets the lightness component from an RGB color converted to HSL color space.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The lightness value in the HSL representation, typically in the range [0.0, 1.0].</returns>
COLORS_DEV_API colors_dev_float64 GetHslLightness(RgbColor rgb);

/// <summary>
/// Gets the saturation component from an RGB color converted to HSL color space.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The saturation component in HSL color space as a 64-bit floating point value.</returns>
COLORS_DEV_API colors_dev_float64 GetHslSaturation(RgbColor rgb);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif