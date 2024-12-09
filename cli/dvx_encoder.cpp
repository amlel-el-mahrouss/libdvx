/* -------------------------------------------

	Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

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

	std::printf("DVX Encoder: Encoding File: %s\n", argv[1]);
	std::fstream blob(argv[1], std::ios::binary);

	std::stringstream ss_blob;
	ss_blob << blob.rdbuf();

	std::string ss_blob_out;
	ss_blob_out.resize(ss_blob.str().size());

	DVXStreamInterface* interface_codec = dvx_open_stream(argv[1]);

	interface_codec->Encode(ss_blob_out.size(), ss_blob.str().size(), ss_blob.str().data(), ss_blob_out.data());

	dvx_close_stream(interface_codec);

	return EXIT_SUCCESS;
}
