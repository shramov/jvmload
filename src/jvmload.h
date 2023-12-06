// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 Pavel Shramov <shramov@mexmat.net>

#ifndef _JVMLOAD_H
#define _JVMLOAD_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	/// Library pointer, if user wants to unload later
	void * library;
	jint (*GetDefaultJavaVMInitArgs)(void *args);
	jint (*CreateJavaVM)(JavaVM **pvm, void **penv, void *args);
	jint (*GetCreatedJavaVMs)(JavaVM **, jsize, jsize *);
} JVMApi;

/// Translate java home to libjvm.so path
char * jvmload_library_path(const char * java_home);
/// Fill API structure from library handle
int jvmload_fill(JVMApi * api, void * handle);

int jvmload_load(JVMApi * api, const char * java_home);
void jvmload_unload(JVMApi * api);

#ifdef __cplusplus
} // extern "C"
#endif

#endif//_JVMLOAD_H
