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
	bcc     L00A6
	inx
L00A6:	cmp     #$40
	txa
	sbc     #$00
	jcs     L0007
	ldx     #$00
	ldy     #$0B
	lda     (sp),y
	clc
	ldy     #$0D
	adc     (sp),y
	bcc     L00A7
	inx
L00A7:	cmp     #$1E
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
	lda     #$85
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
	lda     #$83
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
	lda     #$84
	sta     (ptr1)
	jsr     decsp5
	ldy     #$08
	jsr     ldeaxysp
	ldy     #$01
	jsr     steaxysp
	ldy     #$0F
	lda     (sp),y
	sta     (sp)
	ldy     #$11
	lda     (sp),y
	ldx     #$00
	jsr     _lfill
	ldy     #$04
	ldx     #$00
	lda     #$40
	jsr     addeqysp
	ldx     #$00
	stz     sreg
	stz     sreg+1
	lda     #$40
	jsr     laddeq0sp
	lda     #$02
	ldy     #$09
L00AA:	sta     (sp),y
	ldy     #$0B
	cmp     (sp),y
	jcs     L0039
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
	lda     #$80
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
	bcs     L004B
	dex
L004B:	sta     ptr1
	stx     ptr1+1
	lda     #$80
	sta     (ptr1)
	jsr     decsp5
	ldy     #$08
	jsr     ldeaxysp
	ldy     #$01
	jsr     steaxysp
	ldy     #$0F
	lda     (sp),y
	sta     (sp)
	ldx     #$00
	lda     #$01
	jsr     _lfill
	jsr     decsp5
	ldy     #$08
	jsr     ldeaxysp
	jsr     pusheax
	ldy     #$15
	ldx     #$00
	lda     (sp),y
	jsr     tosadd0ax
	ldy     #$01
	jsr     deceaxy
	jsr     steaxysp
	ldy     #$0F
	lda     (sp),y
	sta     (sp)
	ldx     #$00
	lda     #$01
	jsr     _lfill
	ldy     #$04
	ldx     #$00
	lda     #$40
	jsr     addeqysp
	ldx     #$00
	stz     sreg
	stz     sreg+1
	lda     #$40
	jsr     laddeq0sp
	ldy     #$09
	lda     (sp),y
	ina
	jmp     L00AA
L0039:	jsr     decsp5
	dey
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	stz     sreg
	stz     sreg+1
	ldy     #$01
	jsr     steaxysp
	lda     #$85
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
	lda     #$81
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
	bcs     L0064
	dex
L0064:	sta     ptr1
	stx     ptr1+1
	lda     #$82
	sta     (ptr1)
	jsr     decsp5
	ldy     #$08
	jsr     ldeaxysp
	ldy     #$01
	jsr     steaxysp
	ldy     #$0F
	lda     (sp),y
	sta     (sp)
	ldy     #$11
	lda     (sp),y
	ldx     #$00
	jsr     _lfill
L0007:	ldy     #$0F
	jmp     addysp

.endproc

; ---------------------------------------------------------------
; void __near__ panel (unsigned char, unsigned char, unsigned char, unsigned char, unsigned char *, unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_panel: near

.segment	"CODE"

	jsr     pusha
	lda     #$00
	jsr     pusha
	jsr     decsp2
	ldx     #$00
	ldy     #$07
	lda     (sp),y
	ldy     #$09
	ora     (sp),y
	and     #$80
	jne     L0097
	ldy     #$06
	lda     (sp),y
	ldy     #$08
	ora     (sp),y
	and     #$80
	jne     L0097
	dey
	lda     (sp),y
	cmp     #$40
	jcs     L0097
	dey
	lda     (sp),y
	cmp     #$1E
	jcs     L0097
	iny
	lda     (sp),y
	clc
	ldy     #$09
	adc     (sp),y
	bcc     L00AB
	inx
L00AB:	cmp     #$40
	txa
	sbc     #$00
	jcs     L0097
	ldx     #$00
	ldy     #$06
	lda     (sp),y
	clc
	ldy     #$08
	adc     (sp),y
	bcc     L00AC
	inx
L00AC:	cmp     #$1E
	txa
	sbc     #$00
	jcs     L0097
	jsr     decsp4
	ldy     #$0D
	lda     (sp),y
	ldy     #$03
	sta     (sp),y
	ldy     #$0C
	lda     (sp),y
	ldy     #$02
	sta     (sp),y
	ldy     #$0B
	lda     (sp),y
	ldy     #$01
	sta     (sp),y
	ldy     #$0A
	lda     (sp),y
	sta     (sp)
	ldy     #$07
	lda     (sp),y
	jsr     _rectangle
	bra     L0085
L0083:	ldy     #$02
	lda     (sp),y
	ina
	sta     (sp),y
L0085:	ldy     #$05
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	ldy     #$02
	lda     (sp),y
	tay
	lda     (ptr1),y
	beq     L00AF
	ldy     #$02
	lda     (sp),y
	ldy     #$07
	cmp     (sp),y
	bcc     L0083
	bra     L00B4
L00AF:	ldy     #$07
L00B4:	lda     (sp),y
	sec
	ldy     #$02
	sbc     (sp),y
	clc
	adc     #$02
	ror     a
	clc
	ldy     #$09
	adc     (sp),y
	sta     (sp)
	lda     #$00
	ldy     #$01
	sta     (sp),y
	jsr     decsp5
	ldy     #$0E
	ldx     #$00
	lda     (sp),y
	jsr     push0ax
	lda     #$F8
	sta     sreg
	lda     #$0F
	sta     sreg+1
	txa
	jsr     tosaddeax
	jsr     pusheax
	ldy     #$11
	ldx     #$00
	lda     (sp),y
	jsr     shlax4
	jsr     shlax2
	jsr     tosadd0ax
	ldy     #$01
	jsr     steaxysp
	lda     #$01
	sta     (sp)
	ldy     #$07
	lda     (sp),y
	ldx     #$00
	jsr     _lfill
	bra     L0098
L0096:	ldy     #$09
	lda     (sp),y
	clc
	adc     #$0A
	sta     ptr1
	lda     #$00
	adc     #$F4
	sta     ptr1+1
	ldy     #$01
	lda     (sp),y
	clc
	adc     ptr1
	ldx     ptr1+1
	bcc     L00AD
	inx
L00AD:	sta     ptr1
	stx     ptr1+1
	ldx     #$00
	ldy     #$08
	lda     (sp),y
	ina
	bne     L00A2
	inx
L00A2:	jsr     shlax4
	jsr     shlax2
	clc
	adc     ptr1
	pha
	txa
	adc     ptr1+1
	tax
	pla
	jsr     pushax
	ldy     #$07
	lda     (sp),y
	sta     ptr1+1
	dey
	lda     (sp),y
	sta     ptr1
	ldy     #$03
	lda     (sp),y
	tay
	lda     (ptr1),y
	ldy     #$00
	jsr     staspidx
	ldy     #$01
	lda     (sp),y
	ina
	sta     (sp),y
L0098:	ldy     #$01
	lda     (sp),y
	jsr     pusha0
	ldy     #$09
	lda     (sp),y
	sec
	sbc     #$02
	bcs     L009A
	ldx     #$FF
L009A:	jsr     tosicmp
	bcs     L0097
	ldy     #$01
	lda     (sp),y
	iny
	cmp     (sp),y
	bcc     L0096
L0097:	ldy     #$0A
	jmp     addysp

.endproc

