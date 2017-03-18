
# include "testing.h"


static char buffer[128];

/**
 * Test print formatted size_t
 */
TEST_CASE{

    struct fmt_stream out = {0};

	fmt_stream_buffer(&out, buffer, sizeof(buffer));

	(void)fmt_print(&out, "TEST %zd TEST", (size_t)123);

	TEST_EQUALS("TEST 123 TEST", buffer);
}
