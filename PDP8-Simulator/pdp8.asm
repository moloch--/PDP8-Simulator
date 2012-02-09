TITLE PDP8-Simulator
; =================================================================
;	Author: Moloch
;	Last Updated: 04/25/2011
;	Architecture: Intel x86
;	About: PDP8 simulator, written in Microsoft macro assembly
;		   compiled and tested on Windows 7 w/Visual Studio 2010
; =================================================================
INCLUDE Irvine32.inc
INCLUDE pdp8-ui.inc
INCLUDE pdp8-iot.inc
INCLUDE pdp8-exec.inc
INCLUDE pdp8-operate.inc

.data
Accumulator			WORD	0h
InterruptFlag		DWORD	0h
ProgramCounter		DWORD	128d
Link			WORD	0
Memory			WORD	128 DUP(0), 110011111111b, 4063 DUP(0)
CurrentInstruction	WORD	0
InstructionTable	DWORD	andAccumulator, twosAdd, incrementSkipZero,
							depositClearAccumulator, jumpSubroutine, jump,
							ioTransfer, operate

.code
getCurrentInstruction PROC
	xor eax, eax
	mov esi, ProgramCounter
	mov ax, Memory[esi * TYPE Memory]
	mov currentInstruction, ax
	ret
getCurrentInstruction ENDP

incrementProgramCounter PROC
	mov eax, ProgramCounter
	inc eax
	mov ProgramCounter, eax
	ret
incrementProgramCounter ENDP

executeInstruction PROC
	call getCurrentInstruction
	push eax
	call getOpCode
	mov esi, 0h
	mov esi, [InstructionTable + eax]
	call esi
	pop eax
	ret	
executeInstruction ENDP

cycle PROC
	mov ecx, 1h
	cpuCycle:
		push ecx
		call executeInstruction
		call incrementProgramCounter
		pop ecx
	loop cpuCycle
	ret
cycle ENDP

main PROC
	call printSplash
	call cycle
	ret
main ENDP

END main

END
