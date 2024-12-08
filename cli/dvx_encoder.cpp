/* -------------------------------------------

	Copyright (C) 2024 ELMH GROUP, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>
#include <stdexcept>
#include <fstream>
#include <sstream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		return EXIT_FAILURE;
	}

	std::printf("DVX Encoder: Encoding: %s\n", argv[1]);
	std::fstream blob(argv[1], std::ios::binary);

	std::stringstream ss_blob;
	ss_blob << blob.rdbuf();

	DVXStreamInterface* interface_codec = dvx_open_stream(argv[1]);



	return EXIT_SUCCESS;
}
