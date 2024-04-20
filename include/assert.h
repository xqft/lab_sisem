#pragma once

#include <msp430.h>

#define LED3 (0x0003)

#ifdef DEBUG
#define ASSERT(expr) {\
	if (!(expr)) {\
	P2DIR |= LED3;\
	P2OUT |= LED3;\
	while (1) {};\
	}\
}
#else
#define ASSERT(expr)
#endif
