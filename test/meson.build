gtest_dep = dependency('gtest', main : true, required : false)
bibs_test_sources = ['bibs.cpp']
e = executable(
  'bibs-test',
  bibs_test_sources,
  dependencies : gtest_dep,
  include_directories : inc,
  link_with : bibs
)
test('gtest test', e)
