#include <conio.h>      // _getch
#include <stdio.h>      // printf
#include <windows.h>    // FlushConsoleInputBuffer, GetStdHandle, STD_INPUT_HANDLE
#include "main.h"

// Stress Testing edge cases for rounding and precision, especially for LCH which can be more 
// lossy due to the polar to cartesian conversions.
const RgbColor rgbNearPureBlack = { 255, 1, 2, 3 };
const RgbColor rgbDeepNavy = { 255, 18, 52, 86 };
const RgbColor rgbNearPureWhite = { 255, 254, 253, 252 };
// Stress Testing LCH, which can be more lossy due to the polar to cartesian conversions, especially 
// around neutral grays where hue can flip and chroma is very low, which can cause rounding issues.
const RgbColor rgbGray = { 255, 127, 127, 127 };    //7F7F7F
const RgbColor rgbGray2 = { 255, 127, 127, 128 };   //7F7F80
const RgbColor rgbGray3 = { 255, 128, 128, 127 };   //80807F
const RgbColor rgbGray4 = { 255, 127, 128, 128 };   //7F8080
const RgbColor rgbGray5 = { 255, 128, 128, 128 };   //808080

// Common Colors for testing.
const RgbColor rgbRed = { 255, 255, 0, 0 };
const RgbColor rgbBlue = { 255, 0, 0, 255 };
const RgbColor rgbViolet = { 255, 127, 0, 255 };
const RgbColor rgbYellow = { 255, 255, 255, 0 };
const RgbColor rgbCyan = { 255, 0, 255, 255 };
const RgbColor rgbAshRose = { 255, 181, 129, 125 };
const RgbColor rgbBlack = { 255, 0, 0, 0 };
const RgbColor rgbWhite = { 255, 255, 255, 255 };
const WhitePointType d64_Full_Type = WPID_D65_FULL;
const WhitePointType d64_Type = WPID_D65;
const char* welcomeToDemo = " Welcome to the C Console Color Demo! ";

static void ColorConversionDemo(void);
static void ConsoleColorPrintDemo(void);
static void ShowColorInfo(RgbColor bgColor, RgbColor fgColor, char* title);
static void AnyKey(const char* msg, const RgbColor* fg);
static void FormatStringV(char* buffer, size_t size, const char* fmt, va_list args);
static void SetColors(const RgbColor* bg, const RgbColor* fg);
static void WriteLine(const RgbColor* bg, const RgbColor* fg, const char* msg, ...);
static void Write(const RgbColor* bg, const RgbColor* fg, const char* msg, ...);
static void PrintLine(const char* fmt, ...);
static void EnableVT(void);
static BOOL CreateHeader(void);

int main(void)
{
    EnableVT();
    AnyKey("This console buffer will be clear on any key being pressed.\n\nPress any key to clear...\n\n", &rgbCyan);
    ClearBuffer();

    if (!CreateHeader())
    {
		printf("Failed to create header.\n");
        return 1;
    }
    ConsoleColorPrintDemo();
    ColorConversionDemo();

    // with color, use NULL instead for no color.
    AnyKey("Press any key to exit...\n\n", &rgbRed);
    return 0;
}

static void SetColors(const RgbColor* bg, const RgbColor* fg) {
    if (fg != NULL && bg != NULL) SetColorsEx(*bg, *fg);
    else if (fg != NULL) SetFgColorEx(*fg);
    else if (bg != NULL) SetBgColorEx(*bg);
    else ResetColor();
}

