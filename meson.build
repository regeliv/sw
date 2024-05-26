project('spacewar', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++23'])

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

sfml_proj = subproject('sfml')
sfml_dep = sfml_proj.get_variable('sfml_dep')

# test_src = files('test/test.cpp')
app_src = files('src/main.cpp')
lib_src = files('src/lib/window.cpp', 'src/lib/game.cpp')

exe = executable('spacewar', app_src + lib_src,
  install : true,
  dependencies : [
    sfml_dep
  ],
  cpp_args: ['-std=c++23'],
)

# ge = executable(
#   'gtest-all',
#   test_src + lib_src,
#   dependencies : [
#     gtest_dep,
#     gmock_dep,
#   ],
#   cpp_args: ['-std=c++23'],
# )

# test('gtest', ge)
