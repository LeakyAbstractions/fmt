#
# fmt
#
# Copyright (c) 2017 Guillermo Calvo
# Licensed under the GNU Lesser General Public License
#

AUTOMAKE_OPTIONS = foreign subdir-objects

AM_CFLAGS = -Wall -Werror --pedantic -coverage -O0 -I$(FMT_PATH)


# Library

FMT_PATH            = src
FMT_LIBRARY         = lib/libfmt.a


# Install

lib_LIBRARIES =                         \
    $(FMT_LIBRARY)

include_HEADERS =                       \
    src/fmt.h


# Cleanup

CLEANFILES =                            \
    *.log


# fmt library

lib_libfmt_a_CFLAGS                     = -Wall -Werror --pedantic
lib_libfmt_a_SOURCES                    = src/fmt.c
