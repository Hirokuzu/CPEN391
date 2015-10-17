/*
 * dancesport_jukebox.c
 *
 *  Created on: 2015-10-12
 *      Author: Arnold
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "altera_up_avalon_audio_and_video_config.h"
#include "altera_up_avalon_audio.h"
#include "Altera_UP_SD_Card_Avalon_Interface.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "dancesport_jukebox.h"
#include "music.h"
#include "system.h"

int main() {
	av_config_setup(AUDIO_AND_VIDEO_CONFIG_0_NAME);
	alt_up_audio_dev* audio_out = alt_up_audio_open_dev(AUDIO_0_NAME);
	alt_up_sd_card_dev* sd_card = alt_up_sd_card_open_dev(SDCARD_NAME);

	if (sd_card != NULL) {
		// we can work on it?
		// get a bunch of the music
		//
		if (alt_up_sd_card_is_Present()) {
			if (alt_up_sd_card_is_FAT16()) {
				printf("FAT16\n");
				int list_len;
				char ** playlist = get_genre_from_SD(root, &list_len);
				music song;
				song.filename = playlist[1];
				song.fd = alt_up_sd_card_fopen(song.filename, false);
				if(song.fd != -1)
				{
					int count = 0;
					while(count < 40)
					{
						alt_up_sd_card_read(song.fd);
						count++;
					}
					printf("reading data size\n");
					int i;
					size_t data_size = 0;
					for(i = 0; i < 4; i++)
					{
						data_size = data_size | alt_up_sd_card_read(song.fd) << (i*8);
					}
					printf("File size: %i bytes.\n", data_size);

					unsigned int left[data_size/4];
					unsigned int right[data_size/4];
					int j;

					printf("Reading file...\n");
					short int left_sample;
					for(i = 0; i < data_size/4 && (left_sample = alt_up_sd_card_read(song.fd))!=-1 ; i++)
					{
						left_sample = alt_up_sd_card_read(song.fd) << 8 | left_sample;
						left[i] = left_sample;
						short int right_sample = alt_up_sd_card_read(song.fd);
						right_sample = alt_up_sd_card_read(song.fd) << 8 | right_sample;
						right[i] = right_sample;
					}

					printf("Playing audio\n");
					alt_up_audio_enable_write_interrupt(audio_out);
					for(i = 0; i < data_size/4; i++)
					{
						while(!alt_up_audio_write_fifo_space(audio_out,ALT_UP_AUDIO_LEFT));
						alt_up_audio_write_fifo(audio_out, &left[i], 1, ALT_UP_AUDIO_LEFT);
						alt_up_audio_write_fifo(audio_out, &right[i], 1, ALT_UP_AUDIO_RIGHT);
					}
				}
				else
				{
					printf("I can't read :(\nError reading %s.\n", song.filename);
				}
			} else {
				printf("SD card not FAT16. Exiting...\n");
				return 3;
			}
		} else {
			printf("SD card not present. Exiting...\n");
			return 2;
		}
	} else {
		printf("SD Card NULL. Exiting...\n");
		return 1;
	}
	return 0;
}

void av_config_setup(const char * av_location) {
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev(av_location);
	while (!alt_up_av_config_read_ready(av_config));
}

void refill_write_fifo(void * context, alt_u32 id)
{
	int len = alt_up_audio_write_fifo_space(AUDIO_0_NAME, ALT_UP_AUDIO_LEFT);
	// write current track to fifo?

}
