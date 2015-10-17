/*
 * dancesport_jukebox.h
 *
 *  Created on: 2015-10-12
 *      Author: Arnold
 */

#ifndef DANCESPORT_JUKEBOX_H_
#define DANCESPORT_JUKEBOX_H_

#define root (char*) ""
#define chacha (char*) "chacha/"
#define jive (char*) "jive/"
#define rumba (char*) "rumba/"
#define samba (char*) "samba/"
#define paso_doble (char*) "paso/"
#define waltz (char*) "waltz/"
#define viennese_waltz (char*) "viennese/"
#define tango (char*) "tango/"
#define quickstep (char*) "quickstep/"
#define slow_foxtrot (char*) "slowfox/"

int main();

void av_config_setup(const char * av_location);

int populate_playlist();

void refill_write_fifo(void * context, alt_u32 id);

#endif /* DANCESPORT_JUKEBOX_H_ */
