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
	.import		_rectangle
	.import		_panel
	.import		_lfill
	.export		_clearScreen
	.export		_displayText
	.export		_layout

.segment	"RODATA"

L0229:
	.byte	$41,$64,$64,$2F,$45,$64,$69,$74,$20,$63,$6F,$6E,$74,$61,$63,$74
	.byte	$00
L01EA:
	.byte	$49,$6E,$63,$6F,$6D,$69,$6E,$67,$20,$63,$61,$6C,$6C,$00
L01E7:
	.byte	$4F,$75,$74,$67,$6F,$69,$6E,$67,$20,$63,$61,$6C,$6C,$00
L01DA:
	.byte	$43,$6F,$6E,$74,$61,$63,$74,$73,$00
L0246:
	.byte	$43,$6F,$6E,$66,$69,$72,$6D,$00
L0258:
	.byte	$44,$65,$6C,$65,$74,$65,$00
L0233:
	.byte	$50,$68,$6F,$6E,$65,$00
L022D:
	.byte	$4E,$61,$6D,$65,$00
L0239:
	.byte	$4D,$61,$69,$6C,$00
L021D:
	.byte	$53,$65,$6E,$64,$00
L01F5:
	.byte	$45,$6E,$64,$00
L0201:
	.byte	$53,$4D,$53,$00

; ---------------------------------------------------------------
; void __near__ clearScreen (void)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_clearScreen: near

.segment	"CODE"

	jsr     decsp4
	lda     #$00
	sta     (sp)
	ldy     #$01
	sta     (sp),y
	iny
	sta     (sp),y
	iny
	sta     (sp),y
L0109:	jsr     ldeax0sp
	cmp     #$80
	txa
	sbc     #$07
	lda     sreg
	sbc     #$00
	lda     sreg+1
	sbc     #$00
	bcs     L0108
	jsr     ldeax0sp
	jsr     pusheax
	ldx     #$F4
	lda     #$00
	jsr     tosadd0ax
	sta     sreg
	stx     sreg+1
	lda     #$20
	sta     (sreg)
	jsr     ldeax0sp
	jsr     saveeax
	ldy     #$01
	jsr     inceaxy
	jsr     steax0sp
	jsr     resteax
	bra     L0109
L0108:	jmp     incsp4

.endproc

