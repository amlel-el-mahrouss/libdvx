/* -------------------------------------------

	Copyright (C) 2024 EL Mahrouss Amlal, all rights reserved.

------------------------------------------- */

#include <cstdlib>
#include <dvx_stream.h>

static const char* kDVXURL = nullptr;

/// @brief Opens a stream player (from HTTP or Local Video)
EM_JS(const char*, dvx_stream_open_player, (), {
    return prompt('Please give a DVX media URL:', 'dvx://el-mahrouss-logic.com/welcome');
});

EM_JS(void, dvx_stream_error, (const char* msg), {
    alert(msg);
});


int main(void)
{
    kDVXURL = dvx_stream_open_player();
    
    DVXStreamInterface* dvx_stream = dvx_open_stream(kDVXURL);

    if (!dvx_stream)
    {
        dvx_stream_error("The DVX player couldn't be initialized, we are sorry for that");
        return EXIT_FAILURE;
    }
    else
    {
        // dvx_play_stream(dvx_stream);
        dvx_close_stream(dvx_stream);
    }
    
    return EXIT_SUCCESS;
}