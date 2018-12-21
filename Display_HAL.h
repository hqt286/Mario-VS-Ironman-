//------------------------------------------
// DISPLAY API (Application Programming Interface)
// Also known as DISPLAY HAL (Hardware Abstraction Layer)
// HAL is a specific form of API that designs the interface with a certain hardware

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <ti/grlib/grlib.h>

typedef enum {black, red, green, yellow, blue, magenta, cyan, white} color_t;
#define MY_BLACK GRAPHICS_COLOR_BLACK
#define MY_WHITE GRAPHICS_COLOR_WHITE
#define MY_BLUE GRAPHICS_COLOR_BLUE
#define MY_YELLOW GRAPHICS_COLOR_YELLOW



void InitGraphics();
void LCDClearDisplay(int color);
void LCDDrawChar(unsigned row, unsigned col, int8_t c);
void PrintString(char *str, int row, int col);





#endif /* DISPLAY_H_ */
