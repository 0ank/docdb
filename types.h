#ifndef DOCDB_TYPES_H
#define DOCDB_TYPES_H

typedef size_t DocNat;
typedef long DocInt;
typedef double DocBFloat;
typedef size_t DocDFloat;

typedef char DocBoolean;
#define DOC_TRUE 1
#define DOC_FALSE -1
#define DOC_UNKNOWN 0

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
