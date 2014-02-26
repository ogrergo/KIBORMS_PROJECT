#ifndef DEBUG_MACRO_H_INCLUDED
#define DEBUG_MACRO_H_INCLUDED

#include <stdio.h>

#define DEBUG_EN

#ifdef DEBUG_EN
#define DBG(...) do{ printf("[%s : l.%d] ",__FILE__,__LINE__); printf(__VA_ARGS__); printf("\n");}while(0)
#endif // DEBUG_EN

#define MSG(...) do{ printf(__VA_ARGS__); printf("\n");}while(0)

#define ERR(...) do{ fprintf(stderr,"***erreur*** [%s : l.%d] ",__FILE__,__LINE__); fprintf(stderr,__VA_ARGS__); fprintf(stderr,"\n");}while(0)

//Flags
#define FAILURE 1
#define SUCCESS 0

#endif // DEBUG_MACRO_H_INCLUDED
