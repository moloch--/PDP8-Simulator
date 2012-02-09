TITLE PDP8-Operate

.data
GroupBase	    DWORD  0h
GroupOneTable   DWORD  clearAccumulator, clearLinkBit, onesComplementAccumulator, 
					   complementLink, incrementAccumulator, rotateRight, rotateLeft, 
					   rotateRightTwice, rotateLeftTwice, sixBitSwap
GroupTwoTable   DWORD  clearAccumulator, skipMinusAccumulator, skipZeroAccumulator,
					   skipNonZeroLink

.code
; === ALL GROUPS ===
accessGroupTable PROC
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
	mov GroupBase, eax
	mov ecx, 7h
	iterate:
		call getCurrentInstruction
		push eax
		call getOffset
		pop ebx
		dec cl
		shr ax, cl
		inc cl
		test ax, ax
		jz continue
		mov ebx, 7h
		sub ebx, ecx
		shl ebx, 2
		mov esi, [GroupBase + ebx]
		call esi
		continue:
	loop iterate
	mov esp, ebp
	pop ebp
	ret
accessGroupTable ENDP

groupOne PROC
	push GroupOneTable
	call accessGroupTable
	pop eax
	ret
groupOne ENDP

groupTwo PROC
	push GroupTwoTable
	call accessGroupTable
	pop eax
	ret
groupTwo ENDP

; === GROUP ONE ===

clearAccumulator PROC
	mov Accumulator, 0h
	ret
clearAccumulator ENDP

clearLinkBit PROC
	mov Link, 0h
	ret
clearLinkBit ENDP

onesComplementAccumulator PROC
	mov Accumulator, 0FFFh
	ret
onesComplementAccumulator ENDP

complementLink PROC
	mov Link, 1h
	ret
complementLink ENDP

incrementAccumulator PROC
	mov ax, Accumulator
	inc eax
	mov Accumulator, ax
	ret
incrementAccumulator ENDP

rotateRight PROC ; Test w/12 bits
	xor eax, eax
	mov ax, Accumulator
	test eax, 1h
	jnz notSigned
	shr eax, 1h
	mov Accumulator, ax
	jmp resume
	notSigned:
	shr eax, 1h
	or eax, 800h
	resume:
	ret
rotateRight ENDP

rotateLeft PROC
	xor eax, eax
	mov ax, Accumulator
	test eax, 800h
	jnz nonZero
	shl eax, 1h
	mov Accumulator, ax
	jmp resume
	nonZero:
	shl eax, 1h
	or eax, 1h
	resume:
	ret
rotateLeft ENDP

rotateRightTwice PROC
	call rotateRight
	call rotateRight
	ret
rotateRightTwice ENDP

rotateLeftTwice PROC
	call rotateLeft
	call rotateLeft
	ret
rotateLeftTwice ENDP

sixBitSwap PROC
	xor eax, eax
	mov ax, Accumulator
	and ax, 0FC0h
	shr ax, 6
	mov bx, ax
	mov ax, Accumulator
	and ax, 03Fh
	shl ax, 6
	or ax, bx
	mov Accumulator, ax
	ret
sixBitSwap ENDP

; === GROUP TWO (OR) ===

skipMinusAccumulator PROC
	xor eax, eax
	mov ax, Accumulator
	shr ax, 0Bh
	test eax, eax
	jz done
	call incrementProgramCounter
	done:	
	ret
skipMinusAccumulator ENDP

skipZeroAccumulator PROC
	xor eax, eax
	mov ax, Accumulator
	jnz done
	call incrementProgramCounter
	done:
	ret
skipZeroAccumulator ENDP

skipNonZeroLink PROC
	xor eax, eax
	mov ax, Link
	test eax, eax
	jz done
	call incrementProgramCounter
	done:
	ret
skipNonZeroLink ENDP

; === GROUP TWO (AND) ===

skipPositiveAccumulator PROC
	xor eax, eax
	mov ax, Accumulator
	and ax, 800h
	jz done
	call incrementProgramCounter
	done:
	ret
skipPositiveAccumulator ENDP

skipNonZeroAccumulator PROC
	xor eax, eax
	mov ax, Accumulator
	test eax, eax
	jz done
	call incrementProgramCounter
	done:
	ret
skipNonZeroAccumulator ENDP

skipZeroLink PROC
	xor eax, eax
	mov ax, Link
	jnz done
	call incrementProgramCounter
	done:
	ret
skipZeroLink ENDP
