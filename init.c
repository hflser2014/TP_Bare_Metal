// init.c
extern char _text, _etext, _text_LMA,
      _data, _edata, _data_LMA,
      _bstart, _bend, 
      _vtor, _evtor, _vtor_LMA;

// dst pointer is initialized when definition,
// so that it won't be put in .bss section itself
static unsigned int *dst = (unsigned int *) &_data;

void __attribute__((section(".text.init"))) init_memory(){
  // Zero out bss
  for (dst = (unsigned int *) &_bstart; dst != (unsigned int *) &_bend; dst++){
    *dst = 0;
  }

  // Copy code section
  unsigned int * src = (unsigned int *) &_text_LMA;
  for (dst = (unsigned int *) &_text; dst != (unsigned int *) &_etext; dst++){
    *dst = *src;
    src++;
  }

  // Copy .data section
  src = (unsigned int *) &_data_LMA;
  for (dst = (unsigned int *) &_data; dst != (unsigned int *) &_edata; dst++){
    *dst = *src;
    src++;
  }

  // Copy vector table
  src = (unsigned int *) &_vtor_LMA;
  for (dst = (unsigned int *) &_vtor; dst < (unsigned int *) &_evtor; dst++){
    *dst = *src;
    src++;
  }
}
