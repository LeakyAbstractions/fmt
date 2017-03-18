
# include "testing.h"


static char buffer[128];

/**
 * Test print formatted long double
 */
TEST_CASE{

    struct fmt_stream out = {0};

	fmt_stream_buffer(&out, buffer, sizeof(buffer));

	(void)fmt_print(&out, "TEST %.2Lf TEST", (long double).0);

	TEST_EQUALS("TEST 0.00 TEST", buffer);
}
