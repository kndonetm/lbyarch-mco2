; assembly part using x86-64

section .data
formatString db '%f', 13, 10, 0
zero dd 0.0
result dd 0.0

section .text
bits 64
default rel

extern printf
global asmDotProduct

asmDotProduct:
	sub rsp, 8*5
	; Arguments:
	; rcx - first vector
	; rdx - second vector
	; r8 - number of elements in each vector
	
	; xmm1 stores the current sum 
	movss xmm0, [zero]
	
	; move the first and second vectors to rsi, rdi respectively
	mov rsi, rcx
	mov rdi, rdx

	; move the counter to rcx
	mov rcx, r8
L1:
	movss xmm1, [rsi]
	movss xmm2, [rdi]

	mulss xmm1, xmm2
	addss xmm0, xmm1

	add rsi, 4
	add rdi, 4
	loop L1

	add rsp, 8*5
	ret