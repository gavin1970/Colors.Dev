// hsv_space.c
#include "hsv_space.h"
#include "common.h"             // For clampDbl
#include <math.h>               // For fmin, fmax, fabs, round, pow
#include <string.h>             // For strlen, strcpy_s
#include <stdio.h>              // Required for sprintf
#include <objbase.h>            // For malloc
// CIELAB, CIELCh, and CIELUV, and XYZ conversions.

static char* CreateBuffer(const char* str) {
    char retVal[25] = { 0 };

    snprintf(retVal, sizeof(retVal), str);

    size_t len = strlen(retVal) + 1;
    char* buffer = (char*)malloc(len);

    if (buffer)
        memcpy(buffer, retVal, len);

    return buffer;
}

COLORS_DEV_API RgbColor HsvToRgb(HsvSpace hsv)
{
    // Whole number
    double h = clampDbl(hsv.hue, 0.0, 360.0);
    // Convert 0-100.0 to 0.0-1.0
    double s = clampDbl(hsv.saturation, 0.0, 100.0) / 100.0;
    double v = clampDbl(hsv.value, 0.0, 100.0) / 100.0;
    double raw = hsv.raw_value;       //untouched

    // If raw values exists, they are more precise.
    if (raw > 0.0 && raw <= 1.0 && raw != v)
        v = raw;

    double r = 0.0, g = 0.0, b = 0.0;

    int i = (int)floor(h / 60.0) % 6;
    double f = (h / 60.0) - floor(h / 60.0);
    double p = v * (1.0 - s);
    double q = v * (1.0 - f * s);
    double t = v * (1.0 - (1.0 - f) * s);

    switch (i)
    {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
    }

    // Convert 0.0-1.0 back to 0-255
    RgbColor rgb = {
        (unsigned char)255.0,
        (unsigned char)round(r * 255.0),
        (unsigned char)round(g * 255.0),
        (unsigned char)round(b * 255.0)
    };
    return rgb;
}

COLORS_DEV_API HsvSpace RgbToHsv(RgbColor rgb)
{
    // Convert 0-255 to 0.0-1.0
    double r = clampDbl(rgb.red, 0.0, 255.0) / 255.0;
    double g = clampDbl(rgb.green, 0.0, 255.0) / 255.0;
    double b = clampDbl(rgb.blue, 0.0, 255.0) / 255.0;

    double min = fmin(fmin(r, g), b);
    double max = fmax(fmax(r, g), b);
    double delta = max - min;

    double h = 0.0;
    double s = 0.0;
    double v = max;     // Value is just the max component
    double raw = max;   // raw value, before conversion.  More precise when converting back to RGB.

    if (delta != 0.0)
    {
        s = (max == 0.0) ? 0.0 : (delta / max);

        if (r == max)
            h = (g - b) / delta;
        else if (g == max)
            h = 2.0 + (b - r) / delta;
        else // b == max
            h = 4.0 + (r - g) / delta;

        h *= 60.0; // convert to degrees
        if (h < 0.0)
            h += 360.0;
    }

    HsvSpace hsv = { h, s * 100.0, v * 100.0, raw };
    return hsv;
}

COLORS_DEV_API colors_dev_float64 GetHue(RgbColor rgb) {
    return RgbToHsv(rgb).hue;
}

COLORS_DEV_API colors_dev_float64 GetHsvSaturation(RgbColor rgb)
{
    return RgbToHsv(rgb).saturation;
}

COLORS_DEV_API colors_dev_float64 GetHsvBrightness(RgbColor rgb) {
	return RgbToHsv(rgb).raw_value;
}

COLORS_DEV_API char* GetTone(RgbColor clr) {
    HsvSpace hsv = RgbToHsv(clr);
    double h = hsv.hue;
    double v = hsv.value;
    double s = hsv.saturation;

    // NEUTRALS (Top priority for desaturated colors)
    if (s < 5.0 && v >= 95.0)  return CreateBuffer("Near White");
    if (s < 20.0 && v > 85.0) return CreateBuffer("Light Neutral");
    if (s < 20.0 && v > 55.0) return CreateBuffer("Mid Neutral");
    if (s < 20.0 && v > 20.0) return CreateBuffer("Dark Neutral");

    // VERY DARK (Value <= 20%) - Hue Weighted
    if (v <= 5.0)  return CreateBuffer("Black");
    if (v <= 10.0 && s < 20.0)  return CreateBuffer("Near Black");
    if (v <= 20.0) {
        double threshold = 20.0;
        if (h >= 45.0 && h <= 100.0) threshold = 25.0; // Yellow-Greens
        if (h >= 200.0 && h <= 280.0) threshold = 15.0; // Blues-Purples

        return (s <= threshold) ? CreateBuffer("Neutral") : CreateBuffer("Very Dark");
    }

    // BRIGHTNESS BLOCKS (Remaining colors have s >= 20.0)
    if (v > 85.0) {
        if (s > 75.0) return CreateBuffer("Vivid");
        if (s >= 20.0) return CreateBuffer("Pastel");
        return CreateBuffer("Bright");
    }

    if (v > 55.0) {
        if (s > 75.0) return CreateBuffer("Strong");
        if (s >= 20.0) return CreateBuffer("Moderate");
        return CreateBuffer("Muted Light");
    }

    // LOW BRIGHTNESS
    if (s > 60.0) return CreateBuffer("Deep");
    if (s >= 20.0) return CreateBuffer("Dull");

    return CreateBuffer("Washed Out"); // Accessible if top Neutral thresholds are ever adjusted
}