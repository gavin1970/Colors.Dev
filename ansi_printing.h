// ansi_printing.h

#pragma once

#ifndef ANSI_PRINTING_H
#define ANSI_PRINTING_H

#include "import_exports.h"
#include "color_types.h"

// --- Start of "extern C" block ---
#ifdef __cplusplus
extern "C" {
#endif

    /// <summary>
    /// For Console use only, this will set the foreground and background color to any 24bit color. 
    /// </summary>
    /// <param name="fg">RgbColor struct of foreground color</param>
    /// <param name="bg">RgbColor struct of background color</param>
    COLORS_DEV_API void SetColorsEx(RgbColor bg, RgbColor fg);

    /// <summary>
    /// For Console use only, this will set the foreground color to any 24bit color. 
    /// </summary>
    /// <param name="fg">RgbColor struct of foreground color</param>
    COLORS_DEV_API void SetFgColorEx(RgbColor fg);

    /// <summary>
    /// For Console use only, this will set the background color to any 24bit color. 
    /// </summary>
    /// <param name="bg">RgbColor struct of background color</param>
    COLORS_DEV_API void SetBgColorEx(RgbColor bg);

    /// <summary>
    /// For Console use only, this will set the foreground color to any 24bit color. 
    /// </summary>
    /// <param name="red">byte (0-255)</param>
    /// <param name="green">byte (0-255)</param>
    /// <param name="blue">byte (0-255)</param>
    COLORS_DEV_API void SetFgColor(unsigned char red, unsigned char green, unsigned char blue);

    /// <summary>
    /// For Console use only, this will set the background color to any 24bit color. 
    /// </summary>
    /// <param name="red">byte (0-255)</param>
    /// <param name="green">byte (0-255)</param>
    /// <param name="blue">byte (0-255)</param>
    COLORS_DEV_API void SetBgColor(unsigned char red, unsigned char green, unsigned char blue);

    /// <summary>
    /// For Console use only, this will reset both foreground and background color back to console's default colors.
    /// </summary>
    COLORS_DEV_API void ResetColor(void);

    /// <summary>
    /// For Console use only, this clears the full console buffer, back to a blank screen.
    /// </summary>
    COLORS_DEV_API void ClearBuffer(void);

    /// <summary>
	/// Gets the foreground color as a string representation.<br/>
    /// Requires FreeAllocPtr to be called on the returned string when done to avoid memory leaks.
    /// </summary>
    /// <param name="fg">The RGB color value for the foreground.</param>
    /// <returns>A pointer to a character string representing the foreground color.</returns>
    COLORS_DEV_API char* GetFgColor(RgbColor fg);

    /// <summary>
    /// Gets the background color as a string representation.<br/>
    /// Requires FreeAllocPtr to be called on the returned string when done to avoid memory leaks.
    /// </summary>
    /// <param name="bg">The RGB color value for the background.</param>
    /// <returns>A pointer to a character string representing the background color.</returns>
    COLORS_DEV_API char* GetBgColor(RgbColor bg);

// --- End of "extern C" block ---
#ifdef __cplusplus
}
#endif
#endif