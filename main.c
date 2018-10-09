#include <stdio.h>
#include <string.h>

#include "hal.h"
#include "memory.h"
#include "screen.h"
#include "ascii.h"
#include "draw.h"
#include "layout.h"
#include "include.h"
#include "utilities.h"

#ifdef __CC65__
void main(void)
#else
int main(int argc,char **argv)
#endif
{
    int cpt;
    char s[10]; // Nombre maximal de chiffres + 1
    // Loop variable
    unsigned char i, j, layoutIndex; 

    // Buffer for keyboard input
    char inputBuffer[100];
    unsigned char indexBuffer = 0;
    char currentCharacter;

    // Flag EOS
    unsigned char flagEos = 0;

    // Define some contacts
    unsigned char nbContacts = 5;
    unsigned char currentContact = 0;
    char contacts[5][18] = {"Paul", "Js", "Secret", "Lorem Ipsum", "Flinders"};

    #ifdef __CC65__
      mega65_fast();
      setup_screen();

      // Background black
      POKE(0xd021, COLOUR_BLACK);
    #endif 

    // CPU high speed 
    POKE(0, 65);

    // Enable Mega65 have extensions
    POKE(0xd02f, 0x47);
    POKE(0xd02f, 0x53);

    // Configure serial
    setupSerial();

    /*while(1)
    {
        unsigned char low=PEEK(0xd6b9);
        unsigned char high=PEEK(0xD6BB)&3;
        unsigned char y,x=(low>>4)+(high<<4)+2;
        low=PEEK(0xd6ba);
        high=PEEK(0xd6bb)>>4;
        y=(low>>4)+(high<<4)-4;
        if (x>=0&&y>=0) {
        lpoke(SCREEN_ADDRESS+x+(y<<6),0x40);

        displayText("x: ", (HEADER_HEIGHT+1)*64, COLOR_BLUE);
        displayText(s, (HEADER_HEIGHT+1)*64+3, COLOR_WHITE);
        lpoke(SCREEN_ADDRESS+x+(y<<6),0x20);
        }
    }*/

    /*GS $D6B9 - Touch pad touch #1 X LSB
GS $D6BA - Touch pad touch #1 Y LSB*/

    // Init modem
    write_modem("AT");
    modemCom();
    
    
    // Home
    layoutIndex = 1;
    layout(layoutIndex);

    while(1)
    {

        // Home
        if(layoutIndex == 1)
        {
            // Display the stdin buffer content
            displayText(inputBuffer, 64*(HEADER_HEIGHT+1)+2, COLOR_WHITE);

            // display contacts
            for(i=0; i<nbContacts; i++)
            {
                // Display all contact, the first is "selected"
                displayText(contacts[i], SCREEN_COLS*(HEADER_HEIGHT+4+i)+LEFT_COLUMN_WIDTH+3, i==currentContact?COLOR_YELLOW:COLOR_WHITE);
            }

            // Something to read from input ?
            while(kbhit() != 0)
            {
                // Read the character into the stdin
                currentCharacter = cgetc();

                // Clear the inputBuffer
                // Backspace <=> 1 by 1
                if(currentCharacter == 20)
                {
                    // Only 1 thing into the buffer or nothing
                    if(indexBuffer == 0)
                    {
                        inputBuffer[indexBuffer] = '\0';
                    }
                    // Usual case
                    else if(indexBuffer > 0)
                    {
                        inputBuffer[indexBuffer-1] = '\0';
                        indexBuffer--;
                    }

                    // Clear last character
                    displayText("              ", 64*(HEADER_HEIGHT+1)+2, COLOR_BLACK);
                }

                // Clear the inputBuffer
                // Erase <=> clear all
                else if(currentCharacter == 'e' || currentCharacter == 'E')
                {
                    
                    // Clear input field
                    displayText("              ", 64*(HEADER_HEIGHT+1)+2, COLOR_BLACK);

                    // Re initialize the buffer index
                    indexBuffer = 0;
                    inputBuffer[indexBuffer] = '\0';
                }
                
                // Next or previous contact
                else if(currentCharacter == ',' || currentCharacter == '.')
                {
                    // Previous (above)
                    if(currentCharacter == ',')
                    {
                        // Go to the previous contact or go back to the last one
                        if(currentContact == 0)
                        {
                            currentContact = nbContacts-1;
                        }
                        else
                        {
                            currentContact--;
                        }
                    }

                    // Next (below)
                    else
                    {
                        // Go to the next contact or go back to the first one
                        if(currentContact == nbContacts-1)
                        {
                            currentContact = 0;
                        }
                        else
                        {
                            currentContact++;
                        }
                    }
                }

                // Call
                else if(currentCharacter == 'c' || currentCharacter == 'C')
                {
                    // Change the layout
                    layoutIndex = 2;
                    layout(layoutIndex);
                }

                // Add contact
                else if(currentCharacter == 'a' || currentCharacter == 'A')
                {
                    // Change the layout
                    layoutIndex = 4;
                    layout(layoutIndex);
                }

                // SMS to a contact
                else if(currentCharacter == '/')
                {
                    // Change the layout
                    layoutIndex = 3;
                    layout(layoutIndex);
                }

                // Escape -> go back main menu
                else if(currentCharacter == 3)
                {
                    // Change the layout
                    layout(1);
                }

                // Numero typing
                else
                {
                    // No more than 14 numeros
                    if(indexBuffer < 14)
                    {
                        // Be sure it is a number
                        if(currentCharacter == '0' || currentCharacter == '1' || currentCharacter == '2' || currentCharacter == '3' || currentCharacter == '4' || currentCharacter == '5' || currentCharacter == '6' || currentCharacter == '7' || currentCharacter == '8' || currentCharacter == '9' || currentCharacter == '#' || currentCharacter == '*' || currentCharacter == '+')
                        {
                            inputBuffer[indexBuffer] = currentCharacter;
                            inputBuffer[indexBuffer+1] = '\0';
                            indexBuffer++;
                        }
                    }
                }
            }

        }
        else if(layoutIndex == 2)
        {
            // Call

            displayText("Call with ", (HEADER_HEIGHT+4)*64+2, COLOR_WHITE);
            displayText(indexBuffer ? inputBuffer : "nobody :( Make some friends :)", (HEADER_HEIGHT+4)*64+12, COLOR_WHITE);

            // Something to read from input ?
            while(kbhit() != 0)
            {

                // Read the character into the stdin
                currentCharacter = cgetc();

                // Escape -> go back main menu
                if(currentCharacter == 3)
                {
                    // Change the layout
                    layoutIndex = 1;
                    layout(layoutIndex);
                }
            }

        }
        else if(layoutIndex == 3)
        {
            // SMS

            displayText("28/08 10:06 | Jean-Sebastien :", (HEADER_HEIGHT+7)*64+SCREEN_WIDTH-32, COLOR_RED);
            displayText("Hey, welcome on this marvelous screen !", (HEADER_HEIGHT+8)*64+SCREEN_WIDTH-40, COLOR_GRAY3);

            displayText("You | 28/08 10:15", (HEADER_HEIGHT+4)*64+3, COLOR_BLUE);
            displayText("Thanks man ! Nice example :-)", (HEADER_HEIGHT+5)*64+2, COLOR_GRAY3);

            // Display the stdin buffer content
            displayText(inputBuffer, (SCREEN_HEIGHT-3)*SCREEN_COLS+3, COLOR_WHITE);

            // Something to read from input ?
            while(kbhit() != 0)
            {

                // Read the character into the stdin
                currentCharacter = cgetc();

                // Escape -> go back main menu
                if(currentCharacter == 3)
                {
                    // Change the layout
                    layoutIndex = 1;
                    layout(layoutIndex);
                }

                // Clear the inputBuffer
                else if(currentCharacter == 'e' || currentCharacter == 'E')
                {
                    i=0;
                    while(inputBuffer[i] != '\0')
                    {
                        // Replace by white space
                        POKE(SCREEN_ADDRESS+(SCREEN_HEIGHT-3)*SCREEN_COLS+3+i, ' ');
                        i++;
                    }

                    // Re initialize the buffer index
                    indexBuffer = 0;
                    inputBuffer[indexBuffer] = '\0';
                }

                // Send the text
                else if(currentCharacter == 's' || currentCharacter == 'S')
                {
                    i=0;
                    while(inputBuffer[i] != '\0')
                    {
                        // Replace by white space
                        POKE(SCREEN_ADDRESS+(SCREEN_HEIGHT-3)*SCREEN_COLS+3+i, ' ');
                        i++;
                    }

                    // Re initialize the buffer index
                    indexBuffer = 0;
                    inputBuffer[indexBuffer] = '\0';
                }

                // Text typing
                else
                {
                    // No more than 255 chars
                    if(indexBuffer < 255)
                    {
                        inputBuffer[indexBuffer] = currentCharacter;
                        inputBuffer[indexBuffer+1] = '\0';
                        indexBuffer++;
                    }
                }
            }
        }

        else if(layoutIndex == 4)
        {
            // Something to read from input ?
            while(kbhit() != 0)
            {

                // Read the character into the stdin
                currentCharacter = cgetc();

                // Escape -> go back main menu
                if(currentCharacter == 3)
                {
                    // Change the layout
                    layoutIndex = 1;
                    layout(layoutIndex);
                }
            }
        }

        modemCom();

        listener();

    }
    return;
}