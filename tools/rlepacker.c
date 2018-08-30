/*
  Pack text file using simple run-length encoding scheme.

  0xF0 - 0xFF = run of 1 to 16 of the next character.
  (Characters 0xf0 - 0xff encoded as 0xf0 0xXX)

*/

#include <stdio.h>
#include <stdlib.h>

int last_char=0xFFFF;
int last_count=0;

int encoded_len=0;
int input_len=0;

int bytes_on_line=0;

int emit_byte(unsigned char c)
{
  encoded_len++;
  if (!bytes_on_line) printf("  ");
  printf("0x%02X,",c);
  bytes_on_line++;
  if (bytes_on_line==16) {
    printf("\n"); bytes_on_line=0;
  }
}

int emit_rle(void)
{
  if (!last_count) return 0;
  if (last_char>=0xf0) {
    // Forced to use RLE for characters 0xf0 - 0xff
    emit_byte(0xf0+last_count-1);
    emit_byte(last_char);
  } else {
    if (last_count>1) {
      // Run of characters
      emit_byte(0xf0+last_count-1);
      emit_byte(last_char);
    } else {
      // Singleton
      emit_byte(last_char);      
    }
  }
  last_count=0;
  
}

int pack_char(unsigned char c)
{
  input_len++;
  if (c==last_char) {
    if (last_count==16) {
      emit_rle();
      last_count=1;
      last_char=c;
    } else {
      last_count++;
    }
  } else {
    if (last_count) emit_rle();
    last_char=c;
    last_count=1;
  }
  return 0;
}

int main(int argc,char **argv)
{
  unsigned char line[1024];

  if (!argv[1]) {
    fprintf(stderr,"usage: rlepacker <input file>\n");
    exit(-3);
  }
  
  FILE *f=fopen(argv[1],"r");

  printf("unsigned char packed[]={\n");
  
  line[0]=0; fgets(line,1024,f);
  while(line[0]) {
    for(int i=0;line[i];i++) pack_char(line[i]);
    
    line[0]=0; fgets(line,1024,f);
  }
  pack_char(0);

  if (bytes_on_line) printf("\n");
  printf("  0x00\n};\n");
  
  fprintf(stderr,"Input file of %d bytes packed to %d bytes\n",
	  input_len,encoded_len);

  return 0;
}
