
# include "testing.h"


/**
 * Test print formatted string to a file
 */
TEST_CASE{

    int written = 0;
    struct fmt_stream out = {0};

    fmt_stream_file(&out, fopen("TEST.TMP", "w"));

    written = fmt_print(&out, "TEST %-6s TEST", "TEST");

    TEST_ASSERT(written == 16);
}
