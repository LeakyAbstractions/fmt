
# include "testing.h"


static char buffer[128];

/**
 * Test print formatted double
 */
TEST_CASE{

    struct fmt_stream out = {0};

    fmt_stream_buffer(&out, buffer, sizeof(buffer));

    (void)fmt_print(&out, "TEST %.2f TEST", 1.23f);

    TEST_EQUALS("TEST 1.23 TEST", buffer);
}
