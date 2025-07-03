#include<stdio.h>
#include<stdlib.h>

#include "types.h"


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
char* bool2str(DocBoolean boolean)
{
    switch(boolean)
    {
    case DOC_TRUE: return "true";
    case DOC_FALSE: return "false";
    case DOC_UNKNOWN: return "unknown";
    default: return NULL;
    }
}

int main(int argc, char** argv)
{
    Arena arena = arena_init(1024);
    StringView file = arena_fmap(&arena, "database.lib", "rb");
    DocNat number = docdb_imread_nat(&file);
    DocBoolean boolean = docdb_imread_boolean(&file);
    printf("number: %lu\n", number);
    printf("boolean: %s\n", bool2str(boolean));
    return 0;
}
