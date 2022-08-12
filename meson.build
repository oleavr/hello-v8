project('hello-v8', 'cpp',
  default_options: [
    'cpp_std=c++17',
    'optimization=s',
    'b_ndebug=true',
    'strip=true',
  ],
)

v8_dep = dependency('v8-10.0')

executable('hello-v8', 'hello.cc',
  dependencies: [v8_dep],
)
