	ORG $300
	
* Get source file name

getSource
	PMC	PUTS    sourcePrompt
    
* Get destination directory

                PUTS	destPrompt

	RTS
	
* Variables

sourcePrompt    asc "File to copy:",00
destPrompt      asc "Directory to copy it to:",00

