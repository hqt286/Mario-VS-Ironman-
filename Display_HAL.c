#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
char o1,o2,o3,o4;
Graphics_Context g_sContext;
typedef enum {black, red, green, yellow, blue, magenta, cyan, white} color_t;



void InitGraphics() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
    GrContextFontSet(&g_sContext, &g_sFontCmtt16);
    Graphics_clearDisplay(&g_sContext);
}

void LCDClearDisplay(int color) {
    Graphics_setBackgroundColor(&g_sContext, color);
    Graphics_clearDisplay(&g_sContext);
}


void LCDDrawChar(unsigned row, unsigned col, int8_t c) {
    Graphics_drawString(&g_sContext,
                        &c,
                        1,
                        8 * (col % 16),
                        16 * (row % 8),
                        OPAQUE_TEXT);
}

void PrintString(char *str, int row, int col) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        LCDDrawChar(row,  col, str[i]);
        col++;
        if (col >= 16) {
            col = 0;
            row++;
            if (row >= 8) {
                row = 0;
            }
        }
    }
}

void LCDSetFgColor(color_t c) {
    switch (c)
       {
       case black:
           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
           break;
       case red:
           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
           break;
       case green:
           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
           break;
       case yellow:
           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
           break;
       case blue:
           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
           break;
       case magenta:
           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_MAGENTA);
           break;
       case cyan:
           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_CYAN);
           break;
       case white:
           Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
           break;
       }


}
// this function set the background color for any background input color.
void LCDSetBgColor(color_t c) {
    switch (c)
    {
    case black:
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        break;
    case red:
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_RED);
        break;
    case green:
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
        break;
    case yellow:
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_YELLOW);
        break;
    case blue:
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
        break;
    case magenta:
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_MAGENTA);
        break;
    case cyan:
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_CYAN);
        break;
    case white:
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        break;
    }
}

//-----------------------------------------------------------------------

