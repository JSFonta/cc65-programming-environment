#include "utilities.h"
#include "hal.h"
#include "memory.h"
#include "screen.h"
#include "ascii.h"
#include "draw.h"
#include "layout.h"
#include "include.h"

unsigned char modem_line[MAX_MODEM_LINE_LEN+1];
unsigned char modem_line_len=0;
unsigned char parsedData[5][64];
int cpt=0;
unsigned char i;

void write_modem(const unsigned char *s)
{
    for(i=0;s[i];i++) 
    {
        POKE(0xd0e0,s[i]);
        POKE(SCREEN_ADDRESS+64*5+10+i, s[i]);
    }
    displayText("Command : ", 64*5, COLOR_BLUE);
    
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
        displayText("Answer : ", 64*7, COLOR_BLUE);
        displayText(modem_line, 64*7+10, COLOR_WHITE+cpt);
        cpt++;
        if(cpt>5) cpt=0;
    } else {
        if (modem_line_len<MAX_MODEM_LINE_LEN) {
            modem_line[modem_line_len++]=c;
        }
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
        if(modem_line[1] == 'C' && modem_line[2] == 'C' && modem_line[3] == 'L' && modem_line[4] == 'K'&&  modem_line[5] == ':')
        {
            for(i=8;(modem_line[i]!='"' && i<50);i++)
            {
                parsedData[0][i-8] = modem_line[i];
                parsedData[3][i-8] = modem_line[i];
            }
        }

        // Parse network name
        if(modem_line[1] == 'C' && modem_line[2] == 'C' && modem_line[3] == 'L' && modem_line[4] == 'K'&&  modem_line[5] == ':')
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
    displayText("Parsed : ", 64*9, COLOR_BLUE);
    displayText(parsedData[0], 64*9+10, COLOR_WHITE);
}

void updateHeader(void)
{
    write_modem("AT+CSQ\r");
    parser();
    poll_modem();
    write_modem("AT+CCLK?\r");
    parser();
    poll_modem();
}