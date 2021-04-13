#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern bool hFlag;
extern bool vFlag;
extern bool dFlag;
extern bool lFlag;
extern bool wFlag;
extern bool xFlag;

extern size_t dFlagindex;
extern size_t lFlagindex;
extern size_t wFlagindex;

extern int64_t lFlaglow;
extern int64_t lFlaghigh;

extern int argi;
extern char **args;

extern char *delim;

#endif
