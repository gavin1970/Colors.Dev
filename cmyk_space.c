// cmyk_conversions.c
#include "cmyk_space.h"
#include "common.h"             // For clampInt, clampDbl
#include <string.h>             // For strlen, strcpy_s
#include <math.h>               // For fmin, fmax, fabs, round, pow

COLORS_DEV_API CmykSpace RgbToCmyk(RgbColor rgb)
{
    double r = rgb.red / 255.0;
    double g = rgb.green / 255.0;
    double b = rgb.blue / 255.0;

    double rawK = 1.0 - fmax(r, fmax(g, b));
    double c = 0, m = 0, y = 0;

    //can not divid by 0, so zero it all out.
    if ((1.0 - rawK) > 1e-12)
    {
        c = (1.0 - r - rawK) / (1.0 - rawK);
        m = (1.0 - g - rawK) / (1.0 - rawK);
        y = (1.0 - b - rawK) / (1.0 - rawK);

        // clamp for safety vs tiny negatives from floating point
        c = fmax(0.0, fmin(1.0, c));
        m = fmax(0.0, fmin(1.0, m));
        y = fmax(0.0, fmin(1.0, y));
    }

	// Convert to 0-100.0 range for CMYK struct, but keep rawK in 0.0-1.0 for better accuracy when converting back to RGB.
    CmykSpace cmyk = {
        c * 100, 
        m * 100, 
        y * 100, 
        rawK * 100,
        rawK 
    };
    return cmyk;
}

COLORS_DEV_API RgbColor CmykToRgb(CmykSpace cmyk)
{
    double c = clampDbl(cmyk.cyan / 100.0, 0.0, 1.0);
    double m = clampDbl(cmyk.magenta / 100.0, 0.0, 1.0);
    double y = clampDbl(cmyk.yellow / 100.0, 0.0, 1.0);

    double k = (cmyk.raw_key >= 0.0 && cmyk.raw_key <= 1.0)
        ? cmyk.raw_key
        : clampDbl(cmyk.key / 100.0, 0.0, 1.0);

    // Convert CMYK to RGB
    int r = (int)lround(255.0 * (1.0 - c) * (1.0 - k));
    int g = (int)lround(255.0 * (1.0 - m) * (1.0 - k));
    int b = (int)lround(255.0 * (1.0 - y) * (1.0 - k));

    // Ensure RGB values are within the valid range [0, 255]
    r = clampInt(r, 0, 255);
    g = clampInt(g, 0, 255);
    b = clampInt(b, 0, 255);

	RgbColor rgb = { 
        255, 
        (unsigned char)r, 
        (unsigned char)g, 
        (unsigned char)b 
    };
    return rgb;
}

