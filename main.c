/*
  A simple example program using CC65 and some simple routines to
  use an 80 column ASCII screen on the MEGA65.

  If you follow some restrictions, it is also possible to make such
  programs compile and run natively on your development system for
  testing.
 
*/

#include <stdio.h>
#include <string.h>

#include "hal.h"
#include "memory.h"
#include "screen.h"
#include "ascii.h"
#include "draw.h"
#include "layout.h"
#include "include.h"

int setupSerial()
{
    // Setup 115200 bit rate
    POKE(0xd0e6, 0xb2);
    POKE(0xd0e7, 0x01);
        
    return 0;
}   


    void write_modem(const unsigned char *s,const unsigned char len)
    {
        unsigned char i;
        for(i=0;i!=len;i++) POKE(0xd0e0,s[i]);
        return;
    }

    #define MAX_MODEM_LINE_LEN (255-1)
    unsigned char modem_line[MAX_MODEM_LINE_LEN+1];
    unsigned char modem_line_len=0;

    void process_modem_line(void) 
    {
        printf("%s\n",modem_line);
        return;
    }

    void poll_modem(void)
    {
        unsigned char c=PEEK(0xd0e0);
        if (!c) return;
        if (c=='\r'||c=='\n') {
            // End of line
            modem_line[modem_line_len]=0;
            process_modem_line();
            modem_line_len=0;
        } else {
            if (modem_line_len<MAX_MODEM_LINE_LEN) {
                modem_line[modem_line_len++]=c;
            }
        }
    }


#ifdef __CC65__
void main(void)
#else
int main(int argc,char **argv)
#endif
{ 
  
  // Loop variable
    unsigned char i, j; 

    // Buffer for keyboard input
    char inputBuffer[100];
    unsigned char indexBuffer = 0;
    char currentCharacter;

    // Flag EOS
    unsigned char flagEos = 0;

    // Define some variable which will need to be provided by the modem
    char data[4][10] = {"YES OPTUS", "09:26:30", "4G+", "Low"};

    // Define some contacts
    char contacts[5][18] = {"Paul", "Js", "Secret", "Lorem Ipsum", "Flinders"};

    #ifdef __CC65__
      mega65_fast();
      setup_screen();
    #endif 

    // CPU high speed 
    POKE(0, 65);

    // Enable Mega65 have extensions
    POKE(0xd02f, 0x47);
    POKE(0xd02f, 0x53);

    // Configure serial
    setupSerial();

    write_line("Hello world!",0);
    recolour_last_line(2);
    
    while(1) {
        poll_modem();
        if (kbhit()) { 
            unsigned char c=cgetc();
            if (c) write_modem(&c,1);
        }
        POKE(53280,(PEEK(53280)+1)&15);
    }

    // Clear all the screen
    clrscr();

    layout(1);

    while(1)
    {
        // Header
        textcolor(COLOR_WHITE);

        // Display data
        gotoxy(0, 0);
        for(i = 0; i < MAX_NUMBER_PARAM_HEADER; i++)
        {
            for(j = 0; j < MAX_LENGTH_PARAM_HEADER; j++)
            {
                // End of this data ?
                if(data[i][j] == '\0')
                {
                    flagEos = 1;
                }

                // Complete with text or white space
                if(flagEos == 1)
                {
                    cputc(' ');
                }
                else
                {
                    cputc(data[i][j]);
                }
            }

            // Reset the flag Eos
            flagEos = 0;
        }

        // Something to read from the keyboard ?
        while(kbhit() != 0)
        {
            // Read the character into the stdin
            currentCharacter = cgetc();

            // Clear the inputBuffer
            if(currentCharacter == 'e' || currentCharacter == 'E')
            {
                indexBuffer = 0;
                inputBuffer[indexBuffer] = '\0';
                clearNumero();
            }

            // Call
            else if(currentCharacter == 'c' || currentCharacter == 'C')
            {
                // Change the layout
                layout(2);
                
                // Display data
            }

            // Add contact
            else if(currentCharacter == 'a' || currentCharacter == 'A')
            {
                // Change the layout
                layout(3);
            }

            // Escape -> go back main menu
            else if(currentCharacter == 3)
            {
                // Change the layout
                clrscr();
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

        // Display what was typed
        gotoxy(1, 3);
        textcolor(COLOR_WHITE);
        printf("%s", inputBuffer);

    }
    return;
}