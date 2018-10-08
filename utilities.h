#define MAX_MODEM_LINE_LEN (255-1)

#define NB_PARAM_PARSER 5
#define NB_CHAR_PER_PARAM_PARSER 64

extern unsigned char modem_line[MAX_MODEM_LINE_LEN+1];
extern unsigned char dataHeaderFirstLine[51] = "                                                   ";
extern unsigned char dataHeaderSecondLine[51] = "                                                   ";

void write_modem(const unsigned char *s);
int setupSerial(void);
void poll_modem(void);
void updateHeader(void);
void parser(void);
void modemCom(void);