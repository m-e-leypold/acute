# Acute - A C Unit Testing Environment
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

EXTRA_DIST         = macro-machinery-vec.h.t4
pkginclude_HEADERS = commands.h			\
		     control.h			\
		     expectations.h		\
		     framework.h		\
		     gargs.h			\
		     macro-machinery-vec.h	\
		     macro-machinery.h		\
		     registry.h			\
		     runtime.h			\
		     tap.h			\
		     testsuite.h		\
		     typehandlers.h

macro-machinery-vec.h: macro-machinery-vec.h.t4
	autom4te -o macro-machinery-vec.h -l M4sugar macro-machinery-vec.h.t4 

clean-local:
	rm -f macro-machinery-vec.h
