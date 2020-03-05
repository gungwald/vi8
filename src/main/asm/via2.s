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

		org $300

screenx	db	0
screeny	db	0
bufferx	db	0
buffery	db	0
buffer	ds	800		;100 80-char lines
topline	db	0
lnaddrs	da	$400	;Line 0
		da	$480	;Line 1 = lineaddrs + 2
		da	$500	;Line 2 = lineaddrs + 4
