SCREEN_WIDTH	= 40
SCREEN_HEIGHT	= 24
BUFFER_WIDTH	= 64
BUFFER_HEIGHT	= 256
LINE_ADDRESS	= 6
BUFFER_ADDRESS	= 8

.segment "CODE"

.macro	copy	dest,src
	lda	src
	sta	dest
.endmacro

.macro	copyix	dest,src
	copy	dest,{src,X}
	inx
	copy	dest+1,{src,X}
.endmacro

main:	
	cld					; Ensure integer mode, not BCD
	ldx	#0				; X holds the screen line number
	copy	bufferLine,topLine

nextLine:
	copyix	LINE_ADDRESS,lineAddresses	; Address of beginning of line
	ldy	#0				; Y holds the screen column number
	copy	bufferColumn,topColumn		; Init starting column in buffer
	jsr	getBufferAddress		; Get start address of line in buffer

nextChar:
	copy	{(LINE_ADDRESS),y},{BUFFER_ADDRESS,y}

	; Progress across columns
	iny					; Increment column
	inc	bufferColumn
	
	lda	bufferColumn			; Check for end-of-line
	cmp	lineLengths,Y
	bmi	widthCheck
	jsr	spacesToEol

widthCheck:
	cpy	#SCREEN_WIDTH
	bmi	nextChar

	; Progress down lines
	inc	bufferLine			; Increment buffer line
	inx

	cpx	#SCREEN_HEIGHT * 2
	bmi	nextLine
	rts

spacesToEol:
	cpy	#SCREEN_WIDTH
	bpl	done
	lda	#$A0				; Space with high-bit set
	iny
	jmp	spacesToEol
done	rts

;
; BUFFER_ADDRESS = buffer[displayBufferY][displayBufferX]
; BUFFER_ADDRESS = buffer + (displayBufferY * BUFFER_WIDTH) + displayBufferX 
;
getBufferAddress:
	lda	#0
	sta	BUFFER_ADDRESS+1

	lda	bufferLine

	; Shift address (2 bytes) left 6 times which is multiply by 64
	asl	a			; Left shift lo-byte in A
	rol	BUFFER_ADDRESS+1	; Left shift carry into hi-byte
	asl	a			; Left shift lo-byte in A
	rol	BUFFER_ADDRESS+1	; Left shift carry into hi-byte
	asl	a			; Left shift lo-byte in A
	rol	BUFFER_ADDRESS+1	; Left shift carry into hi-byte
	asl	a			; Left shift lo-byte in A
	rol	BUFFER_ADDRESS+1	; Left shift carry into hi-byte
	asl	a			; Left shift lo-byte in A
	rol	BUFFER_ADDRESS+1	; Left shift carry into hi-byte
	asl	a			; Left shift lo-byte in A
	rol	BUFFER_ADDRESS+1	; Left shift carry into hi-byte
	sta	BUFFER_ADDRESS
		
	; BUFFER_ADDRESS(lo-byte) = BUFFER_ADDRESS(lo-byte) + buffer(lo-byte)
	clc
	adc	#<buffer
	sta	BUFFER_ADDRESS

	; Same for hi-byte. Previous value of carry is added in auto
	lda	BUFFER_ADDRESS+1
	adc	#>buffer
	sta	BUFFER_ADDRESS+1
	rts

;;;;;;;;;;;;;;

.segment "DATA"

lineAddresses:	.addr	$0400,$0480,$0500,$0580,$0600,$0680,$0700,$0780,$0428,$04A8
		.addr	$0528,$05A8,$0628,$06A8,$0728,$07A8,$0450,$04D0,$0550,$05D0
		.addr	$0650,$06D0,$0750,$07D0

buffer:		.res	BUFFER_WIDTH * BUFFER_HEIGHT,0
lineLengths:	.res	BUFFER_WIDTH,0
screenCursorX:	.byte	0
screenCursorY:	.byte	0
topColumn:	.byte	0
topLine:	.byte	0
bufferLength:	.byte	0
bufferCursorX:	.byte	0
bufferCursorY:	.byte	0
bufferColumn:	.byte	0
bufferLine:	.byte	0
screenColumn:	.byte	0
screenLine:	.byte	0

