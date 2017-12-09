#ifndef __WIFISOCKETDEBUG_H__
#define __WIFISOCKETDEBUG_H__
#include <Arduino.h>
typedef enum DEBUG_LEVEL
{
  DEBUG = 0,
  WARN = 1,
  ERROR = 2,
  FATAL = 3
} DEBUG_LEVEL;
class WIFISocketDebugClass
{
  public:
    WIFISocketDebugClass();
    void begin(HardwareSerial* serial, DEBUG_LEVEL level);
    void begin(DEBUG_LEVEL level = DEBUG);
    void SetDebugLevel(DEBUG_LEVEL level);
    DEBUG_LEVEL GetDebugLevel();
    void Debug(const char* format, ...);
    void Warning(const char* format, ...);
    void Error(const char* format, ...);
    void Fatal(const char* format, ...);
  private:
    DEBUG_LEVEL 	        level;
    HardwareSerial*       serial;
};
extern WIFISocketDebugClass WIFISocketDebug;
#endif
