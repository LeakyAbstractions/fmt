
# include "testing.h"


static char buffer[128];

void format_meta(struct fmt_stream * out, const char * format, ...);

/**
 * Test print meta formatter
 */
TEST_CASE{

    struct fmt_stream out = {0};

	fmt_stream_buffer(&out, buffer, sizeof(buffer));

	format_meta(&out, "(%s/%d)", "META", 123);

	TEST_EQUALS("TEST (META/123) TEST", buffer);
}

void format_meta(struct fmt_stream * out, const char * format, ...){
	va_list arg;
	va_start(arg, format);
	fmt_print(out, "TEST %{*} TEST", format, &arg);
	va_end(arg);
}
