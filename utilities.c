#include "utilities.h"
#include "hal.h"
#include "memory.h"
#include "screen.h"
#include "ascii.h"
#include "draw.h"
#include "layout.h"
#include "include.h"
#include <stdlib.h>

unsigned char modem_line[MAX_MODEM_LINE_LEN+1];
unsigned char modem_line_len=0;
unsigned char parsedData[5][64];
int cpt=0;
unsigned char i, k;
unsigned char at[3][15] = {"AT+QSPN\r", "AT+CCLK?\r", "AT+CSQ\r"};
unsigned char j = 0;

struct coordinate {
   unsigned char x;
   unsigned char y;
};

struct area {
   struct coordinate topleft;
   struct coordinate bottomright;
   unsigned char key;
};

struct area interaction[NB_MAX_INTERACTION];
unsigned char nbInteraction = 0;
unsigned char isTouching;

void addInteraction(unsigned char startx, unsigned char starty, unsigned char endx, unsigned char endy,
unsigned char keySimulated)
{
    struct area new;
    new.topleft.x = startx;
    new.topleft.y = starty;
    new.bottomright.x = endx;
    new.bottomright.y = endy;
    new.key = keySimulated;
    if(nbInteraction < NB_MAX_INTERACTION)
    {
        interaction[nbInteraction] = new;
        nbInteraction++;
    }
}

void clearInteraction(void)
{
    nbInteraction = 0;
}

unsigned char listener(void)
{
    int cpt;
    unsigned char i;
    unsigned char rising;
    unsigned char newPressedButton;
    unsigned char text[2];
    unsigned char low=PEEK(0xd6b9);
    unsigned char high=PEEK(0xD6BB)&3;
    unsigned char y,x=(low>>4)+(high<<4)+2;
    low=PEEK(0xd6ba);
    high=PEEK(0xd6bb)>>4;
    y=(low>>4)+(high<<4)-4;

    // Detect if user touch the screen or not
    
    if (isTouching&&(!(PEEK(0xd6b0)&1))) rising=1; else rising=0;
    isTouching = PEEK(0xD6B0)&1;

    if(!isTouching && !rising) return '\0';

    // Listen to every button position
    for(i=0; i<nbInteraction; i++)
    {
        if (x > interaction[i].topleft.x && x < interaction[i].bottomright.x
        && y > interaction[i].topleft.y && y < interaction[i].bottomright.y)
        {
            
            // Change the color of the last pressed number on dialpad
            if((interaction[i].key >= '0' && interaction[i].key <= '9') 
            || (interaction[i].key >= 'A' && interaction[i].key <= 'D')
            || interaction[i].key == '#' || interaction[i].key == '*' 
            || interaction[i].key == '-' || interaction[i].key == '+'
            || interaction[i].key == '=')
            {

                if(interaction[i].key >= '1' && interaction[i].key <= '3')
                {
                    newPressedButton = interaction[i].key-49;
                }
                else if(interaction[i].key == 'A') newPressedButton = 3;
                else if(interaction[i].key >= '4' && interaction[i].key <= '6')
                {
                    newPressedButton = interaction[i].key-48;
                }
                else if(interaction[i].key == 'B') newPressedButton = 7;
                else if(interaction[i].key >= '7' && interaction[i].key <= '9')
                {
                    newPressedButton = interaction[i].key-47;
                }
                else if(interaction[i].key == 'C') newPressedButton = 11;
                else if(interaction[i].key == '#') newPressedButton = 12;
                else if(interaction[i].key == '0') newPressedButton = 13;
                else if(interaction[i].key == '*') newPressedButton = 14;
                else if(interaction[i].key == 'D') newPressedButton = 15;
                else if(interaction[i].key == 'c') newPressedButton = 16;
                else if(interaction[i].key == '-') newPressedButton = 17;
                else if(interaction[i].key == '+') newPressedButton = 18;
                else if(interaction[i].key == '=') newPressedButton = 19;

                if(pressed_button != newPressedButton)
                {
                    pressed_button = newPressedButton;
                    display_dialpad();
                }
            } 

            if(rising)
            {
                return interaction[i].key;
            }

        }
    }
}

void write_modem(const unsigned char *s)
{
    for(i=0;s[i];i++) 
    {
        POKE(0xd0e0,s[i]);
    }
    //displayText("Command : ", 64*5, COLOR_BLUE);
    
    return;
}

void poll_modem(void)
{
    unsigned char c=PEEK(0xd0e0);
    if (!c) return;
    if (c=='\r'||c=='\n') {
        // End of line
        modem_line[modem_line_len]=0;
        modem_line_len=0;
        //displayText("Answer : ", 64*7, COLOR_BLUE);
        //displayText(modem_line, 64*7+10, COLOR_WHITE);
        parser();
    } else {
        if (modem_line_len<MAX_MODEM_LINE_LEN) {
            modem_line[modem_line_len++]=c;
        }
    }
}

