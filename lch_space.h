// lch_conversions.h

#pragma once

#ifndef LCH_CONVERSIONS_H
#define LCH_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "color_types.h"

/// <summary>
/// Converts an RGB color to the LCH (Lightness, Chroma, Hue) color space.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The color represented in the LCH color space.</returns>
COLORS_DEV_API LchSpace RgbToLch(RgbColor rgb);
/// <summary>
/// Converts a color from LAB color space to LCH color space.
/// </summary>
/// <param name="lab">The color in LAB color space to convert.</param>
/// <returns>The color converted to LCH color space.</returns>
COLORS_DEV_API LchSpace LabToLch(LabSpace lab);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif