
# include "testing.h"


static char buffer[128];
static char tmp[128];

/**
 * Test print unknown formatter ID
 */
TEST_CASE{

    struct fmt_stream out = {0};
    int result = 0;

    fmt_stream_buffer(&out, buffer, sizeof(buffer));

    result = fmt_print(&out, "TEST %{Wrong} TEST", &out);

    (void)sprintf(tmp, "TEST Wrong@%p", (void *)&out);

    TEST_EQUALS(tmp, buffer);
    TEST_ASSERT(result == FMT_ERROR);
}
