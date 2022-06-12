
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "iffy.h"

int main( int argc, char** argv ) {
   int retval = 0;
   FILE* iff_file = NULL;
   size_t iff_file_sz = 0,
      iff_read_sz = 0;
   uint8_t* iff_bytes = NULL;
   uint32_t chunk_sz = 0;

   assert( 1 < argc );

   /* Open file. */
   iff_file = fopen( argv[1], "rb" );
   assert( NULL != iff_file );

   /* Get file size. */
   fseek( iff_file, 0, SEEK_END );
   iff_file_sz = ftell( iff_file );
   fseek( iff_file, 0, SEEK_SET );

   /* Allocate/read file. */
   iff_bytes = calloc( iff_file_sz, 1 );
   assert( NULL != iff_bytes );
   iff_read_sz = fread( iff_bytes, 1, iff_file_sz, iff_file );
   assert( iff_read_sz == iff_file_sz );

   assert( 'F' == iff_bytes[0] );
   assert( 'O' == iff_bytes[1] );
   assert( 'R' == iff_bytes[2] );
   assert( 'M' == iff_bytes[3] );

   chunk_sz =  iffy_endian_swap_32( *((uint32_t*)(&(iff_bytes[4]))) );
   printf( "iff_file %s, %u (%lu) bytes long\n", argv[1], chunk_sz, iff_file_sz );
   assert( chunk_sz == iff_file_sz - 8 );

/* cleanup: */

   if( NULL != iff_file ) {
      fclose( iff_file );
   }

   if( NULL != iff_bytes ) {
      free( iff_bytes );
   }

   return retval;
}

