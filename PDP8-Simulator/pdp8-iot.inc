TITLE PDP8-InputOutputTransfer

.data
ReadyFlag		DWORD 0h
Devices			DWORD iotProcessor, paperTapeReader, paperTapePunch,
					  consoleKeyboard, consolePrinter
TapeReader		BYTE  "[*] Paper Tape Reader: ", 0
TapePunch		BYTE  "[*] Paper Tape Punch: ", 0
Printer			BYTE  "[*] Console Printer: ", 0

.code
; === ALL I/O TRANSFER ===
getDevice PROC
	push ebp
	mov esp, ebp
	xor eax, eax
	mov eax, [ebp + 8]
	and ax, 1F8h
	shr ax, 3
	mov esp, ebp
	pop ebp
	ret
getDevice ENDP

; === INPUT ===

iotProcessor PROC
	mov InterruptFlag, 1h
	ret
iotProcessor ENDP

consoleKeyboard PROC
	mov InterruptFlag, 1h
	ret
consoleKeyboard ENDP

; === OUTPUT ===

paperTapeReader PROC
	mov edx, offset TapeReader
	call writeString
	ret
paperTapeReader ENDP

paperTapePunch PROC
	mov edx, offset TapePunch
	call writeString
	ret
paperTapePunch ENDP

consolePrinter PROC
	mov edx, offset Printer
	call writeString
	ret
consolePrinter ENDP
