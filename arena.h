#ifndef DOCDB_ARENA_H
#define DOCDB_ARENA_H

typedef struct
{
    size_t len;
    char* str;
} StringView;

typedef struct
{
    char* buffer;
    size_t next;
    size_t capacity;
} Arena;
Arena arena_init(size_t capacity)
{
    Arena a;
    a.buffer = calloc(capacity, sizeof(char));
    a.capacity = capacity;
    a.next = 0;
    return a;
}
void arena_destroy(Arena* arena)
{
    free(arena);
}
char* arena_alloc(Arena* arena, size_t size)
{
    if(arena->next + size <= arena->capacity)
    {
        char* next = arena->buffer + arena->next;
        arena->next += size;
        return next;
    }
    else
        return NULL;
}
StringView arena_fmap(Arena* arena, char* file, char* mode)
{
    FILE* fp = fopen(file, mode);
    fseek(fp, 0, SEEK_END);
    StringView sv;
    sv.len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    sv.str = arena_alloc(arena, sv.len);
    fread((void*)sv.str, sv.len, sizeof(char), fp);
    fclose(fp);
    return sv;
}
// ================================================================
// ====================== DOCDB ===================================
// ================================================================

#endif
