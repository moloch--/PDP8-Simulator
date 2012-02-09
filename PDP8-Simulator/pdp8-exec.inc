TITLE PDP8-Executable

.code
andAccumulator PROC
	call getCurrentInstruction
	push eax
	call getOffset
	mov esi, eax
	mov ax, Memory[esi * TYPE Memory]
	pop ebx
	xor ebx, ebx
	mov bx, Accumulator
	and ebx, eax
	mov Accumulator, bx
	ret
andAccumulator ENDP

twosAdd PROC
	call getCurrentInstruction
	push eax
	call getOffset
	mov esi, eax
	xor eax, eax
	mov ax, Memory[esi * TYPE Memory]
	xor ebx, ebx
	mov bx, Accumulator
	add eax, ebx
	mov Accumulator, ax
	ret
twosAdd ENDP

incrementSkipZero PROC
	call getCurrentInstruction
	push eax
	call getOffset
	inc eax
	test eax, eax
	jnz return
	inc ProgramCounter
	return:
	ret
incrementSkipZero ENDP

depositClearAccumulator PROC
	call getCurrentInstruction
	push eax
	call getOffset
	xor eax, eax
	mov ax, Accumulator
	mov [esi * TYPE Memory], ax
	mov Accumulator, 0h
	ret
depositClearAccumulator ENDP

jumpSubroutine PROC
	call getCurrentInstruction
	push eax
	call getOffset
	mov ebx, eax
	inc ebx
	mov ProgramCounter, ebx
	mov [esi * TYPE Memory], ax
	ret
jumpSubroutine ENDP

jump PROC
	call getCurrentInstruction
	push eax
	call getOffset
	mov ProgramCounter, eax
	ret
jump ENDP

ioTransfer PROC
	call getCurrentInstruction
	push eax
	call getDevice
	ret
ioTransfer ENDP

operate PROC
	call getCurrentInstruction
	push eax
	call getIndirect
	pop ebx
	test eax, eax
	jnz Continue
	call groupOne
	Continue:
	ret
operate ENDP

getValueAt PROC
	push ebp
	mov ebp, esp
	mov esi, [ebp +8]
	mov ax, Memory[esi * TYPE Memory] 
	mov esp, ebp
	pop ebp
	ret
getValueAt ENDP

getOpCode PROC
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
	and eax, 000000E00h
	shr ax, 7h
	mov esp, ebp
	pop ebp
	ret
getOpCode ENDP

getIndirect PROC
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
	and eax, 000000100h
	shr ax, 8h
	pop ebp
	ret
getIndirect ENDP

getPageBit PROC
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
	and eax, 000000080h
	shr ax, 7h
	pop ebp
	ret
getPageBit ENDP

getOffset PROC
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
	and eax, 00000007Fh
	pop ebp
	ret
getOffset ENDP