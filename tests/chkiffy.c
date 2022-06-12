
#include <check.h>
#include "../src/iffy.h"

#include <stdio.h>

START_TEST( test_example ) {
}
END_TEST

static void setup_example() {
}

static void teardown_example() {
}

Suite* iffy_suite( void ) {
   Suite* s = NULL;
   TCase* tc_example = NULL;

   s = suite_create( "iffy" );

   tc_example = tcase_create( "example" );

   tcase_add_checked_fixture(
      tc_example, setup_example, teardown_example );

   tcase_add_loop_test( tc_example, test_example, 2, 3 );
   tcase_add_test( tc_example, test_example );

   suite_add_tcase( s, tc_example );

   return s;
}

