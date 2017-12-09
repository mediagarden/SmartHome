#include "WIFISocketDebug.h"
WIFISocketDebugClass WIFISocketDebug;

WIFISocketDebugClass::WIFISocketDebugClass()
{
  this->serial = &Serial;
  this->level = DEBUG;
}
void WIFISocketDebugClass::begin(HardwareSerial* serial, DEBUG_LEVEL level)
{
  this->serial = serial;
  this->level = level;
}
void WIFISocketDebugClass::begin(DEBUG_LEVEL level)
{
  this->level = level;
}
void WIFISocketDebugClass::SetDebugLevel(DEBUG_LEVEL level)
{
  this->level = level;
}
DEBUG_LEVEL WIFISocketDebugClass::GetDebugLevel()
{
  return this->level;
}
void WIFISocketDebugClass::Debug(const char *format, ...)
{
  if (this->level == FATAL || this->level == ERROR || this->level == WARN)
  {
    return;
  }
  va_list arg;
  va_start(arg, format);
  while (*format)
  {
    char ret = *format;
    if (ret == '%')
    {
      switch (*++format)
      {
        case 'd':
          {
            int val = va_arg(arg, int);
            serial->print(val);
            break;
          }
        case 'c':
          {
            char ch = va_arg(arg, char);
            serial->print(ch);
            break;
          }
        case 's':
          {
            char *pc = va_arg(arg, char *);
            while (*pc)
            {
              serial->print(*pc);
              pc++;
            }
            break;
          }
        default:
          break;
      }
    }
    else
    {
      serial->print(*format);
    }
    format++;
  }
  va_end(arg);
  serial->print('\n');
}
void WIFISocketDebugClass::Warning(const char *format, ...)
{
  if (this->level == FATAL || this->level == ERROR)
  {
    return;
  }
  va_list arg;
  va_start(arg, format);
  while (*format)
  {
    char ret = *format;
    if (ret == '%')
    {
      switch (*++format)
      {
        case 'd':
          {
            int val = va_arg(arg, int);
            serial->print(val);
            break;
          }
        case 'c':
          {
            char ch = va_arg(arg, char);
            serial->print(ch);
            break;
          }
        case 's':
          {
            char *pc = va_arg(arg, char *);
            while (*pc)
            {
              serial->print(*pc);
              pc++;
            }
            break;
          }
        default:
          break;
      }
    }
    else
    {
      serial->print(*format);
    }
    format++;
  }
  va_end(arg);
  serial->print('\n');
}
void WIFISocketDebugClass::Error(const char *format, ...)
{
  if (this->level == FATAL)
  {
    return;
  }
  va_list arg;
  va_start(arg, format);
  while (*format)
  {
    char ret = *format;
    if (ret == '%')
    {
      switch (*++format)
      {
        case 'd':
          {
            int val = va_arg(arg, int);
            serial->print(val);
            break;
          }
        case 'c':
          {
            char ch = va_arg(arg, char);
            serial->print(ch);
            break;
          }
        case 's':
          {
            char *pc = va_arg(arg, char *);
            while (*pc)
            {
              serial->print(*pc);
              pc++;
            }
            break;
          }
        default:
          break;
      }
    }
    else
    {
      serial->print(*format);
    }
    format++;
  }
  va_end(arg);
  serial->print('\n');
}
void WIFISocketDebugClass::Fatal(const char *format, ...)
{
  va_list arg;
  va_start(arg, format);
  while (*format)
  {
    char ret = *format;
    if (ret == '%')
    {
      switch (*++format)
      {
        case 'd':
          {
            int val = va_arg(arg, int);
            serial->print(val);
            break;
          }
        case 'c':
          {
            char ch = va_arg(arg, char);
            serial->print(ch);
            break;
          }
        case 's':
          {
            char *pc = va_arg(arg, char *);
            while (*pc)
            {
              serial->print(*pc);
              pc++;
            }
            break;
          }
        default:
          break;
      }
    }
    else
    {
      serial->print(*format);
    }
    format++;
  }
  va_end(arg);
  serial->print('\n');
}

