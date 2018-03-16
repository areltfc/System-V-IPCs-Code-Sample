/*
** EPITECH PROJECT, 2018
** Sys V IPCs
** File description:
** Created by arthur,
*/

#ifndef IPCS_FUNCS_H
# define IPCS_FUNCS_H

#include <sys/ipc.h>
#include <stdlib.h>

#include "ipcs_defines.h"

/*
 *	Wraps for IPCs functions.
 */

key_t xftok(const char *path, int proj_id);
int xsemget(key_t key, int nsems, int semflg);
int xshmget(key_t key, size_t size, int shmflg);
void *xshmat(int shmid, const void *shmaddr, int shmflg);
int xmsgget(key_t key, int msgflg);

/*
 *	Initialization functions.
 */

char *init_track(char *track);
char *init_tracks(int *shm_id, key_t key);

/*
 *	Processes functions.
 */

void train_proc(const char *path, unsigned int rank);

/*
 *	Priting functions
 */

void display_procs_msq(char *tracks, char *sample, int msg_id);
void display_procs_shm(char *tracks, char *sample);

/*
 *	Destruction functions.
 */

void kill_unfinished_procs(const pid_t procs [NB_TRAINS]);
void wait_procs(const pid_t procs [NB_TRAINS]);

#endif /* !IPCS_FUNCS_H */
