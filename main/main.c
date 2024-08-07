#include <stdio.h>
#include "HAL.h"


// static const TAG = "main";


void app_main(void)
{
  surface_dial_init();
  foc_init();
  display_init();
  lvgl_display_init();
}