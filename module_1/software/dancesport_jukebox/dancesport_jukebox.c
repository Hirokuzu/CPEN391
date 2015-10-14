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

#define root (char*) ""
#define chacha (char*) "cha_cha/"
#define jive (char*) "jive/"
#define rumba (char*) "rumba/"
#define samba (char*) "samba/"
#define paso_doble (char*) "paso_doble/"
#define waltz (char*) "waltz/"
#define viennese_waltz (char*) "viennese_waltz/"
#define tango (char*) "tango/"
#define quickstep (char*) "quickstep/"
#define slow_foxtrot (char*) "slow_foxtrot/"

int main()
{
	// av_config_setup();
	alt_up_audio_dev* audio_out = alt_up_audio_open_dev("/dev/audio_0");
	alt_up_sd_card_dev* sd_card = alt_up_sd_card_open_dev("/dev/sdcard");

	if(sd_card != NULL)
	{
		// we can work on it?
		// get a bunch of the music
		//
		if(alt_up_sd_card_is_Present())
		{
			if(alt_up_sd_card_is_FAT16())
			{
				printf("FAT16\n");
				char * current_file;
				if(alt_up_sd_card_find_first("",current_file) == 0)
				{
					printf("File Found.\n");
					do
					{
						printf("%s\n", current_file);
					} while(alt_up_sd_card_find_next(current_file) == 0);
				}
			}
			else
			{
				printf("SD card not FAT16. Exiting...\n");
				return 3;
			}
		}
		else
		{
			printf("SD card not present. Exiting...\n");
			return 2;
		}
	}
	else
	{
		printf("SD Card NULL. Exiting...\n");
		return 1;
	}
	return 0;
}

void av_config_setup(const char * av_location)
{
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev(av_location);
	while(!alt_up_av_config_read_ready(av_config));
}
