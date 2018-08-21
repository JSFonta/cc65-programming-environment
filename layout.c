#include <conio.h>
#include "draw.h"
#include "screen.h"
#include "memory.h"

unsigned char clearNumero(void)
{
    gotoxy(1,3);

    printf("              ");

    return 0;
}

/**
 *  @brief          This function write on the screen the full layout of the app
 *  @author         Jean-Sebastien FONTA
 *  @date           14/08/2018
 *  @param  screen  the number of the screen to draw :
 *                  1 = main menu
 *                  2 = Call
 *                  3 = sms
 *                  4 = add contact
 *  @return         code which indicate the state : -1 if error, 0 or higher if it is ok
 */
unsigned char layout(unsigned char screen)
{

    // Loop var
    unsigned char i;

    // Coordinate var
    unsigned char numberx, numbery;

    switch(screen)
    {
        case 1: // Main screen

            // Display contacts section into the right column
            panel(SCREEN_WIDTH-RIGHT_COLUMN_WIDTH, HEADER_HEIGHT, RIGHT_COLUMN_WIDTH, SCREEN_HEIGHT-HEADER_HEIGHT, "Contacts", COLOR_GRAY3);

            // Display number composition
            rectangle(0, HEADER_HEIGHT, LEFT_COLUMN_WIDTH, 3, COLOR_BLUE);

            // Display numbers
            for(i=0; i<9; i++)
            {
                if(i/3 == 0)
                {
                    numbery = 5;
                }
                else if(i/3 == 1)
                {
                    numbery = 10;
                }
                else
                {
                    numbery = 15;
                }

                numberx = (i%3)*5;

                rectangle(numberx, numbery, 5, 5, COLOR_BLUE);
                POKE(SCREEN_ADDRESS+(numberx+2)+64*(numbery+2), i+1+48);
                lfill(COLOUR_RAM_ADDRESS+(numberx+2)+64*(numbery+2), COLOR_WHITE, 1);
            }
            /*
            // Display 0, #, *
            rectangle(15, 5, 5, 5, COLOR_BLUE);
            gotoxy(17,7);
            textcolor(COLOR_WHITE);
            printf("#");

            rectangle(15, 10, 5, 5, COLOR_BLUE);
            gotoxy(17,12);
            textcolor(COLOR_WHITE);
            printf("*");

            rectangle(15, 15, 5, 5, COLOR_BLUE);
            gotoxy(17,17);
            textcolor(COLOR_WHITE);
            printf("0");

            // Display function button and + : Call, +, Erase, Add contact
            rectangle(0, 20, 5, 5, COLOR_GREEN);
            gotoxy(1,22);
            textcolor(COLOR_WHITE);
            printf("Cal");

            rectangle(5, 20, 5, 5, COLOR_BLUE);
            gotoxy(7,22);
            textcolor(COLOR_WHITE);
            printf("+");

            rectangle(10, 20, 5, 5, COLOR_BLUE);
            gotoxy(12,22);
            textcolor(COLOR_WHITE);
            printf("E");

            rectangle(15, 20, 5, 5, COLOR_GREEN);
            gotoxy(16,22);
            textcolor(COLOR_WHITE);
            printf("Add");
            */
            break;

        case 2: // Call
            
            panel(0, HEADER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT-HEADER_HEIGHT, "Incoming call", COLOR_GRAY3);

            // Draw button to end the call
            rectangle(10, SCREEN_HEIGHT-6, SCREEN_WIDTH-20, 5, COLOR_RED);
            gotoxy(19, SCREEN_HEIGHT-4);
            textcolor(COLOR_RED);
            printf("End");

            break;

        case 3: // SMS
                
                panel(0, HEADER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT-HEADER_HEIGHT, "SMS: Contact name", COLOR_GRAY3);
                gotoxy(10,10);
                printf("%d", cgetc());
                break;

        case 4: // Add contact
                
                panel(0, HEADER_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT-HEADER_HEIGHT, "Add/Edit contact", COLOR_GRAY3);

                // Print fields
                textcolor(COLOR_GRAY3);
                gotoxy(2, HEADER_HEIGHT+4);
                printf("Name");

                gotoxy(2, HEADER_HEIGHT+8);
                printf("Number");

                gotoxy(2, HEADER_HEIGHT+12);
                printf("Mail");

                // Print buttons
                rectangle(1, SCREEN_HEIGHT-6, (SCREEN_WIDTH-1)/2, 5, COLOR_GREEN);
                gotoxy((((SCREEN_WIDTH-1)/2)/2-2), SCREEN_HEIGHT-4);
                textcolor(COLOR_GREEN);
                printf("Confirm");

                rectangle(SCREEN_WIDTH-1-((SCREEN_WIDTH-1)/2), SCREEN_HEIGHT-6, (SCREEN_WIDTH-1)/2, 5, COLOR_RED);
                gotoxy(SCREEN_WIDTH-SCREEN_WIDTH/4-4, SCREEN_HEIGHT-4);
                textcolor(COLOR_RED);
                printf("Delete");

                break;

        default:
            break;

    }

    return 0;
}