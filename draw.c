#include <conio.h>
#include "include.h"

/**
 *  @brief          draw a full rectangle which erase all char under its position
 *  @param  x       first x coordonate
 *  @param  y       first y coordonate
 *  @param  width   size of the rectangle, from x to x+width; width > 1
 *  @param  height  size of the rectangle, from y to y+height; height > 1
 *  @param  color   color of the border
 */
unsigned char rectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color)
{
    // Loop
    int i, j;

    // Initial position
    gotoxy(x,y);

    // Color
    textcolor(color);

    // Draw
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            // Corners
            if(i==0 && j==0)
            {
                cputc(CORNER_TOP_LEFT);
            }
            else if(i==height-1 && j==0)
            {
                cputc(CORNER_BOTTOM_LEFT);
            }
            else if(i==0 && j==width-1)
            {
                cputc(CORNER_TOP_RIGHT);
            }
            else if(i==height-1 && j==width-1)
            {
                cputc(CORNER_BOTTOM_RIGHT);
            }
            else if((i==0 || i==height-1) && j!=0 && j!=width-1)
            {
                // Top and bottom lines
                cputc(HORIZONTAL);
            }
            else if((j==0 || j==width-1) && i!=0 && i!=height-1)
            {
                // Left and right lines
                cputc(VERTICAL);
            }
            else
            {
                cputc(' ');
            }
        }
        gotoxy(x,y+i+1);
    }

    return 0;
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