#ifndef DOCDB_TYPES_H
#define DOCDB_TYPES_H

typedef size_t DocNat;
typedef long DocInt;
typedef double DocBFloat;
typedef size_t DocDFloat;

typedef char DocNull;

#define DOC_NULL(v) (v) == 0

typedef char DocBoolean;

#define DOC_TRUE(v) (v) > 0
#define DOC_FALSE(v) (v) < 0
#define DOC_UNKNOWN(v) (v) == 0

typedef struct
{
    size_t frac;
    size_t val;
} DocFixedPoint;

typedef struct
{
    double real;
    double imag;
} DocComplex;

#endif
