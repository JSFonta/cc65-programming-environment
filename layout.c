#include "draw.h"
#include "screen.h"
#include "memory.h"
#include "ascii.h"
#include "rlepacker.h"

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
 *  @brief          Draw the dialpad on the screen
 *  @author         Paul Gardner-Stephen
 *  @date           30 AUG 2018
 *  @param          pressed_button indicates which button, if any, should be
 *                  displayed as though currently pressed.
 *  @return         None
 */
unsigned char pressed_button=4;
unsigned char keypad_colours_1[]={
  0x22,0x22,0x22,0x22,
  0x00,0x22,0x22,0x22,0x22,
  0x00,0x22,0x22,0x22,0x22,
  0x00,0x27,0x27,0x27,0x27
};
unsigned char keypad_colours_2[]={
  0x25,0x25,0x25,0x25,
  0x00,0x22,0x22,0x22,0x22,
  0x00,0x27,0x27,0x27,0x27,
  0x00,0x27,0x27,0x27,0x27
};
void display_dialpad(void) {
  unsigned char i,j;
  unsigned long row_addr;
  unpack(packed_dialpad,SCREEN_ADDRESS+((HEADER_HEIGHT+2+1)*64),64);
  
  // Colour and reverse the keypad buttons
  row_addr=COLOUR_RAM_ADDRESS+((HEADER_HEIGHT+2)*64)+1;
  for(i=0;i<16;i++) {
    if (i&3) lcopy(keypad_colours_1,row_addr,19);
    row_addr+=64;
  }
  for(i=0;i<4;i++) {
    if (i&3) lcopy(keypad_colours_2,row_addr,19);
    row_addr+=64;
  }

  // XXX - Change colour of the button currently being pressed
  row_addr=COLOUR_RAM_ADDRESS+((HEADER_HEIGHT+2+1)*64)+1;
  row_addr+=(pressed_button&3)*5;
  row_addr+=(pressed_button/4)*(4*64);
  for(i=0;i<3;i++) {
    lfill(row_addr,0x26,4);
    row_addr+=64;
  }
  
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
    // Incoming call (0) or outgoing call (1)
    unsigned char callType = 0;

    // Coordinate var
    unsigned char numberx, numbery, offsetx;

    // Clear the display
    clearScreen();

    switch(screen)
    {
        case 1: // Main screen

            // Display number composition
            rectangle(0, HEADER_HEIGHT, LEFT_COLUMN_WIDTH, 3, COLOR_BLUE);

            // Display keypad
	    display_dialpad();
	    
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
