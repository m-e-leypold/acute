# Acute - A C Unit Testing Environment, Example Project
# Copyright (C) 2019 M E Leypold
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

LOG_DRIVER         = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/build-aux/tap-driver.sh
TEST_LOG_DRIVER    = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/build-aux/tap-driver.sh

AM_CPPFLAGS         = -I$(srcdir)/../include
TESTS               = an-example-test sample-test-1
EXTRA_DIST          = an-example-test

# Don't add binaries to EXTRA_DIST.
# see also: https://www.gnu.org/software/automake/manual/html_node/Scripts.html

check_PROGRAMS         = sample-test-1
sample_test_1_SOURCES  = sample-test-1.c

# single1_SOURCES = single1.c
# suite1_SOURCES  = suite1.c



