/*
 * music.h
 *
 *  Created on: Oct 14, 2015
 *      Author: aip
 */

#ifndef MUSIC_H_
#define MUSIC_H_

typedef struct music
/* the idea was also to store the data here for fast access, but in reality
 * it's easier to just open the file every time, i think. accessing an array
 * of this stuff would require a map of some sort
 */
{
	char * filename;
	char * directory;
	int fd;
	size_t audio_len;
	size_t file_len;
} music;

// music * get_music_from_wav(char * directory, char * file_name);

/**
 * Given a valid directory containing (a) file(s) with ".wav" (extension), returns a list of ".wav" (extension) files
 * (a file named ".wav" is not considered one with a ".wav" extension - that's its name.
 * Otherwise, returns NULL
 * param
 * 		directory - a string for the directory they want to search
 *		list_len - a pointer to return the number of tracks in the list
 *
 * returns
 * 		an array of strings. the first string is always the directory.
 */
char ** get_genre_from_SD(char * directory, int * list_len);


#endif /* MUSIC_H_ */
