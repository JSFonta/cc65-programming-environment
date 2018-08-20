#include <conio.h>
#include "include.h"
#include "screen.h"
#include "memory.h"

/**
 *  @brief          draw a full rectangle which erase all char under its position
 *  @param  x       first x coordonate
 *  @param  y       first y coordonate
 *  @param  width   size of the rectangle, from x to x+width; width > 1
 *  @param  height  size of the rectangle, from y to y+height; height > 1
 *  @param  color   color of the border
 */
void rectangle(const unsigned char x, const unsigned char y, 
               const unsigned char width, const unsigned char height, 
               const unsigned char color)
{
    // Loop
    unsigned char i, j;

    unsigned int offset, scr_addr;
    unsigned long col_addr;

    // Dont allow x position or width > 127, so that arithmetic below cant overflow
    if ((x|width)&0x80) return;
    if ((y|height)&0x80) return;
    // Do simple bounds checks
    if (width>=SCREEN_COLS) return;
    if (height>=SCREEN_ROWS) return;
    if ((x+width)>=SCREEN_COLS) return;
    if ((y+height)>=SCREEN_ROWS) return;

    // Initial position
    offset=(y<<6);  // because screen lines take 64 bytes each
    offset+=x;

    scr_addr=SCREEN_ADDRESS+offset;
    col_addr=COLOUR_RAM_ADDRESS+offset;

    // Draw
        lfill(scr_addr,HORIZONTAL,width);
        POKE(scr_addr,CORNER_TOP_LEFT);
        POKE(scr_addr+width-1,CORNER_TOP_RIGHT);
        scr_addr+=64;

    for(i=2; i<height; i++)
    {
        lfill(scr_addr,0x20,width);
        POKE(scr_addr,VERTICAL);
        POKE(scr_addr+width-1,VERTICAL);
        scr_addr+=64;
    }

        lfill(scr_addr,HORIZONTAL,width);
        POKE(scr_addr,CORNER_BOTTOM_LEFT);
        POKE(scr_addr+width-1,CORNER_BOTTOM_RIGHT);
     
    return;
}

/**
 *  @brief          draw a full rectangle which erase all char under its position, with a center title
 *  @param  x       first x coordonate
 *  @param  y       first y coordonate
 *  @param  width   size of the rectangle, from x to x+width; width > 1
 *  @param  height  size of the rectangle, from y to y+height; height > 1
 *  @param  title   title at the top center, too long title will be cut
 */
unsigned char panel(unsigned char x, unsigned char y, unsigned char width, unsigned char height, char title[MAX_LENGTH_TITLE], unsigned char color)
{
    unsigned char titleLenght = 0;
    unsigned char i;

    // Draw a rectangle
    rectangle(x, y, width, height, color);

    // Center and write the title
    while(title[titleLenght] != '\0' && titleLenght < width)
    {
        titleLenght++;
    }
    gotoxy(x+(width-titleLenght+2)/2, y+1);
    i=0;
    while(i<width-2 && i<titleLenght)
    {
        cputc(title[i]);
        i++;
    }

    // Draw a line under the title
    gotoxy(x,y+2);
    cputc(SEPARATOR_LEFT);
    for(i=0; i<width-2; i++)
    {
        cputc(HORIZONTAL);
    }
    cputc(SEPARATOR_RIGHT);

    return 0;
}