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

info_TEXINFOS   = acute.texi
acute_TEXINFOS  = fdl.texi sample-test-1.c


clean-local:
	rm -f *.pdf

sample-test-1.c: ../example-project/tests/sample-test-1.c
	awk 's{print}/ *[*][/]/{s=1}' <../example-project/tests/sample-test-1.c >sample-test-1.c
