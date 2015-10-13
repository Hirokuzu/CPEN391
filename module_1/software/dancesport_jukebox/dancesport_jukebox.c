/*
 * dancesport_jukebox.c
 *
 *  Created on: 2015-10-12
 *      Author: Arnold
 */

#include <stdio.h>
#include <stdlib.h>
#include "altera_up_avalon_audio_and_video_config.h"
#include "altera_up_avalon_audio.h"
#include "Altera_UP_SD_Card_Avalon_Interface.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "dancesport_jukebox.h"

int main()
{
	av_config_setup();
	at_up_audio_dev* audio_out = alt_up_audio_open_dev("/dev/audio_0");
	alt_up_sd_card_dev* sd_card = alt_up_sd_card_open_dev("/dev/sdcard");

	if(sd_card != NULL)
	{
		// we can work on it?
		// get a bunch of the music
		//
		if(alt_up_sd_card_is_FAT16())
		{

		}
	}
	return 0;
}

void av_config_setup(const char * av_location)
{
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev(av_location);
	while(!alt_up_av_config_read_ready(av_config));
}
