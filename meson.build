project('tll', 'c', 'java'
	, version: '0.0.0'
	, default_options : ['cpp_std=c++17', 'werror=true', 'optimization=2']
	, meson_version: '>= 0.62'
	)

jvm =  dependency('jni', version: '>= 1.8.0', modules: ['jvm'])
dl = meson.get_compiler('c').find_library('dl', required: false) # Not needed since glibc 2.34

jvmload = shared_library('jvmload',
		['src/jvmload.c'],
		dependencies : [jvm, dl],
		install : true
)

executable('example', ['src/example.c'], include_directories: include_directories('src'), link_with: jvmload, dependencies: jvm)
