// main.h
#pragma once

// We include this here so that any .c file that includes main.h
// automatically gets the DLL functions, too. Good!
#include "ansi_printing.h"
#include "color_support.h"
#include "rgb_color.h"
#include "hsl_space.h"
#include "hsv_space.h"
#include "xyz_space.h"
#include "cmyk_space.h"
#include "lch_space.h"
#include "luv_space.h"

// --- DECLARATIONS ---
// We "declare" the variables with 'extern'.
// This tells the compiler these variables *exist*, but doesn't
// create them. This is just a "bookmark."
extern const RgbColor rgbRed;
extern const RgbColor rgbBlue;
extern const RgbColor rgbYellow;
extern const RgbColor rgbCyan;