/// <summary>
/// Does a dump of the bg color info for the provided color, 
/// including conversions to/from HSL and HSV, and hex formats.
/// </summary>
static void ColorConversionDemo(void)
{
    ShowColorInfo(rgbBlue, rgbWhite, "Blue - #0000FF");
    ShowColorInfo(rgbViolet, rgbWhite, "Violet - #7F00FF");
    ShowColorInfo(rgbCyan, rgbBlack, "Cyan - #00FFFF");
    ShowColorInfo(rgbAshRose, rgbWhite, "Ash Rose - #B5817D");

    /*  <- add forward slash ('//*') to uncomment group.
    
    // Stress Testing edge cases for rounding and precision, especially for LCH which can be more 
    // lossy due to the polar to cartesian conversions.
    ShowColorInfo(rgbNearPureBlack, rgbWhite, "Near Pure Black - #010203");
    ShowColorInfo(rgbDeepNavy, rgbWhite, "Deep Navy - #123456");
    ShowColorInfo(rgbNearPureWhite, rgbBlack, "Near Pure White - #FEFDFC");
    /**/

    /*  <- add forward slash ('//*') to uncomment group.

    // Stress Testing LCH
    ShowColorInfo(rgbGray, rgbBlack, "Gray - #7F7F7F");
    ShowColorInfo(rgbGray2, rgbBlack, "Gray - #7F7F80");
    ShowColorInfo(rgbGray3, rgbBlack, "Gray - #80807F");
    ShowColorInfo(rgbGray4, rgbBlack, "Gray - #7F8080");
    ShowColorInfo(rgbGray5, rgbBlack, "Gray - #808080");

    /**/

    AnyKey("\nPress any key to continue...", &rgbYellow);
}

/// <summary>
/// Does a dump of the bg color info for the provided color, including conversions to/from HSL and HSV, and hex formats.
/// </summary>
/// <param name="bgColor"></param>
/// <param name="fgColor"></param>
/// <param name="title"></param>
static void ShowColorInfo(RgbColor bgColor, RgbColor fgColor, char* title) {
    HsvSpace hsv = RgbToHsv(bgColor);
    HslSpace hsl = RgbToHsl(bgColor);
    XyzSpace xyz = RgbToXyz(bgColor);
	CmykSpace cmyk = RgbToCmyk(bgColor);
    LabSpace labFull = XyzToLabEx(xyz, d64_Full_Type);
    LabSpace lab64 = XyzToLabEx(xyz, d64_Type);
    LuvSpace luvFull = XyzToLuvEx(xyz, d64_Full_Type);
    LuvSpace luv64 = XyzToLuvEx(xyz, d64_Type);
    LchSpace lchFull = LabToLch(labFull);
    LchSpace lch64 = LabToLch(lab64);

    RgbColor hsv_rt = HsvToRgb(hsv);
    RgbColor hsl_rt = HslToRgb(hsl);
    RgbColor cmyk_rt = CmykToRgb(cmyk);

    char* ahex = RgbToRgbHex(bgColor, 1);
    char* hex = RgbToRgbHex(bgColor, 0);
    int aDec = RgbToArgbDec(bgColor);
    int dec = RgbToRgbDec(bgColor);

    SetColorsEx(bgColor, fgColor);
    
    PrintLine(" --- Testing %s Conversions --- ", title);
    PrintLine(" '%s' Color: (R:%u, G:%u, B:%u)", title, bgColor.red, bgColor.green, bgColor.blue);
	PrintLine("  - CMYK: C:%.2f, M:%.2f, Y:%.2f, K:%.2f, Raw:%f", cmyk.cyan, cmyk.magenta, cmyk.yellow, cmyk.key, cmyk.raw_key);
    PrintLine("  - HSL: H:%.2f, S:%.2f, L:%.2f, Raw:%f", hsl.hue, hsl.saturation, hsl.lightness, hsl.raw_lightness);
    PrintLine("  - HSV: H:%.2f, S:%.2f, V:%.2f, Raw:%f", hsv.hue, hsv.saturation, hsv.value, hsv.raw_value);
    PrintLine("  - XYZ: X:%.2f, Y:%.2f, Z:%.2f", xyz.x, xyz.y, xyz.z);
    PrintLine("  - LAB_64:   L:%.4f, A:%.4f, B:%.4f", lab64.l, lab64.a, lab64.b);
    PrintLine("  - LAB_FULL: L:%.4f, A:%.4f, B:%.4f", labFull.l, labFull.a, labFull.b);
    PrintLine("  - LUV_64:   L:%.4f, U:%.4f, V:%.4f", luv64.l, luv64.u, luv64.v);
    PrintLine("  - LUV_FULL: L:%.4f, U:%.4f, V:%.4f", luvFull.l, luvFull.u, luvFull.v);
    PrintLine("  - LCH_64:   L:%.4f, C:%.4f, H:%.4f", lch64.l, lch64.c, lch64.h);
    PrintLine("  - LCH_FULL: L:%.4f, C:%.4f, H:%.4f", lchFull.l, lchFull.c, lchFull.h);
    PrintLine("  - HEX8: %s (%i)", ahex, aDec);
    PrintLine("  - HEX6: %s (%i)", hex, dec);

    PrintLine("  - HSL Roundtrip -> RGB: (R:%u, G:%u, B:%u)", hsl_rt.red, hsl_rt.green, hsl_rt.blue);
    PrintLine("  - HSV Roundtrip -> RGB: (R:%u, G:%u, B:%u)", hsv_rt.red, hsv_rt.green, hsv_rt.blue);
	PrintLine("  - CMYK Roundtrip -> RGB: (R:%u, G:%u, B:%u)", cmyk_rt.red, cmyk_rt.green, cmyk_rt.blue);

    //PrintLine("  - LCH_64 raw C = %.17g\n", lch64.c);
    //PrintLine("  - LAB_64 raw a = %.17g, b = %.17g\n", lab64.a, lab64.b);

    ResetColor();

	FreeAllocPtr(ahex);
    FreeAllocPtr(hex);
}

