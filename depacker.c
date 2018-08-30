#include "memory.h"



void unpack(unsigned char *in,long addr,unsigned char line_len)
{
  unsigned char line_offset=0,count,c;
  while(*in) {    
    if ((*in)>=0xf0) {
      // Run of 1 -- 16 characters
      count=(*in)-0xEF;
      in++;
      c=*in;
      lfill(addr,c,count);
      addr+=count;
      line_offset+=count;
      in++;
    } else {
      if (((*in)==0x0d) ||((*in)==0x0a) ) {
	addr+=line_len-line_offset;
	line_offset=0;
      } else {
	lpoke(addr,*in);
	line_offset++;
      }
      in++;
    }
  }
  return;
}
