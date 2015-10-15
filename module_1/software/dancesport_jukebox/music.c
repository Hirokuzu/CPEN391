/*
 * music.c
 *
 *  Created on: Oct 15, 2015
 *      Author: aip
 */

#include <stdlib.h>
#include <stdio.h>
#include "Altera_UP_SD_Card_Avalon_Interface.h"
#define wav (char *) ".wav"
#define fat16_name_len 13
#define playlist_max 150

char ** get_genre_from_SD(char * directory, int * list_len)
{
	// open file, get data

	char * first_file = malloc(fat16_name_len); // 13 bytes for char
	//if(strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".csv"))
	char * adjust_directory = malloc(fat16_name_len);
	strcpy(adjust_directory, directory);
	strcat(adjust_directory, ".");
	if(alt_up_sd_card_find_first(adjust_directory, first_file) == 0) // directory actually exists, there's stuff here
	{
		printf("%s\n", first_file);
		char ** playlist = malloc(sizeof(first_file) * playlist_max); // dunno if the first file is garbage and rest is good
		playlist[0] = directory;
		printf("Directory: %s\n", playlist[0]);
		int count = 1;
		playlist[count] = malloc(fat16_name_len);
		strcpy(playlist[count],first_file);

		do
		{
			printf("Playlist[%d]: %s\n", count, playlist[count]);
			int namelen = strlen(playlist[count]);
//			printf("namelen: %i\n", namelen);
			printf("%s\n", *(playlist+count) + namelen - 4);
			if(namelen > 4 && !strcmp(*(playlist+count) + namelen - 4, ".wav")) // actually a wav file
			{
				count++; // we can move on
			}
		}while(alt_up_sd_card_find_next(playlist[count]) == 0);
		printf("%d\n", count);
		int i = 0;
		for(i = 0; i < count; i++)
		{
			printf("%s\n", playlist[count]);
		}
		if(count > 1)
		{
			* list_len = count;
			return playlist;
		}
		else; // there were no useful files, just return a null pointer?
	}
	// close file, return struct
	return NULL; // failed.
}
