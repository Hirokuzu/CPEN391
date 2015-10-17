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

	char * adjust_directory = malloc(fat16_name_len);
	// all defined directories have names shorter than 13 characters because I don't have time to find out if FAT16 supports that

	strcpy(adjust_directory, directory);
	strcat(adjust_directory, "."); // input "directory" doesn't have the . at the end needed for the "first" function
	if(alt_up_sd_card_find_first(adjust_directory, first_file) == 0) // directory actually exists, there's stuff here
	{
		char ** playlist = malloc(sizeof(first_file) * playlist_max);
		playlist[0] = directory;
		int count = 1;
		playlist[count] = malloc(fat16_name_len);
		strcpy(playlist[count],first_file);  // dunno if the first file is garbage and rest is good. just assign
		do
		{
			int namelen = strlen(playlist[count]);
//			printf("namelen: %i\n", namelen);
			if(namelen > 4 && !strcasecmp((*(playlist+count)) + namelen - 4, ".wav")) // actually a wav file
			{
				count++; // we can move on
			}
			else; // don't increment. next file read will overwrite. overhead?
		}while(alt_up_sd_card_find_next(*(playlist+count)) == 0);
		if(count > 1) // there was at least one wav file in here.
		{
			*list_len = count;
			return playlist;
		}
		else; // there were no useful files, just return a null pointer?
	}
	// close file, return struct
	return NULL; // failed.
}
