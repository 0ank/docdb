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
} ArenaPool;

typedef struct
{
    ArenaPool* pools;
    ArenaPool* pool;        // current pool
    size_t npools;
    size_t pools_capacity; // capacity of the entire arena
    size_t buf_capacity; // capacity of a single pool
} Arena;

void arena_init_pools(Arena* arena, size_t capacity)
{
    arena->pools = calloc(capacity, sizeof(ArenaPool));
    arena->pool = arena->pools;
    arena->pools_capacity = capacity;
}
Arena arena_init(size_t capacity, size_t buf_capacity)
{
    Arena a;
    arena_init_pools(&a, capacity);
    a.pools[0].buffer = calloc(buf_capacity, sizeof(char));
    a.pools[0].capacity = buf_capacity;
    a.buf_capacity = buf_capacity;
    a.npools = 1;
    a.pools[0].next = 0;
    return a;
}
void arena_destroy(Arena* arena)
{
    for(size_t i = 0; i < arena->npools; i++)
        free(arena->pools[i].buffer);
    free(arena->pools);
}
ArenaPool* arena_alloc_pool(Arena* arena)
{
    if(arena->npools + 1 <= arena->pools_capacity)
    {
        (++arena->pool)->buffer = calloc(arena->buf_capacity, sizeof(char));
        arena->pool->capacity = arena->buf_capacity;
        arena->npools++;
        arena->pool->next = 0;
        return arena->pool;
    }
    else return NULL;
}
char* arena_alloc(Arena* arena, size_t size)
{
    if(arena->pool->next + size <= arena->pool->capacity)
    {
        char* next = arena->pool->buffer + arena->pool->next;
        arena->pool->next += size;
        return next;
    }
    else
    {
        // TODO: Implement virtual memory for the arena to not miss any too small pool endings
        // arena_get(addr) => addr - SUM(pool[i].cap) is an offset to the pool the resource is located in
        if(arena_alloc_pool(arena))
            return arena_alloc(arena, size);
        else
            return NULL;
    }
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
