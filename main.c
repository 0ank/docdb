#include<stdio.h>
#include<stdlib.h>

#include "arena.h"
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

char* null2str(DocNull null)
{
    if(DOC_NULL(null)) return "null";
    else return "<<error: null should be 0>>";
}
char* bool2str(DocBoolean boolean)
{
    if(DOC_TRUE(boolean))    return "true";
    if(DOC_FALSE(boolean))   return "false";
    if(DOC_UNKNOWN(boolean)) return "unknown";
}

int main(int argc, char** argv)
{
    Arena arena = arena_init(1, 1024);
    StringView file = arena_fmap(&arena, "database.lib", "rb");
    DocNat number = docdb_imread_nat(&file);
    DocBoolean boolean = docdb_imread_boolean(&file);
    StringView sv = docdb_imread_string(&file);
    DocNull null = docdb_imread_null(&file);
    printf("number: %lu\n", number);
    printf("boolean: %s\n", bool2str(boolean));
    printf("string: %.*s\n", (int)sv.len, sv.str);
    printf("null: %s\n", null2str(null));
    return 0;
}
