// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 Pavel Shramov <shramov@mexmat.net>

#include "jvmload.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	JVMApi api = {};

	if (jvmload_load(&api, argc > 1 ? argv[1] : NULL)) {
		printf("Failed to load libjvm.so\n");
		return 1;
	}

	JavaVMInitArgs args = {};
	api.GetDefaultJavaVMInitArgs(&args);
	args.version = JNI_VERSION_10;
	
	JNIEnv * env = NULL;
	JavaVM * jvm = NULL;
	api.CreateJavaVM(&jvm, (void **) &env, &args);

	return 0;
}
