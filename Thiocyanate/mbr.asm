BITS    16
ORG     0x7c00

start:
		; clear screen
		mov ah, 0x07
		mov al, 0x00
		mov bh, 0x09  ; color
		mov cx, 0x0000 ; select all
		mov dx, 0x184f
		int 0x10

		mov ax,cs
		mov ds,ax
		mov si,msg
		; print
		cld
next:
		mov al,[si]
		cmp al,0
		je done
		; print char
		mov ah,0x0e
		int 0x10

		inc si
		jmp next
done:
		cli
		hlt
		jmp $-1

msg: db "kys", 0
times 510 - ($-$$) db 0
dw        0xaa55