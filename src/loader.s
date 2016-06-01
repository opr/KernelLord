.global loader				# making entry point visible to linker
#.global init_descriptor_tables
.set STACKSIZE,	0x8000			# that is, 32k.
.extern gdt_ptr
.global gdt_flush
.global	idt_flush
.global vgainit
.global init_timer
.global init_keyboard
.global init_exceptions
loader:
	mov	$(stack + STACKSIZE), %esp	# set up the stack
	push	%eax			# Multiboot magic number
	#mov 	%ebx, %eax
	push	%ebx			# Multiboot data structure
	call	init_exceptions
	call 	vgainit
	call 	init_descriptor_tables
	mov		$50, %eax
	push	%eax
	call 	init_timer
	call	init_keyboard
	pop		%eax
	#mov 	%ebx, %rax
	#sti
	call	kmain			# call kernel proper

	cli				# Disable interrupts
hang:
	hlt				# halt machine should kernel return
	jmp	hang
gdt_flush:
	lgdt (gdt_ptr)
	mov	$0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ljmp $0x08,$gflush
gflush:
	ret
idt_flush:
	mov 4(%esp), %eax
	lidt (%eax)
	ret
	
.macro ISR_NOERRCODE code  #; define a macro, taking one parameter
.global isr\code       #; %1 accesses the first parameter.
  isr\code:
    cli
    push $0
    push $\code
    jmp isr_common_stub
.endm

.macro ISR_ERRCODE code
.global isr\code       #; %1 accesses the first parameter.
  isr\code:
    cli
    push $\code
    jmp isr_common_stub
.endm
	
.macro IRQ int, iq
	.global irq\iq
	irq\iq:
		cli
		push  $0
		push $\int
		jmp irq_common_stub
.endm

.extern irq_handler

irq_common_stub:
   pusha                    #; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov %ds, %ax#, ds         #      ; Lower 16-bits of eax = ds.
   push %eax                 #; save the data segment descriptor

   mov $0x10, %ax#, 0x10  #; load the kernel data segment descriptor
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs
   
   call irq_handler

   pop %ebx       # ; reload the original data segment descriptor
   mov %bx, %dx
   mov %bx, %es#, %bx
   mov %bx, %fs
   mov %bx, %gs#, bx

   popa            #         ; Pops edi,esi,ebp...
   add 8, %esp     #; Cleans up the pushed error code and pushed ISR number
   sti
   iret           #; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
	
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31


ISR_NOERRCODE 32
ISR_NOERRCODE 33
ISR_NOERRCODE 34
ISR_NOERRCODE 35
ISR_NOERRCODE 36
ISR_NOERRCODE 37
ISR_NOERRCODE 38
ISR_NOERRCODE 39
ISR_NOERRCODE 40
ISR_NOERRCODE 41
ISR_NOERRCODE 42
ISR_NOERRCODE 43
ISR_NOERRCODE 44
ISR_NOERRCODE 45
ISR_NOERRCODE 46
ISR_NOERRCODE 47

.EXTERN isr_handler]

#; This is our common ISR stub. It saves the processor state, sets
#; up for kernel mode segments, calls the C-level fault handler,
#; and finally restores the stack frame.
isr_common_stub:
   pusha                    #; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov %ds, %ax               #; Lower 16-bits of eax = ds.
   push %eax                 #; save the data segment descriptor

   mov $0x10, %ax#, 0x10  #; load the kernel data segment descriptor
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs

   call isr_handler

   pop %eax        #; reload the original data segment descriptor
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs

   popa            #         ; Pops edi,esi,ebp...
   add $8, %esp    #; Cleans up the pushed error code and pushed ISR number
   sti
   iret 
# reserve initial kernel stack space
.comm stack,	STACKSIZE, 32		# reserve 32k stack on quadword boundary
