SCREEN_WIDTH	= 40
SCREEN_HEIGHT	= 24
BUFFER_WIDTH	= 64
BUFFER_HEIGHT	= 256
LINE_ADDRESS	= 6
BUFFER_ADDRESS	= 8

.segment	"CODE"

		; Clear the decimal flag to make sure all arithmetic is done in
		; integer mode, not BCD.
		cld

		; X holds the screen line number (yes it should be Y but addressing-modes)
		ldx	#0

		; Init starting line in buffer
		lda	topLeftScreenY
		sta	displayBufferY

nextLine:
		; Get address of line X
		lda	lineAddresses,x
		sta	LINE_ADDRESS
		inx
		lda	lineAddresses,x
		sta	LINE_ADDRESS+1

		ldy	#0			; Set to column 0

		; Init starting column in buffer
		lda	topLeftScreenX
		sta	displayBufferX

		; Get starting address of line in buffer
		jsr	getBufferAddress

nextChar:
		lda	BUFFER_ADDRESS,y
		sta	(LINE_ADDRESS),y

		; TODO - Add check for end-of-line in buffer

		iny
		cpy	#SCREEN_WIDTH
		bmi	nextChar

		; Increment buffer line
		inc	displayBufferY

		inx
		cpx	#SCREEN_HEIGHT * 2
		bmi	nextLine
		rts

; BUFFER_ADDRESS = buffer[displayBufferY][displayBufferX]
; BUFFER_ADDRESS = buffer + (displayBufferY * BUFFER_WIDTH) + displayBufferX 
getBufferAddress:
		lda	#0
		sta	BUFFER_ADDRESS+1

		lda	displayBufferY

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

;;;;;;;;;;;;;;;

.segment "DATA"

lineAddresses::	.addr	$0400,$0480,$0500,$0580,$0600,$0680,$0700,$0780,$0428,$04A8
		.addr	$0528,$05A8,$0628,$06A8,$0728,$07A8,$0450,$04D0,$0550,$05D0
		.addr	$0650,$06D0,$0750,$07D0

buffer:		.res	BUFFER_WIDTH * BUFFER_HEIGHT,0
lineLengths:	.res	BUFFER_WIDTH,0
screenCursorX:	.byte	0
screenCursorY:	.byte	0
topLeftScreenX:	.byte	0
topLeftScreenY:	.byte	0
bufferLength:	.byte	0
bufferCursorX:	.byte	0
bufferCursorY:	.byte	0
displayBufferX:	.byte	0
displayBufferY:	.byte	0
displayScreenX:	.byte	0
displayScreenY:	.byte	0

