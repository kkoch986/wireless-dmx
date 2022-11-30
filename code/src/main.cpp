
// 250 is the max packet size supproted by esp_now_send
// save the first byte to indicate what page we are sending
#define MAX_BUFFER_SIZE 250
#define CHANNEL_COUNT 512

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

