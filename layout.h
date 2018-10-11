extern unsigned char pressed_button;
void clearScreen(void);
unsigned char layout(unsigned char screen);
void displayText(char * text, unsigned long startPosition, unsigned char color);
void buttons(unsigned char layout);
void display_dialpad(void);