
#include <stdint.h>

#include <tty.h>
#include <ttycol.h>

#include <paging.h>

#include <stdio.h>

#include <debug/exec.h>

void kernel_init()
{
	map_pages(0xcf000000, 0xB8000, 0x2000);


	tty_set_buffer((struct textbuffer)
	{
		0xcf000000,
		256,	
	});

	for (unsigned char i = 0;i < 255;i++)
	{
		putchar(i);
	}


	return;
}
