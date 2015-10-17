/*
 * music.h
 *
 *  Created on: Oct 14, 2015
 *      Author: aip
 */

#ifndef MUSIC_H_
#define MUSIC_H_

typedef struct music
{
	char * filename;
	char * directory;
	int fd;
	size_t audio_len;
	size_t file_len;
} music;

// music * get_music_from_wav(char * directory, char * file_name);

char ** get_genre_from_SD(char * directory, int * list_len);

#endif /* MUSIC_H_ */
