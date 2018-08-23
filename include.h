#include <stdio.h>
#include <unistd.h>
#include <conio.h>
#include <string.h>

#define POKE(X,Y) (*(unsigned char*)(X))=Y
#define PEEK(X) (*(unsigned char*)(X))

#define MAX_NUMBER_CONTACTS     10
#define MAX_LENGTH_TITLE        20
#define MAX_LENGTH_PARAM_HEADER 10
#define MAX_NUMBER_PARAM_HEADER 4

/* Color defines */
#define COLOR_BLACK             0x00
#define COLOR_WHITE             0x01
#define COLOR_RED               0x02
#define COLOR_CYAN              0x03
#define COLOR_VIOLET            0x04
#define COLOR_GREEN             0x05
#define COLOR_BLUE              0x06
#define COLOR_YELLOW            0x07
#define COLOR_ORANGE            0x08
#define COLOR_BROWN             0x09
#define COLOR_LIGHTRED          0x0A
#define COLOR_GRAY1             0x0B
#define COLOR_GRAY2             0x0C
#define COLOR_LIGHTGREEN        0x0D
#define COLOR_LIGHTBLUE         0x0E
#define COLOR_GRAY3             0x0F

#define CORNER_TOP_LEFT         131
#define CORNER_TOP_RIGHT        132
#define CORNER_BOTTOM_LEFT      129
#define CORNER_BOTTOM_RIGHT     130
#define SEPARATOR_LEFT          134
#define SEPARATOR_RIGHT         135
#define VERTICAL                128
#define HORIZONTAL              133

/* Input keyboard */

#define SCREEN_HEIGHT           25
#define SCREEN_WIDTH            50

#define HEADER_HEIGHT           1
#define LEFT_COLUMN_WIDTH       21
#define RIGHT_COLUMN_WIDTH      28