static void ConsoleColorPrintDemo(void) {
    // Set no color.
    WriteLine(NULL, NULL, " - showing default color - ");
    // foreground color only.
    WriteLine(NULL, &rgbCyan, "Cyan text only.");
	// foreground color only.
    AnyKey("Press any key to continue...", &rgbYellow);
}

static void Write(const RgbColor *bg, const RgbColor *fg, const char* msg, ...) {
    if (msg == NULL)
        return;

    char buffer[256] = { 0 };
    size_t len = sizeof(buffer);

    va_list args;
    va_start(args, msg);
    FormatStringV(buffer, len, msg, args);
    va_end(args);

    SetColors(bg, fg);
    fwrite(buffer, 1, len, stdout);
    ResetColor();
}

static void WriteLine(const RgbColor* bg, const RgbColor* fg, const char* msg, ...) {
    if (msg == NULL)
        return;

    va_list args;
    va_start(args, msg);
    Write(bg, fg, msg, args);
    va_end(args);

    putchar('\n');
}

static void FormatStringV(char* buffer, size_t size, const char* fmt, va_list args) {
    vsnprintf(buffer, size, fmt, args);
}

static void AnyKey(const char* msg, const RgbColor* fg) {
    // Clear buffer.  
    // If this wasn't used, previous buffered input could 
    // force _getch() to continue without prompt.  
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    if (msg != NULL)
        WriteLine(NULL, fg, msg);

    int c = 0;
    // not sure why, F-Keys will throw a 0 first, but we want to ignore it.  
    // If we don't, F-Keys will cause the next prompt to be skipped.
	while (c == 0)  
        c = _getch();
}

/// <summary>
/// Setup Terminal type for this console.
/// </summary>
static void EnableVT(void)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return;

    if (!(mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING))
        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

static int ConsoleWidth(void)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return 120;
}

static int CursorX(void)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return 0;
}

static BOOL CreateHeader(void) {
    int num_spaces = (int)(ConsoleWidth() * 0.5) - (int)(strlen(welcomeToDemo) * 0.5);

    char* space_string = malloc(num_spaces + 1);
    if (space_string == NULL) {
        // Handle memory allocation failure
        perror("malloc failed");
        return FALSE;
    }
    else {
        memset(space_string, ' ', num_spaces);
        space_string[num_spaces] = '\0';
    }

    // Default background and foreground color.
    Write(NULL, NULL, space_string);
	// free from malloc
    free(space_string);

    // Set background and foreground color.
    WriteLine(&rgbRed, &rgbYellow, welcomeToDemo);

    return TRUE;
}

/// <summary>
/// This is specifically for bg colors that we want console width.
/// </summary>
static void PrintLine(const char* fmt, ...)
{
    char buf[1024];

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    // Strip trailing newline if caller included it
    size_t len = strlen(buf);
    while (len && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
        buf[--len] = '\0';
    }

    int width = ConsoleWidth();
    int x = CursorX();                 // where we are on the current line
    int remaining = width - x;         // cells left on this line

    // print text (truncate if it would wrap)
    int toWrite = (int)len;
    if (toWrite > remaining) toWrite = remaining;
    fwrite(buf, 1, (size_t)toWrite, stdout);

    // pad the rest of the *current* line only (no wrapping)
    int pad = remaining - toWrite;
    for (int i = 0; i < pad; i++) putchar(' ');

    putchar('\n');
}
