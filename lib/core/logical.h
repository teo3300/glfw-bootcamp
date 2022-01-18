#pragma once
#include <stdbool.h>

#define implies(a,b)        ((!(a))||(b))
#define biconditional(a,b)  (implies(a,b) && implies(b,a))
#define exclude(a,b)        (!biconditional(a,b))