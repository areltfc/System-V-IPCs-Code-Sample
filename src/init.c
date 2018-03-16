/*
** EPITECH PROJECT, 2018
** Sys V IPCs
** File description:
** Created by arthur,
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

#include "ipcs_defines.h"
#include "ipcs_funcs.h"

/*
 *	Setup a single railroad, based on the parameters in ipcs_tests.h
 */

char *init_track(char *track)
{
	unsigned int i = 0;

	while (i < BRIDGE_BEG) {
		track[i] = '=';
		++i;
	}
	track[i++] = '|';
	while (i < BRIDGE_END) {
		track[i] = '-';
		++i;
	}
	track[i++] = '|';
	while (i < TOTAL_SIZE) {
		track[i] = '=';
		++i;
	}
	return (track);
}

/*
 *	Create the shared memory, attach it, and fill it.
 *
 *	You might notice that a string is used instead of a string array
 *	when using an array is a perfect fit for what we need to achieve,
 *	and that the string is used as an array anyway.
 *	Simple answer, I do not think it is possible to store a C array in
 *	a signle shared memory. Creating a shared memory zone for each
 *	railroad would be preposterous, which is why we simple use one
 *	long string. As all strings share the same size, it is pretty easy
 *	to maneuver within our string, and we use a macro for convenience.
 */

char *init_tracks(int *shm_id, key_t key)
{
	char *tracks = NULL;
	unsigned int i = 0;
	unsigned int mem_size = MEM_SIZE;

	*shm_id = xshmget(key, mem_size, IPC_CREAT | IPC_EXCL | SHM_RW);
	if (*shm_id == -1)
		return (NULL);
	tracks = (char *) xshmat(*shm_id, NULL, 0);
	memset(tracks, 0, mem_size);
	for (; i < NB_TRAINS; ++i) {
		init_track(TRACKS(i));
	}
	return (tracks);
}