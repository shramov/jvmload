// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 Pavel Shramov <shramov@mexmat.net>

#include "jvmload.h"

#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int jvmload_load(JVMApi * api, const char * java_home)
{
	if (!api)
		return EINVAL;
	if (!java_home)
		java_home = "";
	
	if (strcmp(java_home, "") == 0) {
		const char * env = getenv("JAVA_HOME");
		if (env)
			java_home = env;
	}

	if (strcmp(java_home, "") == 0)
		java_home = "/usr/lib/jvm/default-java";
	
	const char * suffix = "/lib/server/libjvm.so";
	char * buf = malloc(strlen(java_home) + strlen(suffix) + 1);
	strcpy(buf, java_home);
	strcat(buf, suffix);

	api->library = dlopen(buf, RTLD_NOW);
	free(buf);

	if (!api->library)
		return ENOENT;
	
	api->GetDefaultJavaVMInitArgs = dlsym(api->library, "JNI_GetDefaultJavaVMInitArgs");
	api->CreateJavaVM = dlsym(api->library, "JNI_CreateJavaVM");
	api->GetCreatedJavaVMs = dlsym(api->library, "JNI_GetCreatedJavaVMs");

	if (!api->GetDefaultJavaVMInitArgs || !api->CreateJavaVM || !api->GetCreatedJavaVMs)
		return ENOENT;
	
	return 0;
}

void jvmload_unload(JVMApi * api)
{
	if (!api || !api->library)
		return;
	dlclose(api->library);
}
