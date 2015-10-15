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

int main() {
	av_config_setup("/dev/audio_and_video_config_0");
	alt_up_audio_dev* audio_out = alt_up_audio_open_dev("/dev/audio_0");
	alt_up_sd_card_dev* sd_card = alt_up_sd_card_open_dev("/dev/sdcard");

	if (sd_card != NULL) {
		// we can work on it?
		// get a bunch of the music
		//
		if (alt_up_sd_card_is_Present()) {
			if (alt_up_sd_card_is_FAT16()) {
				printf("FAT16\n");
				int * list_len;
				char ** playlist = get_genre_from_SD(root, list_len);
				int i = 0;
				for(;i < *list_len; i++)
				{
					printf("%i\n", *list_len);
					printf("%s\n", playlist[i]);
				}
//				printf("FAT16\n");
//				char * current_file = malloc(sizeof(char) * 13);
//				if (alt_up_sd_card_find_first(root, current_file) == 0) {
//					printf("File Found.\n");
//					do {
//						printf("%s\n", current_file);
//						if(strcasestr(current_file, ".wav"))
//						{
//							printf("hey!\n");
//							music song;
//							song.filename = current_file;
//							song.fd = alt_up_sd_card_fopen(current_file, false);
//							// read the file
//							if(song.fd != -1)
//							{
//								int count = 0;
//								while(count < 40)
//								{
//									alt_up_sd_card_read(song.fd);
//									count++;
//								}
//								printf("reading data size\n");
//								int i;
//								size_t data_size = 0;
//								for(i = 0; i < 4; i++)
//								{
//									data_size = data_size | alt_up_sd_card_read(song.fd) << (i*8);
//								}
//								printf("File size: %i bytes.\n", data_size);
//
//								unsigned int left[data_size/4];
//								unsigned int right[data_size/4];
//								int j;
//
//								printf("Reading file...\n");
//								for(i = 0; i < data_size/4; i++)
//								{
//									short int left_sample = alt_up_sd_card_read(song.fd);
//									left_sample = alt_up_sd_card_read(song.fd) << 8 | left_sample;
//									left[i] = left_sample;
//									short int right_sample = alt_up_sd_card_read(song.fd);
//									right_sample = alt_up_sd_card_read(song.fd) << 8 | right_sample;
//									right[i] = right_sample;
//								}
//
//								printf("Playing audio\n");
//								for(i = 0; i < data_size/4; i++)
//								{
//									while(!alt_up_audio_write_fifo_space(audio_out,ALT_UP_AUDIO_LEFT));
//									alt_up_audio_write_fifo(audio_out, &left[i], 1, ALT_UP_AUDIO_LEFT);
//									alt_up_audio_write_fifo(audio_out, &right[i], 1, ALT_UP_AUDIO_RIGHT);
//								}
//							}
//							else
//							{
//								printf("I can't read :(\nError reading %s.\n", song.filename);
//							}
//						}
//					} while (alt_up_sd_card_find_next(current_file) == 0);
//				}
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
