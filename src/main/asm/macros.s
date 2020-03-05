********************************
*                              *
* PUTS MACRO                   *
*                              *
* APPLESOFT MUST BE IN MEMORY  *
* BECAUSE THE STROUT SUB IS    *
* USED.                        *
*                              *
* X & Y ARE PRESERVED          *
*                              *
* ]1 - ADDRESS OF STRING       *
*                              *
********************************

PUTS           MAC
               TYA              ;PRESERVE Y
               PHA
               LDA   #<]1       ;PUT LOW BYTE INTO A
               LDY   #>]1       ;PUT HIGH BYTE INTO Y
               JSR   STROUT     ;CALL APPLESOFT'S STRING PRINT
               PLA              ;RESTORE Y
               TAY
               <<<

********************************
*                              *
* PUTS80 MACRO                 *
*                              *
* IN 80-COL MODE EVEN COLUMNS  *
* ARE IN AUXILIARY MEMORY      *
* WHILE ODD COLUMNS ARE IN     *
* MAIN MEMORY.                 *
*                              *
* ]1 - CHARACTER TO DISPLAY    *
* ]2 - DESIRED COLUMN          *
*                              *
********************************

PUTS80         MAC
               TYA              ;MOVE Y TO A
               PHA              ;SAVE Y VALUE ON STACK
               SEI              ;DISABLE INTERRUPTS
               STA   STOR80ON   ;ENABLE MAIN/AUX MEM SWITCHING
               LDA   ]2         ;LOAD 80-COL HORIZ CURSOR POSITN
               LSR   A          ;DIVIDE BY 2 TO CALC PHYS COLUMN
               BCC   AUXMEM     ;IF EVEN, COLUMN IS IN AUX MEM
MAINMEM        STA   PAGE2OFF   ;TURN OFF AUX MEM, MAIN MEM ON
               JMP   CONTINUE   ;AVOID AUX MEM ENABLE
AUXMEM         STA   PAGE2ON    ;TURN ON AUX MEM, MAIN MEM OFF
CONTINUE       TAY              ;MOVE CURSOR POSITION TO Y
               LDA   ]1         ;LOAD THE CHARACTER TO DISPLAY
               STA   (BASL),Y   ;DISPLAY THE CHARACTER
               STA   PAGE2OFF   ;TURN MAIN MEM BACK ON
               CLI              ;ENABLE INTERRUPTS
               PLA              ;PULL Y VALUE FROM STACK
               TAY              ;RESTORE Y VALUE
               <<<




********************************
*                              *
* GETKEY MACRO                 *
*                              *
********************************

GETKEY      MAC
            BIT   KBD        ;TEST FOR KEY PRESSED
            BPL   GETKEY     ;WAIT FOR KEY PRESSED
            LDA   KBD        ;GET THE KEY THAT WAS PRESSED
            BIT   KBDSTRB    ;CLEAR KEYBOARD STROBE
            STA   ]1         ;STORE THE KEY THAT WAS READ
            <<<



********************************
*                              *
* PUTSCUSTOM MACRO             *
*                              *
********************************

PUTSCUSTOM     MAC
               TYA              ;PRESERVE Y
               PHA
               LDY   #0         ;PREPARE LOOP INDEX
]NEXTCHR       LDA   ]1,Y       ;LOAD A CHARACTER
               CMP   #0         ;CHECK FOR END OF STRING
               BEQ   FINISH
               JSR   COUT
               INY
               JMP   ]NEXTCHR
FINISH         PLA              ;RESTORE Y
               TAY
               <<<

********************************
*                              *
* PAUSE Macro                  *
*                              *
********************************

PAUSE          MAC
               PUTS  ]1
               JSR   RDKEY
               JSR   CROUT
               <<<

********************************
*                              *
* ADD_TO_ADDR MACRO            *
*                              *
********************************

ADD_TO_ADDR    MAC
               LDA   ]1
               CLC
               ADC   ]2
               STA   ]1
               BCC   DONE
               INC   ]1+1
DONE           <<<

