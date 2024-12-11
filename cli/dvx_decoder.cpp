/* -------------------------------------------

	Copyright (C) 2024 Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>
#include <stdexcept>
#include <cstdio>
#include <cstring>

int main(int argc, char** argv)
{
    const char* url = nullptr;

	for (size_t i = 1UL; i < (argc); ++i)
	{
		if (strcmp(argv[i], "--codec") == 0)
		{
			std::printf("Name: DVX Open Theather Quality.\nVersion: 1.0.0\n");
		}
		else
		{
			url = argv[i];
			break;
		}

		return LIBDVX_SUCCESS;
	}

	if (!url)
	{
	    return LIBDVX_FAILURE;
	}

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
