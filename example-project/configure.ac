dnl  Acute - A C Unit Testing Environment, Example Project
dnl  Copyright (C) 2019 M E Leypold
dnl  
dnl  This program is free software: you can redistribute it and/or modify
dnl  it under the terms of the GNU General Public License as published by
dnl  the Free Software Foundation, either version 3 of the License, or
dnl  (at your option) any later version.
dnl  
dnl  This program is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl  GNU General Public License for more details.
dnl  
dnl  You should have received a copy of the GNU General Public License
dnl  along with this program.  If not, see <https://www.gnu.org/licenses/>.

AC_INIT([acute-example-project], [0.0.4], [acute-bugs-wh2e212@m-e-leypold.de])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 tests/Makefile
])
AC_REQUIRE_AUX_FILE([tap-driver.sh])
AC_OUTPUT
