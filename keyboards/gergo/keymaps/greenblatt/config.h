#pragma once

#define IGNORE_MOD_TAP_INTERRUPT
#define USB_POLLING_INTERVAL_MS 2

#define LARGE_FILE

#ifdef LARGE_FILE
#    define NO_ACTION_LAYER
#    define NO_ACTION_TAPPING
#    define NO_ACTION_ONESHOT
#    ifndef NO_DEBUG
#        define NO_DEBUG
#    endif
#    if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#        define NO_PRINT
#    endif
#endif
