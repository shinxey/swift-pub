#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SP_IMPLEMENTATION
#include "../swift_pub.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: interface_test path/to/file.swift");
		return 1;
	}

	char* filename = argv[1];

	SpInputBuf *buf = sp_input_buf_create();

	if (!buf) {
		printf("out of memory\n");
		return 1;
	}

	int res = sp_input_buf_open(buf, filename);

	if (res != 0) {
		printf("encountered error while opening file\n");
		sp_input_buf_destroy(buf);
		return 1;
	}

	SpInterfaceOutput output = {0};

	res = sp_interface_calculate_public(buf, &output);

	if (res != 0) {
		printf("error while calculating interface!");
		sp_input_buf_close(buf);
		sp_input_buf_destroy(buf);
		return 1;
	}

	printf("%s\n", output.buf);

	sp_input_buf_close(buf);
	sp_input_buf_destroy(buf);

	return 0;
}
