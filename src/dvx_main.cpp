/* -------------------------------------------

	Copyright (C) 2024 ELMH GROUP, all rights reserved.

------------------------------------------- */

#include <dvx_stream.h>

int main(void)
{
	auto url = "nil";

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

	return LIBDVX_SUCCESS;
}