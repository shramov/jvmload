project('tll', 'c', 'java'
	, version: '0.0.0'
	, default_options : ['cpp_std=c++17', 'werror=true', 'optimization=2']
	, meson_version: '>= 0.62'
	)

jvm =  dependency('jni')
dl = meson.get_compiler('c').find_library('dl', required: false) # Not needed since glibc 2.34

jvmload = static_library('jvmload',
		['src/jvmload.c'],
		dependencies : [jvm, dl],
		install : true
)

jvmload_dep = declare_dependency(include_directories: include_directories('src'), link_with: jvmload)

executable('example', ['src/example.c'], dependencies: [jvm, jvmload_dep])
