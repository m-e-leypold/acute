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

SUBDIRS       = src tests doc
dist_doc_DATA = README

ACLOCAL_AMFLAGS = -I m4 --install
EXTRA_DIST      = m4/NOTES build-aux/bootstrap build-aux/devclean

stage:
	$(MAKE) install DESTDIR=$(CURDIR)/STAGE

devclean:
	$(MAKE) distclean && build-aux/devclean

devcheck: clean
	test $$(git status -s | grep '^[ ?]?' | wc -l) -eq 0
	git clean -fxd
	./build-aux/bootstrap
	make check
	./build-aux/reconfigure-pedantic
	make check



