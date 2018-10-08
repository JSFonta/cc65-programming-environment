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
unsigned char i, k;
unsigned char at[3][15] = {"AT+QSPN\r", "AT+CCLK?\r", "AT+CSQ\r"};
unsigned char j = 0;

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
    if(cpt == 100)
    {
        write_modem(at[j]);
        j++;
        if(j > 2) j = 0;
        cpt = 0;
    }
    poll_modem();
    //displayText(modem_line, 64*19, COLOUR_CYAN);
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
        /*displayText("Parsed : ", 64*9, COLOR_RED);
        displayText(parsedData[0], 64*9+10, COLOR_WHITE);
        displayText("Parsed : ", 64*10, COLOR_RED);
        displayText(parsedData[1], 64*10+10, COLOR_WHITE);
        displayText("Parsed : ", 64*11, COLOR_RED);
        displayText(parsedData[2], 64*11+10, COLOR_WHITE);*/
    }
}

void updateHeader(void)
{
    /*displayText("Parsed : ", 64*15, COLOR_BLUE);
    displayText(parsedData[0], 64*15+10, COLOR_WHITE);
    displayText("Parsed : ", 64*16, COLOR_BLUE);
    displayText(parsedData[1], 64*16+10, COLOR_WHITE);
    displayText("Parsed : ", 64*17, COLOR_BLUE);
    displayText(parsedData[2], 64*17+10, COLOR_WHITE);*/
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