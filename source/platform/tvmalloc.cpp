#include <tvision/tv.h>
//
#include <assert.h>
//
#include <mem.h>
//
#include <alloc.h>
//
#include <stdlib.h>
//
#include <tvision/internal/tvmalloc.h>



namespace tvision {

#if defined(TV_BARE_METAL)

// For common version use standard malloc/realloc/free

void *tvMalloc( size_t size )
{
    return malloc(size);
}

void  tvFree( void *ptr )
{
    free(ptr);
}

void *tvRealloc( void *ptr, size_t new_size )
{
    return realloc(ptr, new_size);
}

#endif // TV_BARE_METAL

} // namespace tvision

