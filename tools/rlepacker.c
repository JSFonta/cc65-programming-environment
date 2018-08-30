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

// 128 - 135 are used for other things, so we start at 136
int next_special_char=136;

int special_indexes[256];
int special_offsets[256];

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
    fprintf(stderr,"Characters 0xf0 - 0xff cannot be encoded.\n");
    exit(-3);
  } else {
    if (last_count>1) {
      // Run of characters
      // If it is space, we RLE code it.
      // If it is something else, then it is a place-holder for
      // a large glyph
      if (last_char==0x0a) {
	while(last_count--) {
	  emit_byte(0x0a);
	}
      }
      else if (last_char==0x20) {
	emit_byte(0xf0+last_count-1);
      } else {
	if (special_indexes[last_char]) {
	  // We already have byte range allocated
	} else {
	  special_indexes[last_char]=next_special_char;
	  special_offsets[last_char]=next_special_char;
	  if (last_count==2) next_special_char+=4; // 2x2 for big digits
	  if (last_count==3) next_special_char+=3; // 3x1 for voice mail button
	  if (last_count==4) next_special_char+=12; // 4x3 for CALL button
	  if (next_special_char>0xf0) {
	    fprintf(stderr,"Too many special characters required.\n");
	    exit(-3);
	  }
	}
	// Output the characters
	while(last_count) {
	  emit_byte(special_offsets[last_char]++);
	  last_count--;
	}
	
      }
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

  for(int i=0;i<256;i++) special_indexes[i]=0;

  // Offsets of various symbols from J-S's font:
  special_indexes['1']=136;
  special_offsets['1']=136;
  special_indexes['2']=140;
  special_offsets['2']=140;
  special_indexes['3']=144;
  special_offsets['3']=144;
  special_indexes['4']=148;
  special_offsets['4']=148;
  special_indexes['5']=152;
  special_offsets['5']=152;
  special_indexes['6']=156;
  special_offsets['6']=156;
  special_indexes['7']=160;
  special_offsets['7']=160;
  special_indexes['8']=164;
  special_offsets['8']=164;
  special_indexes['9']=168;
  special_offsets['9']=168;
  special_indexes['0']=172;
  special_offsets['0']=172;
  next_special_char=176;
  
  FILE *f=fopen(argv[1],"r");

  printf("unsigned char packed_dialpad[]={\n");
  
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
  for(int i=0;i<256;i++) {
    if (special_indexes[i]) {
      fprintf(stderr,"  Big symbol '%c' begins at character 0x%02x (%d)\n",i,special_indexes[i],special_indexes[i]);
    }
  }
  
  return 0;
}
