/* -------------------------------------------

	Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>
#include <stdexcept>

int main(int argc, char** argv)
{
	auto url = "dsp://endpoint/nil";

	// Get media URL.
	if (argc > 2)
		url = argv[1];

	try
	{
		DVXStreamInterface* dvx_stream = dvx_open_stream(url);

		if (!dvx_stream)
		{
			std::printf("The DVX player couldn't be initialized, we are sorry for that");
			return LIBDVX_FAILURE;
		}
		else
		{
			dvx_play_stream(dvx_stream);
			dvx_close_stream(dvx_stream);
		}
	}
	catch (std::runtime_error& err)
	{
		std::printf("%s", err.what());
	}

	return LIBDVX_SUCCESS;
}
