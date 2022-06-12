
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "iffy.h"

#define FILENAME_SZ_MAX 255

int main( int argc, char** argv ) {
   int retval = 0,
      chunk_idx = 0;
   FILE* iff_file = NULL,
      * chunk_file = NULL;
   size_t iff_file_sz = 0,
      iff_read_sz = 0,
      iff_pos = 12;
   uint8_t* iff_bytes = NULL;
   uint32_t chunk_sz = 0;
   char* filename = NULL,
      * filename_dot = NULL,
      chunk_filename[FILENAME_SZ_MAX + 1] = { 0 },
      chunk_type[5] = { 0 };

   assert( 1 < argc );

   filename = argv[1];

   /* Open file. */
   iff_file = fopen( filename, "rb" );
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

   /* Get/verify file size. */
   chunk_sz =  iffy_endian_swap_32( *((uint32_t*)(&(iff_bytes[4]))) );
   printf( "iff_file %s, %u (%lu) bytes long\n",
      filename, chunk_sz, iff_file_sz );
   assert( chunk_sz == iff_file_sz - 8 );

   printf( "FORM type: %c%c%c%c\n", iff_bytes[8], iff_bytes[9], iff_bytes[10], iff_bytes[11] );

   /* Stem filename. */
   filename_dot = strrchr( filename, '.' );
   *filename_dot = '\0';

   /* Print chunk details. */
   while( iff_pos < iff_file_sz ) {
      /* Extract chunk header. */
      chunk_sz =  iffy_endian_swap_32(
         *((uint32_t*)(&(iff_bytes[iff_pos + 4]))) );
      chunk_type[0] = iff_bytes[iff_pos];
      chunk_type[1] = iff_bytes[iff_pos + 1];
      chunk_type[2] = iff_bytes[iff_pos + 2];
      chunk_type[3] = iff_bytes[iff_pos + 3];

      printf( "chunk %d: %s: %u bytes long\n",
         chunk_idx, chunk_type, chunk_sz );

      /* Dump chunk. */
      snprintf( chunk_filename, FILENAME_SZ_MAX, "%s_%d_%s.bin",
         filename, chunk_idx, chunk_type );
      chunk_file = fopen( chunk_filename, "wb" );
      assert( NULL != chunk_file );
      fwrite( &(iff_bytes[iff_pos + 8]), 1, chunk_sz, chunk_file );
      fclose( chunk_file );

      /* Advance to next chunk. */
      iff_pos += 8 + chunk_sz;
      chunk_idx++;
   }

/* cleanup: */

   if( NULL != iff_file ) {
      fclose( iff_file );
   }

   if( NULL != iff_bytes ) {
      free( iff_bytes );
   }

   return retval;
}

