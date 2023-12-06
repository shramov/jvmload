// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2023 Pavel Shramov <shramov@mexmat.net>

#include "jvmload.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	JVMApi api = {};

	if (jvmload_load(&api, argc > 1 ? argv[1] : NULL)) {
		printf("Failed to load libjvm.so\n");
		return 1;
	}

	JavaVMInitArgs args = {};
	args.version = JNI_VERSION_10;
	if (api.GetDefaultJavaVMInitArgs(&args) < 0) {
		printf("Failed to get default Java VM args\n");
		return 1;
	}


	JavaVMOption *options = NULL;
	if (argc > 2) {
		options = malloc(sizeof(JavaVMOption) * (argc - 2));
		int i = 0;
		for (i = 2; i < argc; i++)
			options[i - 2].optionString = argv[i];
		args.options = options;
		args.nOptions = argc - 2;
	}

	JNIEnv * env = NULL;
	JavaVM * jvm = NULL;
	if (api.CreateJavaVM(&jvm, (void **) &env, &args) < 0) {
		printf("Failed to create Java VM\n");
		return 1;
	}

	free(options);

	return 0;
}