void modemCom(void)
{
    // Avoid to ask to many times the modem
    cpt++;
    if(cpt >= 100)
    {
        write_modem(at[j]);
        j++;
        if(j > 2) j = 0;
        cpt = 0;
    }
    poll_modem();
    if(modem_line[0] == 'O' && modem_line[1] == 'K')
    {
        updateHeader();
    }
}

int setupSerial(void)
{
    // Setup 115200 bit rate
    POKE(0xd0e6, 0xb2);
    POKE(0xd0e7, 0x01);
        
    return 0;
}

/*
    0 : network1 quality
    1 : network1 name
    2 : date + time
    3 : network2 quality
    4 : network2 name
*/
void parser(void)
{
    unsigned short i=0;

    // Answer of the modem
    if(modem_line[0] == '+')
    {
        // Parse network quality
        if(modem_line[1] == 'C' && modem_line[2] == 'S' && modem_line[3] == 'Q' && modem_line[4] == ':')
        {
            for(i=6;(modem_line[i]!=',' && i<10);i++)
            {
                parsedData[0][i-6] = modem_line[i];
                parsedData[3][i-6] = modem_line[i];
            }
        }

        // Parse network name
        if(modem_line[1] == 'Q' && modem_line[2] == 'S' && modem_line[3] == 'P' && modem_line[4] == 'N'&&  modem_line[5] == ':')
        {
            for(i=8;(modem_line[i]!='"' && i<50);i++)
            {
                parsedData[1][i-8] = modem_line[i];
                parsedData[4][i-8] = modem_line[i];
            }
        }

        // Parse the date
        if(modem_line[1] == 'C' && modem_line[2] == 'C' && modem_line[3] == 'L' && modem_line[4] == 'K'&&  modem_line[5] == ':')
        {
            for(i=8;(modem_line[i]!='"' && i<50);i++)
            {
                parsedData[2][i-8] = modem_line[i];
            }
        }
    }
}

void updateHeader(void)
{
    // Header on every layout
    // Check first sim network name on 7 char + separator
    for(i=0; i<7; i++)
    {
        dataHeaderFirstLine[i] = parsedData[1][i];
    }
    dataHeaderFirstLine[i] = ' ';

    // Check first sim quality network on 4 char + separator
    for(i=8; i<8+4; i++)
    {
        if(parsedData[0][0] >= '1' && parsedData[0][0] >= '9'
        && parsedData[0][1] >= '1' && parsedData[0][1] >= '9'
        && parsedData[0][2] >= '1' && parsedData[0][2] >= '9')
        {
            dataHeaderFirstLine[i] = 'g';
        }
        else
        {
            dataHeaderFirstLine[i] = 'b';
        }
    }
    dataHeaderFirstLine[i] = ' ';

    // Display notification & gps of the first sim on 6 char + separator
    for(i=13; i<13+6; i++)
    {
        dataHeaderFirstLine[i] = 'n';
    }
    dataHeaderFirstLine[i] = ' ';

    // Display time on 8 char + separator
    for(i=20; i<20+8; i++)
    {
        dataHeaderFirstLine[i] = parsedData[2][i-20];
    }
    dataHeaderFirstLine[i] = ' ';

    // Display notification & gps of the second sim on 6 char + separator
    for(i=30; i<30+6; i++)
    {
        dataHeaderFirstLine[i] = 'n';
    }
    dataHeaderFirstLine[i] = ' ';

    // Check second sim network name on 7 char + separator
    for(i=37; i<37+7; i++)
    {
        dataHeaderFirstLine[i] = parsedData[1][i-37];
    }
    dataHeaderFirstLine[i] = ' ';

    // Check second sim quality network on 4 char + separator
    for(i=45; i<45+4; i++)
    {
        if(parsedData[0][0] >= '1' && parsedData[0][0] >= '9'
        && parsedData[0][1] >= '1' && parsedData[0][1] >= '9'
        && parsedData[0][2] >= '1' && parsedData[0][2] >= '9')
        {
            dataHeaderFirstLine[i] = 'g';
        }
        else
        {
            dataHeaderFirstLine[i] = 'b';
        }
    }
    dataHeaderFirstLine[i] = ' ';

    // Second line first sim type of network on 4 char
    for(i=8; i<8+4; i++)
    {
        dataHeaderSecondLine[i] = 't';
    }

    // Second line battery level on 8 char
    for(i=20; i<20+9; i++)
    {
        dataHeaderSecondLine[i] = 'B';
    }

    // Second line first sim type of network on 4 char
    for(i=45; i<45+4; i++)
    {
        dataHeaderSecondLine[i] = 't';
    }
    dataHeaderFirstLine[50] = '\0';
    dataHeaderSecondLine[50] = '\0';
    displayText(dataHeaderFirstLine, 0, COLOR_WHITE);
    displayText(dataHeaderSecondLine, SCREEN_COLS, COLOR_WHITE);
}