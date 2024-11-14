// init.c

extern char _etext, _data,
	    _edata, _bstart, _bend;

// dst pointer is initialized when definition,
// so that it won't be put in .bss section itself
static unsigned int *dst = (unsigned int *) &_data;

void init_bss(){
  // Zero out bss
  for (dst = (unsigned int *) &_bstart; dst < (unsigned int *) &_bend; dst++)
    *dst = 0;
}
