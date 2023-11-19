
ENTRY(_start)

_LD_KERNEL_OFFSET = 0xC0000000;
_LD_KERNEL_PHYS_START = 1M;
_LD_KERNEL_START = _LD_KERNEL_PHYS_START + _LD_KERNEL_OFFSET;
_LD_KERNEL_SIZE = _LD_KERNEL_END - _LD_KERNEL_START;

SEARCH_DIR($SYSROOT/lib/);

SECTIONS
{

	. = _LD_KERNEL_PHYS_START;

	.multiboot :
	{
		KEEP(* (.multiboot));
		* (.multiboot.bss);
	}

	. += _LD_KERNEL_OFFSET;

	.text ALIGN (4K) : AT ( ADDR( .text ) - _LD_KERNEL_OFFSET )
	{
		* (.text);
	}


	.data ALIGN (4K) : AT ( ADDR( .data ) - _LD_KERNEL_OFFSET )
	{
		* (.data);
	}

	.rodata ALIGN (4K) : AT ( ADDR( .rodata ) - _LD_KERNEL_OFFSET )
	{
		* (.rodata);
	}

	.bss ALIGN (4K) : AT ( ADDR( .bss ) - _LD_KERNEL_OFFSET )
	{
		*(COMMON)
		* (.bss);
	}

	_LD_KERNEL_END = .;

	. = ALIGN (4K); 
}
