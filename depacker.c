#include "memory.h"



void unpack(unsigned char *in,long addr,unsigned char line_len)
{
  unsigned char b=0;
  unsigned char line_offset=0,count,c;
  while(*in) {
    POKE(0x8000+b,*in);
    if (((*in)>=0xf0)&&((*in)<0xf8)) {
      // Run of 1 -- 16 characters
      count=(*in)-0xEF;
      POKE(0x8000+b,count);
      in++;
      lfill(addr,0x20,count);
      addr+=count;
      line_offset+=count;
    } else {
      if (((*in)==0x0d) ||((*in)==0x0a) ) {
	addr+=line_len-line_offset;
	line_offset=0;
      } else {
	lpoke(addr,*in);
	line_offset++;
	addr++;
      }
      in++;
    }
    b++;
  }

  return;
}
