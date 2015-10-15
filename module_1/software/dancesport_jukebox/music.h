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
	int fd;
	size_t audio_len;
	size_t file_len;
} music;


#endif /* MUSIC_H_ */
