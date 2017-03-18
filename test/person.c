
# include "testing.h"


static char buffer[128];
struct person{

	const char * name;
	const char * surname;
	int age;
};

int format_person(struct fmt_stream * out, const char * id, const char * options, va_list * arg);
int format_age(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

/**
 * Test print formatted custom structure with options
 */
TEST_CASE{

    struct fmt_stream out = {0};

	struct person p = {"John", "Doe", 32};

	TEST_ASSERT(fmt_register_formatter(format_person, "Person") == 1);
	TEST_ASSERT(fmt_register_formatter(format_age, "Age") == 1);

	fmt_stream_buffer(&out, buffer, sizeof(buffer));
	(void)fmt_print(&out, "%{Person}", NULL);

	TEST_EQUALS("NULL PERSON", buffer);

	fmt_stream_buffer(&out, buffer, sizeof(buffer));
	(void)fmt_print(&out, "%{Person:XXX}", &p);

	TEST_EQUALS("WRONG FORMAT (XXX)", buffer);

	fmt_stream_buffer(&out, buffer, sizeof(buffer));
	(void)fmt_print(&out, "%{Person}", &p);

	TEST_EQUALS("Doe, John (32 years)", buffer);

	fmt_stream_buffer(&out, buffer, sizeof(buffer));
	(void)fmt_print(&out, "Mr. %{Person:surname} is %{Age} old.", &p, p.age);

	TEST_EQUALS("Mr. Doe is 32 years old.", buffer);
}

int format_person(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

	struct person * p = va_arg(*arg, void *);

	(void)id;

	if(p == NULL){

		return( fmt_print_builtin(out, "NULL PERSON") );
	}

	if(options == NULL){

		return( fmt_print(out, "%s, %s (%{Age})", p->surname, p->name, p->age) );
	}

	if(strcmp(options, "name") == 0){

		return( fmt_print_builtin(out, "%s", p->name) );
	}

	if(strcmp(options, "surname") == 0){

		return( fmt_print_builtin(out, "%s", p->surname) );
	}

	if(strcmp(options, "age") == 0){

		return( fmt_print(out, "%{Age}", p->age) );
	}

	return( fmt_print_builtin(out, "WRONG FORMAT (%s)", options) );
}

int format_age(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

	int age = va_arg(*arg, int);

	(void)id;
	(void)options;

	return( fmt_print_builtin(out, "%d years", age) );
}
