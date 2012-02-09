TITLE PDP8-UserInterface

.data
UserInput			BYTE	14 DUP(0)
Splash				BYTE	"[*] PDP8 System Boot at Location: ", 0
InstructionPrompt	BYTE	"[+] Enter a new instruction: ", 0
InstructionCount	WORD	0
Address				BYTE	" OFFSET: 0x", 0
Indirect			BYTE	" [>] INDIRECT: ", 0
PageNumber			BYTE	" PAGE: ", 0
DisplayPC			BYTE	"[*] Program Counter: ", 0
Instructions		BYTE	"ADD", 0, "TAD", 0, "ISZ", 0, "DCA", 0, "JMS", 0, "JMP", 0, "IOT", 0, "OPR", 0

.code
printSplash PROC USES eax edx
	 mov edx, offset Splash
	 call WriteString
	 mov eax, ProgramCounter
	 call WriteDec
	 call CrLf
	 ret
printSplash ENDP

printOpCode PROC USES eax edx
	mov ax, CurrentInstruction
	and eax, 000000E00h
	shr ax, 7h
	mov edx, offset Instructions
	add edx, eax
	call WriteString
	ret
printOpCode ENDP
	
printIndirect PROC USES eax edx
	mov ax, CurrentInstruction
	and eax, 000000100h
	shr ax, 8h
	mov edx, offset Indirect
	call WriteString
	call WriteDec
	ret
printIndirect ENDP

printPageNumber PROC USES eax edx
	mov ax, CurrentInstruction
	and eax, 000000080h
	shr ax, 7h
	mov edx, offset PageNumber
	call WriteString
	call WriteDec
	ret
printPageNumber ENDP

printOffset PROC USES eax edx
	mov ax, CurrentInstruction
	and eax, 00000007Fh
	mov edx, offset address
	call WriteString
	call WriteHex
	ret
printOffset ENDP

printAll PROC
	call printOpCode
	call printIndirect
	call printPageNumber
	call printOffset
	call CrLf
	ret
printAll ENDP

printProgramCounter PROC USES eax edx
	mov eax, ProgramCounter
	mov edx, offset DisplayPC
	call WriteString
	call WriteHex
	call CrLf
	ret
printProgramCounter ENDP

printInstructionList PROC USES eax edx ecx
	 mov eax, 1h
	 mov edx, offset Instructions
	 mov cx, 8
	 iterate:
		call WriteString
		shl eax, 1h
	 loop iterate
	 ret
printInstructionList ENDP
