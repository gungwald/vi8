SCREEN_WIDTH	= 40
SCREEN_HEIGHT	= 24
BUFFER_WIDTH	= 64
BUFFER_HEIGHT	= 256
LINE_ADDRESS	= 6
BUFFER_ADDRESS	= 8
bge             = bcs   ; Branch Carry Set is Branch Greater or Equal
blt             = bcc   ; Branch Carry Clear is Branch Less Than

.segment "CODE"

;
; Copies one byte from src address to dest address. 
; A is destroyed.
; 
.macro	cpByte	dest,src
	lda	src
	sta	dest
.endmacro

;
; Copies two bytes from src+X address to dest address and src+X+1 to dest+1.
; A is destroyed.
; X is incremented.
;
.macro	cpWordX dest,src
	cpByte	dest,{src,X}
	inx
	cpByte	dest+1,{src,X}
.endmacro

;
; Add addend2 to addend1 storing the result at addend1.
; A is destroyed.
;
.macro	addWord	addend1,addend2
	lda	addend1
	clc
	adc	addend2
	sta	addend1
	lda	addend1+1
	adc	addend2+1
	sta	addend1+1
.endmacro

;
; Left shift is multiply by 2 ^ count
; 
.macro	shWdLft wordAddress,count
	txa			; Move X to pushing position
	pha			; Store X onto the stack
	ldx	#0		; Begin, initializing X
	lda	wordAddress	; Low byte of what to shift
next:
	asl	a		; Left shift lo-byte in A
	rol	wordAddress+1	; Left shift carry into hi-byte
	inx
	cpx	count
        bcc	next            ; bcc = Branch if X < count
	sta	wordAddress	; Store what we're holding in A
	pla			; Restore X
	tax
.endmacro


;;;;;;;;;;;;;;;;
;              ;
; Main Program ;
;              ;
;;;;;;;;;;;;;;;;
	cld				; Ensure integer mode, not BCD
        jsr     loadTestFile
        jsr     display
        rts

.proc   display
	ldx	#0			; X holds the screen line number
	cpByte	bufferLine,topLine
nextLine:
	cpWordX	LINE_ADDRESS,lineAddresses ; Address of beginning of line
	ldy	#0			; Y holds the screen column number
	cpByte	bufferColumn,topColumn	; Init starting column in buffer
	jsr	getBufferCellAddress	; Get start address of line in buffer
nextChar:
	cpByte	{(LINE_ADDRESS),y},{BUFFER_ADDRESS,y}
	iny			    ; Increment column
	inc	bufferColumn
	
	lda	bufferColumn	    ; Check for end-of-line
	cmp	lineLengths,Y
        bcc	widthCheck  ; Branch if bufferColumn < lineLengths,Y
	jsr	spacesToScreenEdge
        jmp     advanceLine
widthCheck:
	cpy	#SCREEN_WIDTH
        bcc	nextChar            ; Branch if Y < SCREEN_WIDTH
advanceLine:
	inc	bufferLine	    ; Increment buffer line
	inx

	cpx	#SCREEN_HEIGHT * 2
        bcc	nextLine            ; Branch if X < SCREEN_HEIGHT*2
	rts
.endproc

.proc   spacesToScreenEdge
	cpy	#SCREEN_WIDTH
        bcs	done                ; Branch if Y >= SCREEN_WIDTH
	lda	#$A0	    	    ; Space with high-bit set
	iny
        bne	spacesToScreenEdge
done:	rts
.endproc

;
; BUFFER_ADDRESS = buffer[displayBufferY][displayBufferX]
; BUFFER_ADDRESS = buffer + (displayBufferY * BUFFER_WIDTH) + displayBufferX 
;
.proc   getBufferCellAddress
	cpByte	BUFFER_ADDRESS,bufferLine
	cpByte 	BUFFER_ADDRESS+1,#0
	shWdLft	BUFFER_ADDRESS,6	; Multiply by 64
	addWord	BUFFER_ADDRESS,#<buffer
	rts
.endproc

.proc	loadTestFile
	lda	#$40
	sta	buffer
	rts
.endproc

;;;;;;;;;;;;;;;;;;
;                ;
; End of Program ;
;                ;
;;;;;;;;;;;;;;;;;;

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

