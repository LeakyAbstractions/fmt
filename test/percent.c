
# include "testing.h"


static char buffer[128];

/**
 * Test print percent character
 */
TEST_CASE{

    struct fmt_stream out = {0};

    fmt_stream_buffer(&out, buffer, sizeof(buffer));

    (void)fmt_print(&out, "TEST %% TEST", 123);

    TEST_EQUALS("TEST % TEST", buffer);
}
