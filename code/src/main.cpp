
// 250 is the max packet size supported by esp_now_send
#define MAX_BUFFER_SIZE 250

#ifndef RUN_MODE_CONTROLLER
  #ifndef RUN_MODE_RECEIVER
    #error Run Mode Must Be Specified
  #endif
#endif

#ifdef RUN_MODE_CONTROLLER
#include "./controller.h"
#elif RUN_MODE_RECEIVER
#include "./receiver.h"
#endif

