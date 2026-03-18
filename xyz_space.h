// xyz_conversions.h

#pragma once

#ifndef XYZ_CONVERSIONS_H
#define XYZ_CONVERSIONS_H

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

#include "import_exports.h"
#include "color_types.h"
#include "white_points.h"       // For white point definitions used in XYZ to Lab conversions.
#include <stdint.h>             // For uint32_t type

/// <summary>
/// Converts an RGB color to the Lab color space.<br/>
/// (Default: WP_D65_FULL white point is used for the conversion.)
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The color represented in Lab color space.</returns>
COLORS_DEV_API LabSpace RgbToLab(RgbColor rgb);
	
/// <summary>
/// Converts an RGB color to the CIE XYZ color space.
/// </summary>
/// <param name="rgb">The RGB color to convert.</param>
/// <returns>The color represented in the CIE XYZ color space.</returns>
COLORS_DEV_API XyzSpace RgbToXyz(RgbColor rgb);

/// <summary>
/// Converts a color from XYZ color space to Lab color space.<br/>
/// (Default: WP_D65_FULL white point is used for the conversion.)
/// </summary>
/// <param name="xyz">The color in XYZ color space to convert.</param>
/// <returns>The color converted to Lab color space.</returns>
COLORS_DEV_API LabSpace XyzToLab(XyzSpace xyz);

/// <summary>
/// Converts a color from XYZ color space to LAB color space using a specified white point.
/// </summary>
/// <param name="xyz">The color in XYZ color space to convert.</param>
/// <param name="wp">The white point type to use for the conversion.</param>
/// <returns>The color converted to LAB color space.</returns>
COLORS_DEV_API LabSpace XyzToLabEx(XyzSpace xyz, WhitePointType wp);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif