#
# fmt
#
# Copyright (c) 2017 Guillermo Calvo
# Licensed under the GNU Lesser General Public License
#

AUTOMAKE_OPTIONS = foreign subdir-objects

AM_CFLAGS = -Wall -Wextra -Werror --pedantic -Wno-missing-field-initializers -coverage -O0 -I$(FMT_PATH)


# Library

FMT_PATH            = src
FMT_LIBRARY         = lib/libfmt.a


# Install

lib_LIBRARIES =                         \
    $(FMT_LIBRARY)

include_HEADERS =                       \
    src/fmt.h


# Documentation

docdir = $(datadir)/doc/fmt
doc_DATA = doc/*


# Cleanup

CLEANFILES =                            \
    *.log                               \
    *.gcda                              \
    *.gcno                              \
    *.gcov                              \
    src/*.gcda                          \
    src/*.gcno                          \
    src/*.gcov                          \
    test/*.gcda                         \
    test/*.gcno                         \
    test/*.gcov


# Check

check_PROGRAMS =                        \
	bin/check/double                    \
	bin/check/file                      \
	bin/check/flags                     \
	bin/check/integer                   \
	bin/check/intmax                    \
	bin/check/ldouble                   \
	bin/check/long                      \
	bin/check/longlong                  \
	bin/check/meta                      \
	bin/check/month                     \
	bin/check/percent                   \
	bin/check/person                    \
	bin/check/ptrdiff                   \
	bin/check/precision                 \
	bin/check/short                     \
	bin/check/size                      \
	bin/check/string                    \
	bin/check/wrongid

TESTS =                                 \
	bin/check/double                    \
	bin/check/file                      \
	bin/check/flags                     \
	bin/check/integer                   \
	bin/check/intmax                    \
	bin/check/ldouble                   \
	bin/check/long                      \
	bin/check/longlong                  \
	bin/check/meta                      \
	bin/check/month                     \
	bin/check/percent                   \
	bin/check/person                    \
	bin/check/ptrdiff                   \
	bin/check/precision                 \
	bin/check/short                     \
	bin/check/size                      \
	bin/check/string                    \
	bin/check/wrongid


tests: check


# fmt library

lib_libfmt_a_CFLAGS                     = -Wall -Wextra -Werror --pedantic
lib_libfmt_a_SOURCES                    = src/fmt.c


# fmt tests

bin_check_double_SOURCES                = src/fmt.c test/double.c
bin_check_file_SOURCES                  = src/fmt.c test/file.c
bin_check_flags_SOURCES                 = src/fmt.c test/flags.c
bin_check_integer_SOURCES               = src/fmt.c test/integer.c
bin_check_intmax_SOURCES                = src/fmt.c test/intmax.c
bin_check_ldouble_SOURCES               = src/fmt.c test/ldouble.c
bin_check_long_SOURCES                  = src/fmt.c test/long.c
bin_check_longlong_SOURCES              = src/fmt.c test/longlong.c
bin_check_meta_SOURCES                  = src/fmt.c test/meta.c
bin_check_month_SOURCES                 = src/fmt.c test/month.c
bin_check_percent_SOURCES               = src/fmt.c test/percent.c
bin_check_person_SOURCES                = src/fmt.c test/person.c
bin_check_ptrdiff_SOURCES               = src/fmt.c test/ptrdiff.c
bin_check_precision_SOURCES             = src/fmt.c test/precision.c
bin_check_short_SOURCES                 = src/fmt.c test/short.c
bin_check_size_SOURCES                  = src/fmt.c test/size.c
bin_check_string_SOURCES                = src/fmt.c test/string.c
bin_check_wrongid_SOURCES               = src/fmt.c test/wrongid.c


# coverage

coverage: check fmt.c.gcov

fmt.c.gcov:
	gcov src/fmt.c --object-directory src/*
