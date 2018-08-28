#include "draw.h"
#include "screen.h"
#include "memory.h"
#include "ascii.h"

void clearScreen(void)
{
    unsigned long i;

    for(i=0; i<SCREEN_COLS*SCREEN_ROWS; i++)
    {
        POKE(SCREEN_ADDRESS+i, ' ');
    }
    return;
}

void displayText(char * text, unsigned long startPosition, unsigned char color)
{
    unsigned short i=0;

    while(text[i] != '\0' && i < 1000)
    {
        // Color
        lfill(COLOUR_RAM_ADDRESS+startPosition+i, color, 1);

        // Text
        POKE(SCREEN_ADDRESS+startPosition+i, text[i]);
        i++;
    }

    return;
}

/**
 *  @brief          This function write on the screen the full layout of the app
 *  @author         Jean-Sebastien FONTA
 *  @date           14/08/2018
 *  @param  screen  the number of the screen to draw :
 *                  1 = main menu
 *                  2 = call
 *                  3 = sms
 *                  4 = add contact
 *  @return         code which indicate the state : -1 if error, 0 or higher if it is ok
 */
void layout(unsigned char screen)
{

    // Loop var
    unsigned char i, j;

    // Incoming call (0) or outgoing call (1)
    unsigned char callType = 0;

    // Coordinate var
    unsigned char numberx, numbery, offsetx;

    char toDisplay[15][4] = {"1", "2", "3",
                             "4", "5", "6",
                             "7", "8", "9",
                             "#", "0", "*",
                             "Add", "Cal", "Clr"};

    // Clear the display
    clearScreen();

    switch(screen)
    {
        case 1: // Main screen

            // Display number composition
            rectangle(0, HEADER_HEIGHT, LEFT_COLUMN_WIDTH, 3, COLOR_BLUE);

            // Display keyboard
            for(i=0; i<15; i++)
            {
                if(i/3 == 0)
                {
                    numbery = 4;
                }
                else if(i/3 == 1)
                {
                    numbery = 9;
                }
                else if(i/3 == 2)
                {
                    numbery = 14;
                }
                else if(i/3 == 3)
                {
                    numbery = 19;
                }
                else
                {
                    numbery = 24;
                }

                numberx = (i%3)*7;

                // Draw rectangle
                if(toDisplay[i][0] >= '0' && toDisplay[i][0] <= '9' || toDisplay[i][0] == '*' || toDisplay[i][0] == '#')
                {
                    rectangle(numberx, numbery, 7, 5, COLOR_BLUE);
                }
                else if(toDisplay[i][0] == 'A')
                {
                    rectangle(numberx, numbery, 7, 5, COLOR_YELLOW);
                }
                else if(toDisplay[i][0] == 'C' && toDisplay[i][1] == 'a')
                {
                    rectangle(numberx, numbery, 7, 5, COLOR_GREEN);
                }
                else
                {
                    rectangle(numberx, numbery, 7, 5, COLOR_RED);
                }

                // display text
                j = 0;
                while(toDisplay[i][j] != '\0')
                {
                    // Center
                    if(toDisplay[i][0] >= '0' && toDisplay[i][0] <= '9' || toDisplay[i][0] == '*' || toDisplay[i][0] == '#')
                    {
                        offsetx = 2;
                    }
                    else
                    {
                        offsetx = 1;
                    }
                    POKE(SCREEN_ADDRESS+(numberx+j+offsetx+1)+64*(numbery+2), toDisplay[i][j]);
                    lfill(COLOUR_RAM_ADDRESS+(numberx+j+offsetx+1)+64*(numbery+2), COLOR_WHITE, 1);
                    
                    j++;
                }

            }

            // Display contacts section into the right column
            panel(SCREEN_WIDTH-RIGHT_COLUMN_WIDTH, HEADER_HEIGHT, RIGHT_COLUMN_WIDTH, SCREEN_HEIGHT-HEADER_HEIGHT-1, "Contacts", COLOR_GRAY3);

            break;

        case 2: // Call
            
            // Outgoing call
            callType = 1;

            // Draw panel
            panel(0, HEADER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT-HEADER_HEIGHT-1, callType ? "Outgoing call" : "Incoming call", COLOR_GRAY3);

            // Draw button to end the call
            rectangle(10, SCREEN_HEIGHT-8, SCREEN_WIDTH-20, 5, COLOR_RED);
            // Text into the end button
            displayText("End", 64*(SCREEN_HEIGHT-6)+SCREEN_WIDTH-26, COLOR_WHITE);

            break;

        case 3: // SMS
                
            // Conversation
            panel(0, HEADER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT-HEADER_HEIGHT-1, "SMS", COLOR_GRAY3);

            // Text typing
            // Draw a gray3 line under the conversation
            lfill(COLOUR_RAM_ADDRESS+(SCREEN_HEIGHT-4)*SCREEN_COLS, COLOR_GRAY3, SCREEN_WIDTH);
            lfill(SCREEN_ADDRESS+(SCREEN_HEIGHT-4)*SCREEN_COLS+1, HORIZONTAL, SCREEN_WIDTH-2);
            POKE(SCREEN_ADDRESS+(SCREEN_HEIGHT-4)*SCREEN_COLS, SEPARATOR_LEFT);
            POKE(SCREEN_ADDRESS+(SCREEN_HEIGHT-4)*SCREEN_COLS+SCREEN_WIDTH-1, SEPARATOR_RIGHT);

            // Send text in blue
            displayText("Send", (SCREEN_HEIGHT-3)*SCREEN_COLS+SCREEN_WIDTH-5, COLOR_WHITE);

            break;

        case 4: // Add contact
                
            panel(0, HEADER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT-HEADER_HEIGHT-1, "Add/Edit contact", COLOR_GRAY3);

            // Print fields
            displayText("Name", SCREEN_COLS*(HEADER_HEIGHT+4)+1, COLOR_GRAY3);
            displayText("Phone", SCREEN_COLS*(HEADER_HEIGHT+8)+1, COLOR_GRAY3);
            displayText("Mail", SCREEN_COLS*(HEADER_HEIGHT+12)+1, COLOR_GRAY3);

            // Print buttons
            rectangle(1, SCREEN_HEIGHT-7, (SCREEN_WIDTH-1)/2, 5, COLOR_GREEN);
            displayText("Confirm", (((SCREEN_WIDTH-1)/2)/2-2)+SCREEN_COLS*(SCREEN_HEIGHT-5), COLOR_WHITE);

            rectangle(SCREEN_WIDTH-1-((SCREEN_WIDTH-1)/2), SCREEN_HEIGHT-7, (SCREEN_WIDTH-1)/2, 5, COLOR_RED);
            displayText("Delete", (SCREEN_WIDTH-SCREEN_WIDTH/4-4)+SCREEN_COLS*(SCREEN_HEIGHT-5), COLOR_WHITE);

            break;

        default:
            break;

    }

    return;
}