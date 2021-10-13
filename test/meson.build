#    BIBS, the belief-induced behaviour simulation
#    Copyright (C) 2021 Robert Greener
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

gtest_dep = dependency('gtest', main : true, required : false)
bibs_test_sources = [
  'agent.cpp',
  'bibs.cpp',
  'behaviour.cpp',
  'belief.cpp']
e = executable(
  'bibs-test',
  bibs_test_sources,
  dependencies : gtest_dep,
  include_directories : inc,
  link_with : bibs
)
test('gtest test', e)
