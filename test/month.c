
# include "testing.h"


static char buffer[128];
const char * month_name[] = { "ERROR", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

int format_month(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

/**
 * Test print custom formatted integer
 */
TEST_CASE{

    struct fmt_stream out = {0};

    fmt_stream_buffer(&out, buffer, sizeof(buffer));

    TEST_ASSERT(fmt_register_formatter(format_month, "Month") == 1);

    (void)fmt_print(&out, "TEST %{Month} TEST", 7);

    TEST_EQUALS("TEST July TEST", buffer);
}

int format_month(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

    int month = va_arg(*arg, int);

    (void)id;
    (void)options;

    return( fmt_print_builtin(out, "%s", month_name[month < 0 || month > 12 ? 0 : month]) );
}
