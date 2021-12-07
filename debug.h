#ifndef DEBUG_H
#define DEBUG_H


#define DEBUG

#ifdef DEBUG
#define debug(...) Serial.print(__VA_ARGS__)
#define debugln(...) Serial.println(__VA_ARGS__)
#else
#define debugln(...)
#define debug(...)
#endif


#endif
