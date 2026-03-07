// luv_conversions.h

#pragma once

#ifndef LUV_CONVERSIONS_H
#define LUV_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "color_types.h"
#include "white_points.h"       // For white point definitions used in XYZ to Lab conversions.


/// <summary>
/// Converts a color from XYZ color space to Luv color space.<br/>
/// (Default: WP_D65_FULL white point is used for the conversion.)
/// </summary>
/// <param name="rgb">The color in XYZ color space to convert.</param>
/// <returns>The color converted to Luv color space.</returns>
COLORS_DEV_API LuvSpace XyzToLuv(XyzSpace xyz);
/// <summary>
/// Converts a color from XYZ color space to Luv color space using a specified white point.
/// </summary>
/// <param name="xyz">The color in XYZ color space to convert.</param>
/// <param name="wp">The white point type to use for the conversion.</param>
/// <returns>The color converted to LUV color space.</returns>
COLORS_DEV_API LuvSpace XyzToLuvEx(XyzSpace xyz, WhitePointType wp);
/// <summary>
/// Converts an RGB color to the XYZ Space then to CIE Luv color space.<br/>
/// (Default: WP_D65_FULL white point is used between XYZ to Luv for this conversion.)
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The color represented in the CIE Luv color space.</returns>
COLORS_DEV_API LuvSpace RgbToLuv(RgbColor	rgb);


// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif