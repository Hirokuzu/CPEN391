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
	// TODO: register interrupts for push switch and switches

	// TODO: setup the state machine here.
	if (sd_card != NULL) {
		// there's some sort of connection with the SD card port
		if (alt_up_sd_card_is_Present()) {
			// there's a card!
			if (alt_up_sd_card_is_FAT16()) {
				/* it's FAT16. In reality, this also checks if the SD card is
				 * present. It would be possible to just use this initially
				 * and then in the else condition check if the SD card is
				 * present, but this is what I had when I presented. GG.
				 */
				printf("FAT16\n");
				int list_len;
				char ** playlist = get_genre_from_SD(root, &list_len);//dbl ptr all the way acrs the sky~
				// TODO: make an array of playlists, and an array of lengths

				/* could instead do a for loop here, iterate through list_len
				 * and end up playing songs in sequence.
				 */
				// the music structure was useless. list of strings instead
				music song;
				song.filename = playlist[1]; // playlist[0] is the directory string
				song.fd = alt_up_sd_card_fopen(song.filename, false);
				if(song.fd != -1) // yay it didn't fail -> values less than -1?
				{
					int count = 0;
					while(count < 40)
					/* First 40 bytes are header info. One useful piece of info
					 * would be the size of file as a whole, but there's one section
					 * that already lists the size of the contained data.
					 *
					 * There's also info on number of channels.
					 *
					 * more info http://www.topherlee.com/software/pcm-tut-wavformat.html
					 *
					 */
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
						// I have managed to get ridiculously large numbers (543MB+) before
					}
					printf("File size: %i bytes.\n", data_size);

					// data size is in bytes, each channel samples two bytes at a time
					// there are two channels
					// should always be a multiple of 4
					unsigned int left[data_size/4];
					unsigned int right[data_size/4];

					printf("Reading file...\n");
					/* TODO: make faster version of alt_up_sd_card_read(int file_handle)
					 * Currently reads one byte at a time. Can make a alt_up_sd_card_read_sample(int file_handle)?
					 * Then I can reassemble in that function and less checks (unecessary overhead == bad)
					 */
					short int left_sample;
					// populate array with samples
					for(i = 0; i < data_size/4 && (left_sample = alt_up_sd_card_read(song.fd))!=-1 ; i++)
					{
						left_sample = alt_up_sd_card_read(song.fd) << 8 | left_sample;
						left[i] = left_sample;
						short int right_sample = alt_up_sd_card_read(song.fd);
						right_sample = alt_up_sd_card_read(song.fd) << 8 | right_sample;
						right[i] = right_sample;
					}

					// TODO: at this point, there should be something here to process the audio based on the requested playback speed

					printf("Playing audio\n");
					alt_up_audio_enable_write_interrupt(audio_out);
					// could add 96 samples at once
					for(i = 0; i < data_size/4; i++)
					{
						while(!alt_up_audio_write_fifo_space(audio_out,ALT_UP_AUDIO_LEFT));
						alt_up_audio_write_fifo(audio_out, &left[i], 1, ALT_UP_AUDIO_LEFT);
						alt_up_audio_write_fifo(audio_out, &right[i], 1, ALT_UP_AUDIO_RIGHT);
					}
//					for(i = 0; i < data_size/4; i = i + 96) //somewhat similar to what interrupt would do, but we're still waiting
//					{
//						while(alt_up_audio_write_fifo_space(audio_out,ALT_UP_AUDIO_LEFT) < 96);
//						if((data_size/4 - i) < 96) {
//							alt_up_audio_write_fifo(audio_out, &left[i], data_size/4 - i), ALT_UP_AUDIO_LEFT);
//							alt_up_audio_write_fifo(audio_out, &right[i], data_size/4 - i), ALT_UP_AUDIO_RIGHT);
//						}
//						alt_up_audio_write_fifo(audio_out, &left[i], data_size/4 - i), ALT_UP_AUDIO_LEFT);
//						alt_up_audio_write_fifo(audio_out, &right[i], data_size/4 - i), ALT_UP_AUDIO_RIGHT);
//					}
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
	// TODO: set global pointer we have to malloc so we can fill the buffer without taking in anything?
	// 	    - security issue?
}
