#ifndef DOCDB_PRIM_H
#define DOCDB_PRIM_H

#include "types.h"
#include "arena.h"

DocNat docdb_imread_nat(StringView* buf)
{
    DocNat nat = *(DocNat*)(buf->str);
    buf->len -= sizeof(DocNat);
    buf->str += sizeof(DocNat);
    return nat;
}
DocInt docdb_imread_int(StringView* buf)
{
    DocInt int_ = *(DocInt*)(buf->str);
    buf->len -= sizeof(DocInt);
    buf->str += sizeof(DocInt);
    return int_;
}
DocBFloat docdb_imread_bfloat(StringView* buf)
{
    DocBFloat bfloat = *(DocBFloat*)(buf->str);
    buf->len -= sizeof(DocBFloat);
    buf->str += sizeof(DocBFloat);
    return bfloat;
}
DocDFloat docdb_imread_dfloat(StringView* buf)
{
    DocDFloat dfloat = *(DocDFloat*)(buf->str);
    buf->len -= sizeof(DocDFloat);
    buf->str += sizeof(DocDFloat);
    return dfloat;
}
DocFixedPoint docdb_imread_fixed(StringView* buf)
{
    DocFixedPoint fixed = *(DocFixedPoint*)(buf->str);
    buf->len -= sizeof(DocFixedPoint);
    buf->str += sizeof(DocFixedPoint);
    return fixed;
}
DocComplex docdb_imread_complex(StringView* buf)
{
    DocComplex complex = *(DocComplex*)(buf->str);
    buf->len -= sizeof(DocComplex);
    buf->str += sizeof(DocComplex);
    return complex;
}
DocBoolean docdb_imread_boolean(StringView* buf)
{
    DocBoolean boolean = *(DocBoolean*)(buf->str);
    buf->len -= sizeof(DocBoolean);
    buf->str += sizeof(DocBoolean);
    return boolean;
}
StringView docdb_imread_string(StringView* buf)
{
    size_t len = *(size_t*)(buf->str);
    buf->len -= sizeof(size_t);
    buf->str += sizeof(size_t);
    StringView sv;
    sv.len = len;
    sv.str = calloc(len, sizeof(char));
    for(size_t i = 0; i < len; i++)
    {
        sv.str[i] = buf->str[i];
    }
    buf->len -= sizeof(StringView);
    buf->str += sizeof(StringView);
    return sv;
}
DocNull docdb_imread_null(StringView* buf)
{
    DocNull null = *(DocNull*)(buf->str);
    buf->len -= sizeof(DocNull);
    buf->str += sizeof(DocNull);
    if(DOC_NULL(null)); // FIXME: null should be 0
    return null;
}

#endif
