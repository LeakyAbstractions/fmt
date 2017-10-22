
# include "testing.h"


static char buffer[128];

/**
 * Test print formatted string
 */
TEST_CASE{

    struct fmt_stream out = {0};

    fmt_stream_buffer(&out, buffer, sizeof(buffer));

    (void)fmt_print(&out, "TEST %s TEST", "STRING");

    TEST_EQUALS("TEST STRING TEST", buffer);
}
