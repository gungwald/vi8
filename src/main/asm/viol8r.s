		typ $ff			;File type of generated executable to be SYSTEM
		dsk viol8r.b	;Specify name of executable for following code

		use symbols		;Include equates
		use macros		;Include macros

bufmaxx equ 80
bufmaxy equ	100

* Translate a line to its memory address
* ]1 - The line number, 0-based
* ]2 - Address for the result, zero-page or absolute
ln2addr	mac
		lda	]1
		asl				;Shift left to multiply by 2
		tax				;Move offset into X
		lda	lnaddrs,x	;Load low byte of line address
		sta	]2			;Store low byte at result address
		inx				;Move to high byte
		lda lnaddrs,x	;Load high byte of line address
		sta ]2+1		;Store high byte at result address
		eom

dline	mac
		eom

draw	mac
		lda #0
		sta	yindex
nextln  cmp linecnt
		bge enddraw
		>>>	dline(yindex
		inc	yindex
		lda	yindex
		jmp nextln
enddraw eom

* Main program
		org $2000
main	>>>	draw
		rts

linecnt db  0
yindex 	db	0
xindex	db	0
screenx	db	0
screeny	db	0
bufferx	db	0
buffery	db	0
buffer	ds	800		;100 80-char lines
topline	db	0
lnaddrs	da	$400	;Line 0
		da	$480	;Line 1 = lineaddrs + 2
		da	$500	;Line 2 = lineaddrs + 4
