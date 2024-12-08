/* -------------------------------------------

	Copyright (C) 2024 ELMH GROUP, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>
#include <stdexcept>

int main(void)
{
	auto url = "nil";

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
