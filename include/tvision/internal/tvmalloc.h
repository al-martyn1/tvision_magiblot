#pragma once

#include "../ttypes.h"

namespace tvision {

void *tvMalloc( size_t size );
void  tvFree( void *ptr );
void *tvRealloc( void *ptr, size_t new_size );


} // namespace tvision

