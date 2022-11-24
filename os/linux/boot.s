


.gobal begtext, begdata, begbss, endtext, enddata, endbss  //.表示编译过程的位置计数器
.text   !正文段
begtext:
.data   !数据段
begdata:
.bss    !未初始化数据段
begbss:
.text   !正文段
BOOTSEG = 0x07c0

entry start
start:
    jmpi go, BOOTSEG
go: mov ax, cs
    mov ds, ax
    mov es, ax
    mov [msg1+17], ah
    mov cx, #20
    mov dx, 0x1004
    mov bx, #0x000c
    mov bp, #msg1
    mov ax,  #0x1301
    int 0x10
loopl : jmp loopl
msg1: .ascii "Loading system..."
      .byte 13, 10
.org 510
      .wrod 0xAA55
.text
endtext:
.data
enddata:
.bss
endbss:


