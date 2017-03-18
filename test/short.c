
# include "testing.h"


static char buffer[128];

/**
 * Test print formatted short integer
 */
TEST_CASE{

    struct fmt_stream out = {0};

	fmt_stream_buffer(&out, buffer, sizeof(buffer));

	(void)fmt_print(&out, "TEST %hd TEST", (short)123);

	TEST_EQUALS("TEST 123 TEST", buffer);
}
