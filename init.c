// init.c

extern char _etext, _data,
	    _edata, _bstart, _bend;

//Étant initialiée, dst ne seront pas être mises en zéro elles-mêmes.
//static unsigned int *src = &_etext;
static unsigned int *dst = &_data;

// ROM has placed .data at end of .text.
// Copy .data to RAM
//while (dst < &_edata)
// *dst++ = *src++;

void init_bss(){
  // Zero out bss
  for (dst = &_bstart; dst < &_bend; dst++)
    *dst = 0;
}
