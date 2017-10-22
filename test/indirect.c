
# include "testing.h"


static char buffer[128];

int format_indirect(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

/**
 * Test print indirect formatter
 */
TEST_CASE{

    struct fmt_stream out = {0};

	fmt_stream_buffer(&out, buffer, sizeof(buffer));

	(void)fmt_print(&out, "TEST %{@INDIRECT:OPTIONS} TEST", format_indirect, 123);

	TEST_EQUALS("TEST (INDIRECT/123/OPTIONS) TEST", buffer);
}

int format_indirect(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

	int number = va_arg(*arg, int);

	return( fmt_print_builtin(out, "(%s/%d/%s)", id, number, options) );
}
