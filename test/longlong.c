
# include "testing.h"


static char buffer[128];

/**
 * Test print formatted long long integer
 */
TEST_CASE{

    struct fmt_stream out = {0};

    fmt_stream_buffer(&out, buffer, sizeof(buffer));

    /* ISO C90 does not support long long */
    (void)fmt_print(&out, "TEST %lld TEST", (long)123);

    TEST_EQUALS("TEST 123 TEST", buffer);
}
