
CC65=	cc65/bin/cc65
CL65=	cc65/bin/cl65
COPTS=	-t c64 -O -Or -Oi -Os --cpu 65c02
LOPTS=	

FILES=		example.prg 

M65IDESOURCES=	main.c \
		layout.c \
		draw.c \
		memory.c \
		screen.c \
		depacker.c \
		packed_dialpad.c \
		hal_mega65.c

ASSFILES=	main.s \
		layout.s \
		draw.s \
		memory.s \
		screen.s \
		depacker.s \
		packed_dialpad.s \
		hal_mega65.s \
		charset.s

HEADERS=	Makefile \
		include.h \
		layout.h \
		draw.h \
		memory.h \
		screen.h \
		hal.h \
		ascii.h

DATAFILES=	ascii8x8.bin

%.s:	%.c $(HEADERS) $(DATAFILES) $(CC65)
	$(CC65) $(COPTS) -o $@ $<

all:	$(FILES)

$(CC65):
	git submodule init
	git submodule update
	(cd cc65 && make -j 8)

ascii8x8.bin: font.png tools/pngprepare tools/raw2bin tools/stretchchars
	# Convert PNG font to bin format
	tools/pngprepare charrom font.png temp.bin
	# Make expanded versions of select characters
	tools/stretchchars temp.bin ascii8x8.bin 31:84 32:88 33:8c 41:90

asciih:	asciih.c
	$(CC) -o asciih asciih.c
ascii.h:	asciih
	./asciih

tools/pngprepare:	tools/pngprepare.c
	$(CC) -I/usr/local/include -L/usr/local/lib -o tools/pngprepare tools/pngprepare.c -lpng

tools/raw2bin:	tools/raw2bin.c
	$(CC) -I/usr/local/include -L/usr/local/lib -o tools/raw2bin tools/raw2bin.c -lpng

tools/rlepacker:	tools/rlepacker.c
	$(CC) -o tools/rlepacker tools/rlepacker.c

tools/stretchchars:	tools/stretchchars.c
	$(CC) -o tools/stretchchars tools/stretchchars.c

packed_dialpad.c:	tools/rlepacker dialpad.txt
	tools/rlepacker dialpad.txt > packed_dialpad.c

example.prg:	$(ASSFILES) $(DATAFILES) $(CL65)
	$(CL65) $(COPTS) $(LOPTS) -vm -m example.map -o example.prg $(ASSFILES)

clean:
	rm -f $(FILES)

cleangen:
	rm ascii8x8.bin