; ---------------------------------------------------------------
; void __near__ displayText (__near__ unsigned char *, unsigned long, unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_displayText: near

.segment	"CODE"

	jsr     pusha
	jsr     push0
	jmp     L011A
L0118:	jsr     decsp5
	ldy     #$0B
	jsr     ldeaxysp
	jsr     pusheax
	ldx     #$00
	lda     #$F8
	sta     sreg
	lda     #$0F
	sta     sreg+1
	txa
	jsr     tosaddeax
	jsr     pusheax
	ldy     #$0A
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     tosadd0ax
	ldy     #$01
	jsr     steaxysp
	ldy     #$07
	lda     (sp),y
	sta     (sp)
	ldx     #$00
	lda     #$01
	jsr     _lfill
	ldy     #$06
	jsr     ldeaxysp
	jsr     pusheax
	ldx     #$F4
	lda     #$00
	jsr     tosadd0ax
	jsr     pusheax
	ldy     #$05
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     tosadd0ax
	sta     sreg
	stx     sreg+1
	ldy     #$07
	lda     (sp),y
	clc
	adc     (sp)
	sta     ptr1
	iny
	lda     (sp),y
	ldy     #$01
	adc     (sp),y
	sta     ptr1+1
	lda     (ptr1)
	sta     (sreg)
	ldy     #$01
	lda     (sp),y
	tax
	lda     (sp)
	ina
	bne     L012C
	inx
L012C:	jsr     stax0sp
L011A:	ldy     #$07
	lda     (sp),y
	clc
	adc     (sp)
	sta     ptr1
	iny
	lda     (sp),y
	ldy     #$01
	adc     (sp),y
	sta     ptr1+1
	lda     (ptr1)
	beq     L0116
	ldy     #$01
	lda     (sp),y
	cmp     #$03
	bne     L011E
	lda     (sp)
	cmp     #$E8
L011E:	jcc     L0118
L0116:	ldy     #$09
	jmp     addysp

.endproc

; ---------------------------------------------------------------
; void __near__ layout (unsigned char)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_layout: near

.segment	"RODATA"

L0132:
	.byte	$31,$00
	.res	2,$00
	.byte	$32,$00
	.res	2,$00
	.byte	$33,$00
	.res	2,$00
	.byte	$34,$00
	.res	2,$00
	.byte	$35,$00
	.res	2,$00
	.byte	$36,$00
	.res	2,$00
	.byte	$37,$00
	.res	2,$00
	.byte	$38,$00
	.res	2,$00
	.byte	$39,$00
	.res	2,$00
	.byte	$23,$00
	.res	2,$00
	.byte	$30,$00
	.res	2,$00
	.byte	$2A,$00
	.res	2,$00
	.byte	$41,$64,$64,$00
	.byte	$43,$61,$6C,$00
	.byte	$43,$6C,$72,$00

.segment	"CODE"

	jsr     pusha
	jsr     decsp2
	lda     #$00
	jsr     pusha
	ldy     #$3F
	jsr     subysp
	ldy     #$3B
L0141:	lda     L0132,y
	sta     (sp),y
	dey
	bpl     L0141
	jsr     _clearScreen
	ldy     #$42
	lda     (sp),y
	cmp     #$01
	beq     L0147
	cmp     #$02
	jeq     L0271
	cmp     #$03
	jeq     L01FB
	cmp     #$04
	jeq     L0223
	jmp     L012D
L0147:	jsr     decsp4
	lda     #$00
	ldy     #$03
	sta     (sp),y
	ina
	dey
	sta     (sp),y
	lda     #$15
	dey
	sta     (sp),y
	lda     #$03
	sta     (sp)
	lda     #$06
	jsr     _rectangle
	lda     #$00
	ldy     #$41
L0275:	sta     (sp),y
	cmp     #$0F
	jcs     L014F
	lda     (sp),y
	jsr     pusha0
	lda     #$03
	jsr     tosudiva0
	cpx     #$00
	bne     L0156
	cmp     #$00
	bne     L0156
	lda     #$04
	bra     L0272
L0156:	ldy     #$41
	lda     (sp),y
	jsr     pusha0
	lda     #$03
	jsr     tosudiva0
	cpx     #$00
	bne     L015C
	cmp     #$01
	bne     L015C
	lda     #$09
	bra     L0272
L015C:	ldy     #$41
	lda     (sp),y
	jsr     pusha0
	lda     #$03
	jsr     tosudiva0
	cpx     #$00
	bne     L0162
	cmp     #$02
	bne     L0162
	lda     #$0E
	bra     L0272
L0162:	ldy     #$41
	lda     (sp),y
	jsr     pusha0
	lda     #$03
	jsr     tosudiva0
	cpx     #$00
	bne     L0168
	cmp     #$03
	bne     L0168
	lda     #$13
	bra     L0272
L0168:	lda     #$18
L0272:	ldy     #$3D
	sta     (sp),y
	ldy     #$41
	lda     (sp),y
	jsr     pusha0
	lda     #$03
	jsr     tosumoda0
	jsr     mulax7
	ldy     #$3E
	sta     (sp),y
	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$30
	bcc     L0177
	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$3A
	bcc     L026C
L0177:	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$2A
	beq     L026C
	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$23
	bne     L0173
L026C:	jsr     decsp4
	ldy     #$42
	lda     (sp),y
	ldy     #$03
	sta     (sp),y
	ldy     #$41
	lda     (sp),y
	ldy     #$02
	sta     (sp),y
	lda     #$07
	dey
	sta     (sp),y
	lda     #$05
	sta     (sp)
	ina
	jmp     L0268
L0173:	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$41
	bne     L0186
	jsr     decsp4
	ldy     #$42
	lda     (sp),y
	ldy     #$03
	sta     (sp),y
	ldy     #$41
	lda     (sp),y
	ldy     #$02
	sta     (sp),y
	lda     #$07
	dey
	sta     (sp),y
	lda     #$05
	sta     (sp)
	lda     #$07
	bra     L0268
L0186:	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$43
	bne     L0191
	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	clc
	adc     sp
	sta     ptr1
	txa
	adc     sp+1
	sta     ptr1+1
	ldy     #$01
	lda     (ptr1),y
	cmp     #$61
	bne     L0191
	jsr     decsp4
	ldy     #$42
	lda     (sp),y
	ldy     #$03
	sta     (sp),y
	ldy     #$41
	lda     (sp),y
	ldy     #$02
	sta     (sp),y
	lda     #$07
	dey
	sta     (sp),y
	lda     #$05
	sta     (sp)
	bra     L0268
L0191:	jsr     decsp4
	ldy     #$42
	lda     (sp),y
	ldy     #$03
	sta     (sp),y
	ldy     #$41
	lda     (sp),y
	ldy     #$02
	sta     (sp),y
	lda     #$07
	dey
	sta     (sp),y
	lda     #$05
	sta     (sp)
	lda     #$02
L0268:	jsr     _rectangle
	lda     #$00
	ldy     #$40
	jmp     L0273
L01A8:	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$30
	bcc     L01B2
	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$3A
	bcc     L026F
L01B2:	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$2A
	beq     L026F
	ldy     #$41
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	sta     ptr1
	txa
	clc
	adc     sp+1
	sta     ptr1+1
	ldy     sp
	lda     (ptr1),y
	cmp     #$23
	bne     L0270
L026F:	lda     #$02
	bra     L0274
L0270:	lda     #$01
L0274:	ldy     #$3C
	sta     (sp),y
	ldx     #$00
	ldy     #$40
	lda     (sp),y
	clc
	ldy     #$3E
	adc     (sp),y
	bcc     L0263
	inx
L0263:	sta     ptr1
	stx     ptr1+1
	ldy     #$3C
	lda     (sp),y
	clc
	adc     ptr1
	ldx     ptr1+1
	bcc     L0264
	inx
L0264:	ina
	bne     L01C4
	inx
L01C4:	sta     ptr1
	txa
	clc
	adc     #$F4
	sta     ptr1+1
	ldx     #$00
	iny
	lda     (sp),y
	clc
	adc     #$02
	bcc     L01C6
	inx
L01C6:	jsr     shlax4
	jsr     shlax2
	clc
	adc     ptr1
	pha
	txa
	adc     ptr1+1
	tax
	pla
	jsr     pushax
	ldy     #$43
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	clc
	adc     #$02
	bcc     L01C9
	inx
	clc
L01C9:	adc     sp
	sta     ptr1
	txa
	adc     sp+1
	sta     ptr1+1
	dey
	lda     (sp),y
	tay
	lda     (ptr1),y
	ldy     #$00
	jsr     staspidx
	jsr     decsp5
	ldx     #$00
	ldy     #$45
	lda     (sp),y
	clc
	ldy     #$43
	adc     (sp),y
	bcc     L0265
	inx
L0265:	sta     ptr1
	stx     ptr1+1
	ldy     #$41
	lda     (sp),y
	clc
	adc     ptr1
	ldx     ptr1+1
	bcc     L0266
	inx
L0266:	ina
	bne     L01CF
	inx
L01CF:	jsr     push0ax
	ldx     #$00
	lda     #$F8
	sta     sreg
	lda     #$0F
	sta     sreg+1
	txa
	jsr     tosaddeax
	jsr     pusheax
	ldy     #$46
	ldx     #$00
	lda     (sp),y
	clc
	adc     #$02
	bcc     L01D1
	inx
L01D1:	jsr     shlax4
	jsr     shlax2
	jsr     tosadd0ax
	ldy     #$01
	jsr     steaxysp
	lda     #$01
	sta     (sp)
	ldx     #$00
	jsr     _lfill
	ldy     #$40
	lda     (sp),y
	ina
L0273:	sta     (sp),y
	iny
	ldx     #$00
	lda     (sp),y
	jsr     aslax2
	clc
	adc     sp
	sta     ptr1
	txa
	adc     sp+1
	sta     ptr1+1
	dey
	lda     (sp),y
	tay
	lda     (ptr1),y
	jne     L01A8
	ldy     #$41
	lda     (sp),y
	ina
	jmp     L0275
L014F:	jsr     decsp6
	lda     #$16
	ldy     #$05
	sta     (sp),y
	lda     #$01
	dey
	sta     (sp),y
	lda     #$1C
	dey
	sta     (sp),y
	dey
	sta     (sp),y
	lda     #<(L01DA)
	sta     (sp)
	dey
	lda     #>(L01DA)
	sta     (sp),y
	lda     #$0F
	jsr     _panel
	jmp     L012D
L0271:	dea
	ldy     #$3F
	sta     (sp),y
	jsr     decsp6
	lda     #$00
	ldy     #$05
	sta     (sp),y
	ina
	dey
	sta     (sp),y
	lda     #$32
	dey
	sta     (sp),y
	lda     #$1C
	dey
	sta     (sp),y
	ldy     #$45
	lda     (sp),y
	beq     L01E8
	lda     #<(L01E7)
	ldx     #>(L01E7)
	bra     L01EB
L01E8:	lda     #<(L01EA)
	ldx     #>(L01EA)
L01EB:	sta     (sp)
	ldy     #$01
	txa
	sta     (sp),y
	lda     #$0F
	jsr     _panel
	jsr     decsp4
	lda     #$0A
	ldy     #$03
	sta     (sp),y
	lda     #$16
	dey
	sta     (sp),y
	lda     #$1E
	dey
	sta     (sp),y
	lda     #$05
	sta     (sp)
	lda     #$02
	jsr     _rectangle
	jsr     decsp6
	lda     #<(L01F5)
	ldy     #$04
	sta     (sp),y
	iny
	lda     #>(L01F5)
	sta     (sp),y
	lda     #$18
	jmp     L0280
L01FB:	jsr     decsp6
	lda     #$00
	ldy     #$05
	sta     (sp),y
	ina
	dey
	sta     (sp),y
	lda     #$32
	dey
	sta     (sp),y
	lda     #$1C
	dey
	sta     (sp),y
	lda     #<(L0201)
	sta     (sp)
	dey
	lda     #>(L0201)
	sta     (sp),y
	lda     #$0F
	jsr     _panel
	jsr     decsp5
	ldy     #$01
	lda     #$80
	sta     (sp),y
	lda     #$06
	iny
	sta     (sp),y
	lda     #$F8
	iny
	sta     (sp),y
	lda     #$0F
	iny
	sta     (sp),y
	sta     (sp)
	ldx     #$00
	lda     #$32
	jsr     _lfill
	jsr     decsp5
	ldy     #$01
	lda     #$81
	sta     (sp),y
	lda     #$FA
	iny
	sta     (sp),y
	lda     #$00
	iny
	sta     (sp),y
	iny
	sta     (sp),y
	lda     #$85
	sta     (sp)
	ldx     #$00
	lda     #$30
	jsr     _lfill
	lda     #$86
	sta     $FA80
	ina
	sta     $FAB1
	jsr     decsp6
	lda     #<(L021D)
	ldy     #$04
	sta     (sp),y
	iny
	lda     #>(L021D)
	sta     (sp),y
	lda     #$ED
	jmp     L0280
L0223:	jsr     decsp6
	lda     #$00
	ldy     #$05
	sta     (sp),y
	ina
	dey
	sta     (sp),y
	lda     #$32
	dey
	sta     (sp),y
	lda     #$1C
	dey
	sta     (sp),y
	lda     #<(L0229)
	sta     (sp)
	dey
	lda     #>(L0229)
	sta     (sp),y
	lda     #$0F
	jsr     _panel
	jsr     decsp6
	lda     #<(L022D)
	ldy     #$04
	sta     (sp),y
	iny
	lda     #>(L022D)
	sta     (sp),y
	lda     #$41
	sta     (sp)
	lda     #$01
	tay
	sta     (sp),y
	dea
	iny
	sta     (sp),y
	iny
	sta     (sp),y
	lda     #$0F
	jsr     _displayText
	jsr     decsp6
	lda     #<(L0233)
	ldy     #$04
	sta     (sp),y
	iny
	lda     #>(L0233)
	sta     (sp),y
	lda     #$41
	sta     (sp)
	lda     #$02
	ldy     #$01
	sta     (sp),y
	lda     #$00
	iny
	sta     (sp),y
	iny
	sta     (sp),y
	lda     #$0F
	jsr     _displayText
	jsr     decsp6
	lda     #<(L0239)
	ldy     #$04
	sta     (sp),y
	iny
	lda     #>(L0239)
	sta     (sp),y
	lda     #$41
	sta     (sp)
	lda     #$03
	ldy     #$01
	sta     (sp),y
	lda     #$00
	iny
	sta     (sp),y
	iny
	sta     (sp),y
	lda     #$0F
	jsr     _displayText
	jsr     decsp4
	lda     #$01
	ldy     #$03
	sta     (sp),y
	lda     #$17
	dey
	sta     (sp),y
	ina
	dey
	sta     (sp),y
	lda     #$05
	sta     (sp)
	jsr     _rectangle
	jsr     decsp6
	lda     #<(L0246)
	ldy     #$04
	sta     (sp),y
	iny
	lda     #>(L0246)
	sta     (sp),y
	lda     #$4A
	sta     (sp)
	lda     #$06
	ldy     #$01
	sta     (sp),y
	lda     #$00
	iny
	sta     (sp),y
	iny
	sta     (sp),y
	ina
	jsr     _displayText
	jsr     decsp4
	lda     #$19
	ldy     #$03
	sta     (sp),y
	lda     #$17
	dey
	sta     (sp),y
	ina
	dey
	sta     (sp),y
	lda     #$05
	sta     (sp)
	lda     #$02
	jsr     _rectangle
	jsr     decsp6
	lda     #<(L0258)
	ldy     #$04
	sta     (sp),y
	iny
	lda     #>(L0258)
	sta     (sp),y
	lda     #$62
L0280:	sta     (sp)
	lda     #$06
	ldy     #$01
	sta     (sp),y
	lda     #$00
	iny
	sta     (sp),y
	iny
	sta     (sp),y
	ina
	jsr     _displayText
L012D:	ldy     #$43
	jmp     addysp

.endproc

