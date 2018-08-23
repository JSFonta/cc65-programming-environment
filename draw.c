#include "include.h"
#include "screen.h"
#include "memory.h"
#include "ascii.h"

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

    // Set color
    lfill(col_addr, color, width);

    // Goto next line
    scr_addr+=64;
    col_addr+=64;

    for(i=2; i<height; i++)
    {
        lfill(scr_addr,0x20,width);
        POKE(scr_addr,VERTICAL);
        POKE(scr_addr+width-1,VERTICAL);

        // Set color
        lfill(col_addr, color, 1);
        lfill(col_addr+width-1, color, 1);

        // Goto next line
        scr_addr+=64;
        col_addr+=64;
    }

        lfill(scr_addr,HORIZONTAL,width);
        POKE(scr_addr,CORNER_BOTTOM_LEFT);
        POKE(scr_addr+width-1,CORNER_BOTTOM_RIGHT);

        // Set color
        lfill(col_addr, color, width);
     
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
void panel(unsigned char x, unsigned char y, unsigned char width,
           unsigned char height, char title[MAX_LENGTH_TITLE], 
           unsigned char color)
{
    unsigned char titleLenght = 0;
    unsigned char i;
    unsigned char firstCharPosition;

    // Dont allow x position or width > 127, so that arithmetic below cant overflow
    if ((x|width)&0x80) return;
    if ((y|height)&0x80) return;
    // Do simple bounds checks
    if (width>=SCREEN_COLS) return;
    if (height>=SCREEN_ROWS) return;
    if ((x+width)>=SCREEN_COLS) return;
    if ((y+height)>=SCREEN_ROWS) return;

    // Draw a rectangle
    rectangle(x, y, width, height, color);

    // Center and write the title
    while(title[titleLenght] != '\0' && titleLenght < width)
    {
        titleLenght++;
    }
    firstCharPosition = x+(width-titleLenght+1)/2;
    i=0;

    // Set text colour
    lfill(COLOUR_RAM_ADDRESS+firstCharPosition+(y+1)*64, COLOR_WHITE, titleLenght);

    // Write the title
    for(i=0; i<titleLenght; i++)
    {
        POKE(SCREEN_ADDRESS+i+firstCharPosition+(y+1)*64, *(title+i));
    }

    // Draw a line under the title
    lfill(SCREEN_ADDRESS+(y+2)*64+x+1, HORIZONTAL, width-2);
    POKE(SCREEN_ADDRESS+(y+2)*64+x, SEPARATOR_LEFT);
    POKE(SCREEN_ADDRESS+(y+2)*64+x+width-1, SEPARATOR_RIGHT);

    // Set the color of the line
    lfill(COLOUR_RAM_ADDRESS+(y+2)*64+x, color, width);


    return;

}