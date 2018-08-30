#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

int main(int argc,char **argv)
{
  if (argc<3) {
    fprintf(stderr,"usage: stretchchars <in.bin> <out.bin> [HEX:HEX ...]\n");
    fprintf(stderr,"  HEX:HEX indicates the source character number, and where to put the 2x2 expanded version of it.\n");
    fprintf(stderr,"          e.g., 41:80 will put a 2x2 version of character 41 at characters 80 -- 83\n");
    exit(-3);
  }

  unsigned char buffer[4096];

  FILE *in=fopen(argv[1],"r");
  if (!in) { perror("fopen"); exit(-3); }
  int bytes=fread(buffer,1,4096,in);
  fclose(in);
  fprintf(stderr,"Read %d bytes\n",bytes);
  
  for(int i=3;i<argc;i++) {
    int from,to;
    if (sscanf(argv[i],"%x:%x",&from,&to)==2) {
      for(int x=0;x<8;x++)
	for(int y=0;y<8;y++) {
	  int addr=(to*8)+y*2+1+(x>>2)*16;
	  buffer[addr]=0;
	  addr--;
	  buffer[addr]=0;
	}
      for(int x=0;x<8;x++)
	for(int y=0;y<7;y++) {
	  buffer[1+(to*8)+y*2+0+16-(x>>2)*16]|=( (buffer[(from*8)+y]&(1<<x))?1:0 ) << ( (x&3) << 1) ;
	  buffer[1+(to*8)+y*2+0+16-(x>>2)*16]|=( (buffer[(from*8)+y]&(1<<x))?1:0 ) << ( 1+ ( (x&3) << 1) );
	  buffer[1+(to*8)+y*2+1+16-(x>>2)*16]|=( (buffer[(from*8)+y]&(1<<x))?1:0 ) << ( (x&3) << 1) ;
	  buffer[1+(to*8)+y*2+1+16-(x>>2)*16]|=( (buffer[(from*8)+y]&(1<<x))?1:0 ) << ( 1+ ( (x&3) << 1) );
	}
      
    } else {
      fprintf(stderr,"Invalid transformation '%s'\n",argv[i]);
    }
  }

  // XXX - A hack to set char FD to the right shape for the left edge of the buttons
  for(int i=0;i<8;i++) buffer[0xfd*8+i]=0xfe;
  
  FILE *out=fopen(argv[2],"w");
  fwrite(buffer,bytes,1,out);
  fclose(out);
  
}
