#include <info/multiboot_info.h>

.set PALIGN, 1<<0
.set MEMINFO, 1<<1
.set VIDINFO, 1<<2

.set FLAGS, (PALIGN | MEMINFO | VIDINFO)

.set CHECKSUM, -(MAGIC + FLAGS)

.align MBALIGN
.section .multiboot, "a"
.long MAGIC
.long FLAGS
.long CHECKSUM

.long 0, 0, 0, 0, 0
.long 0 # 0 = set graphics mode
.long 1920, 1080, 32 # Width, height, depth

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .multiboot.bss
.align 4096
boot_table_directory:
.skip 4096
boot_table_kernel:
.skip 4096


.section .text

.extern kernel_init
.extern arch_init

.global _start
.type _start, @function
_start:

	mov $boot_table_directory, %eax
	mov $boot_table_kernel, %edx
	orl $0x3, %edx
	mov %edx, (%eax)
	add $0xc00, %eax
	mov %edx, (%eax)
	mov $boot_table_directory, %eax
	mov %eax, %edx
	orl $0x3, %edx
	add $0xffc, %eax
	mov %edx, (%eax)

	xor %esi, %esi
	mov $boot_table_kernel, %edi
	mov $1024, %ecx
.pagekernel:

	mov %esi, %edx
	orl $0x3, %edx
	mov %edx, (%edi)

	dec %ecx
	addl $4096, %esi 
	add $0x4, %edi 
	test %ecx, %ecx
	jnz .pagekernel

.pagepdir:

	mov $boot_table_directory, %ecx
	mov %ecx, %cr3

	mov %cr0, %eax
	orl $0x80000000, %eax
	mov %eax, %cr0

	mov $.high_entry, %eax
	jmp *%eax
.high_entry:

	movl $0x0, (boot_table_directory) 

	mov $stack_top, %esp
	mov %esp, %ebp
	add $_LD_KERNEL_OFFSET, %ebx
	push %ebx
	call arch_init
	call kernel_init

_exit:	cli
	hlt
	jmp _exit
