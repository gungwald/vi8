********************************
*                              *
* SYMBOLS REFERENCING SYSTEM   *
* RESOURCES                    *
*                              *
* AUTHOR:  BILL CHATFIELD      *
* LICENSE: GPL                 *
*                              *
********************************

CH             EQU   $24        ;HORIZ CHAR POS (40-COL)
BASL           EQU   $28        ;BASE ADDR FOR CURR VIDEO LINE
KSWL           EQU   $38        ;KEYBOARD SWITCH LOW BYTE
KSWH           EQU   $39        ;KEYBOARD SWITCH HIGH BYTE
IN             EQU   $200       ;256-CHAR INPUT BUFFER
OURCH          EQU   $57B       ;HORIZONTAL POSITION (80-COL)
OURCV          EQU   $5FB       ;VERTICAL POSITION (80-COL)

* ProDOS Addresses

MLI            EQU   $BF00      ;ADDRESS OF MLI ENTRY POINT

* Memory Mapped Input/Output addresses C000 - CFFF

KBD            EQU   $C000      ;KEYBOARD DATA + STROBE
STOR80ON       EQU   $C001      ;ENABLE AUXILIARY MEM SWITCHING
CXROMOFF       EQU   $C006      ;ENABLE SLOT ROMS
CXROMON        EQU   $C007      ;TURN ON INTERNAL ROM
KBDSTRB        EQU   $C010      ;CLEAR KEYBOARD STROBE
ALTCHAR        EQU   $C01E      ;>=$80 IF IN 80-COL
PAGE2OFF       EQU   $C054      ;TURN ON MAIN MEMORY
PAGE2ON        EQU   $C055      ;TURN ON AUXILIARY MEMORY
BASICIN        EQU   $C305
BINPUT         EQU   $C8F6
ESCAPING       EQU   $C918
NOESC          EQU   $C9B7      ;HANDLES KEY OTHER THAN ESC
INVERT         EQU   $CEDD      ;80-col INVERT CHAR ON SCREEN
PICK           EQU   $CF01      ;80-col PICK CHAR OFF SCREEN

* Subroutines stored in ROM addresses D000 - FFFF

STROUT         EQU   $DB3A      ;BAS? PRINT NULL-TERM STR IN AY
HEXDEC         EQU   $ED24      ;HEX-TO-DECIMAL CONVERSION
PRINTXY        EQU   $F940      ;MONITOR PRINT X & Y AS HEX
RDKEY          EQU   $FD0C      ;READS 1 CHAR
KEYIN          EQU   $FD1B
RDCHAR         EQU   $FD35
GETLN          EQU   $FD6A
CROUT          EQU   $FD8E      ;PRINT A CARRIAGE RETURN
PRBYTE         EQU   $FDDA      ;MONITOR PRINT BYTE 2 HEX DIGITS
COUT           EQU   $FDED      ;WRITE A CHARACTER
BELL           EQU   $FF3A      ;SUBROUTINE TO BEEP

* Keyboard key code definitions

ESC            EQU   $9B        ;ESC WITH HIGH BIT SET
RTARROW        EQU   $95        ;RIGHT ARROW WITH HIGH BIT SET
DELETE         EQU   $FF        ;DELETE WITH HIGH BIT SET
BKSPACE        EQU   $88        ;BACKSPACE WITH HIGH BIT SET

* ProDOS command definitions

ON_LINE        EQU   $C5        ;ID FOR ON_LINE MLI SYSTEM CALL

