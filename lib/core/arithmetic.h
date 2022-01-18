#pragma once

#define max(a,b)    ((a) > (b) ? (a) : (b))
#define min(a,b)    max(b,a)

#define odd(a)     ((a) & 0x1)
#define even(a)    (!odd(a))