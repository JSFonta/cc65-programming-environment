;
; File generated by cc65 v 2.17 - Git 6c320f7d
;
	.fopt		compiler,"cc65 v 2.17 - Git 6c320f7d"
	.setcpu		"65C02"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.import		_gotoxy
	.import		_cputc
	.import		_lfill
	.export		_rectangle
	.export		_panel

; ---------------------------------------------------------------
; void __near__ rectangle (const unsigned char, const unsigned char, const unsigned char, const unsigned char, const unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_rectangle: near

.segment	"CODE"

	jsr     pusha
	ldy     #$0A
	jsr     subysp
	ldx     #$00
	ldy     #$0C
	lda     (sp),y
	ldy     #$0E
	ora     (sp),y
	and     #$80
	jne     L0007
	ldy     #$0B
	lda     (sp),y
	ldy     #$0D
	ora     (sp),y
	and     #$80
	jne     L0007
	dey
	lda     (sp),y
	cmp     #$40
	jcs     L0007
	dey
	lda     (sp),y
	cmp     #$1E
	jcs     L0007
	iny
	lda     (sp),y
	clc
	ldy     #$0E
	adc     (sp),y
	bcc     L008E
	inx
L008E:	cmp     #$40
	txa
	sbc     #$00
	jcs     L0007
	ldx     #$00
	ldy     #$0B
	lda     (sp),y
	clc
	ldy     #$0D
	adc     (sp),y
	bcc     L008F
	inx
L008F:	cmp     #$1E
	txa
	sbc     #$00
	jcs     L0007
	ldx     #$00
	lda     (sp),y
	jsr     aslax4
	jsr     aslax2
	ldy     #$06
	jsr     staxysp
	ldy     #$0E
	lda     (sp),y
	ldx     #$00
	ldy     #$06
	jsr     addeqysp
	ldy     #$07
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	pha
	txa
	clc
	adc     #$F4
	tax
	pla
	ldy     #$04
	jsr     staxysp
	ldy     #$07
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     push0ax
	ldx     #$00
	lda     #$F8
	sta     sreg
	lda     #$0F
	sta     sreg+1
	txa
	jsr     tosaddeax
	jsr     steax0sp
	jsr     decsp5
	ldy     #$0A
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	stz     sreg
	stz     sreg+1
	ldy     #$01
	jsr     steaxysp
	lda     #$80
	sta     (sp)
	ldy     #$11
	lda     (sp),y
	ldx     #$00
	jsr     _lfill
	ldy     #$05
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	lda     #$B0
	sta     (ptr1)
	ldy     #$0C
	lda     (sp),y
	clc
	ldy     #$04
	adc     (sp),y
	pha
	lda     #$00
	iny
	adc     (sp),y
	tax
	pla
	sec
	sbc     #$01
	bcs     L002E
	dex
L002E:	sta     ptr1
	stx     ptr1+1
	lda     #$AE
	sta     (ptr1)
	dey
	ldx     #$00
	lda     #$40
	jsr     addeqysp
	lda     #$02
	ldy     #$09
L0092:	sta     (sp),y
	ldy     #$0B
	cmp     (sp),y
	bcs     L0033
	jsr     decsp5
	dey
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	stz     sreg
	stz     sreg+1
	ldy     #$01
	jsr     steaxysp
	lda     #$20
	sta     (sp)
	ldy     #$11
	lda     (sp),y
	ldx     #$00
	jsr     _lfill
	ldy     #$05
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	lda     #$9D
	sta     (ptr1)
	ldy     #$0C
	lda     (sp),y
	clc
	ldy     #$04
	adc     (sp),y
	pha
	lda     #$00
	iny
	adc     (sp),y
	tax
	pla
	sec
	sbc     #$01
	bcs     L0045
	dex
L0045:	sta     ptr1
	stx     ptr1+1
	lda     #$9D
	sta     (ptr1)
	dey
	ldx     #$00
	lda     #$40
	jsr     addeqysp
	ldy     #$09
	lda     (sp),y
	ina
	bra     L0092
L0033:	jsr     decsp5
	dey
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	stz     sreg
	stz     sreg+1
	ldy     #$01
	jsr     steaxysp
	lda     #$80
	sta     (sp)
	ldy     #$11
	lda     (sp),y
	ldx     #$00
	jsr     _lfill
	ldy     #$05
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	lda     #$AD
	sta     (ptr1)
	ldy     #$0C
	lda     (sp),y
	clc
	ldy     #$04
	adc     (sp),y
	pha
	lda     #$00
	iny
	adc     (sp),y
	tax
	pla
	sec
	sbc     #$01
	bcs     L0054
	dex
L0054:	sta     ptr1
	stx     ptr1+1
	lda     #$BD
	sta     (ptr1)
L0007:	ldy     #$0F
	jmp     addysp

.endproc

; ---------------------------------------------------------------
; unsigned char __near__ panel (unsigned char, unsigned char, unsigned char, unsigned char, unsigned char *, unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_panel: near

.segment	"CODE"

	jsr     pusha
	lda     #$00
	jsr     pusha
	jsr     decsp5
	ldy     #$0C
	lda     (sp),y
	ldy     #$03
	sta     (sp),y
	ldy     #$0B
	lda     (sp),y
	ldy     #$02
	sta     (sp),y
	ldy     #$0A
	lda     (sp),y
	ldy     #$01
	sta     (sp),y
	ldy     #$09
	lda     (sp),y
	sta     (sp)
	ldy     #$06
	lda     (sp),y
	jsr     _rectangle
	bra     L0061
L005F:	ldy     #$01
	lda     (sp),y
	ina
	sta     (sp),y
L0061:	ldy     #$04
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	ldy     #$01
	lda     (sp),y
	tay
	lda     (ptr1),y
	beq     L0094
	ldy     #$01
	lda     (sp),y
	ldy     #$06
	cmp     (sp),y
	bcc     L005F
	bra     L009F
L0094:	ldy     #$06
L009F:	lda     (sp),y
	sec
	ldy     #$01
	sbc     (sp),y
	clc
	adc     #$02
	ror     a
	clc
	ldy     #$08
	adc     (sp),y
	jsr     pusha
	ldy     #$08
	lda     (sp),y
	ina
	jsr     _gotoxy
	lda     #$00
	bra     L00A0
L006F:	ldy     #$04
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	lda     (sp)
	tay
	lda     (ptr1),y
	jsr     _cputc
	lda     (sp)
	ina
L00A0:	sta     (sp)
	lda     (sp)
	jsr     pusha0
	ldy     #$08
	lda     (sp),y
	sec
	sbc     #$02
	bcs     L0073
	ldx     #$FF
L0073:	jsr     tosicmp
	bcs     L0095
	lda     (sp)
	ldy     #$01
	cmp     (sp),y
	bcc     L006F
L0095:	ldy     #$08
	lda     (sp),y
	jsr     pusha
	ldy     #$08
	lda     (sp),y
	clc
	adc     #$02
	jsr     _gotoxy
	lda     #$AB
	jsr     _cputc
	lda     #$00
L00A1:	sta     (sp)
	lda     (sp)
	jsr     pusha0
	ldy     #$08
	lda     (sp),y
	sec
	sbc     #$02
	bcs     L0087
	ldx     #$FF
L0087:	jsr     tosicmp
	bcs     L0081
	lda     #$80
	jsr     _cputc
	lda     (sp)
	ina
	bra     L00A1
L0081:	lda     #$B3
	jsr     _cputc
	ldx     #$00
	txa
	ldy     #$09
	jmp     addysp

.endproc

