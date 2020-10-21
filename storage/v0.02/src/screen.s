.export _writeWithAsm

LINEADDR = 6

.segment	"CODE"

.proc _writeWithAsm: near
.segment	"CODE"
		ldx	#0

nextLine:
		lda	lnAddrs,x
		sta	LINEADDR
		inx
		lda	lnAddrs,x
		sta	LINEADDR+1

		txa					; Character for line is based on line number
		clc
		adc #$C0
		ldy	#0

nextChar:
		sta	(LINEADDR),y
		iny
		cpy	#40
		bmi	nextChar

		inx
		cpx	#48
		bmi	nextLine
		rts
.endproc

.segment "DATA"

lnAddrs:
		.addr	$0400
		.addr	$0480
		.addr	$0500
		.addr	$0580
		.addr	$0600
		.addr	$0680
		.addr	$0700
		.addr	$0780
		.addr	$0428
		.addr	$04A8
		.addr	$0528
		.addr	$05A8
		.addr	$0628
		.addr	$06A8
		.addr	$0728
		.addr	$07A8
		.addr	$0450
		.addr	$04D0
		.addr	$0550
		.addr	$05D0
		.addr	$0650
		.addr	$06D0
		.addr	$0750
		.addr	$07D0
