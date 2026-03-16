#include<stdio.h>
#include<stdlib.h>

#include "arena.h"
#include "types.h"



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
