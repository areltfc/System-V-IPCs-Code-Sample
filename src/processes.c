/*
** EPITECH PROJECT, 2018
** Sys V IPCs
** File description:
** Created by arthur,
*/

#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ipcs_defines.h"
#include "ipcs_funcs.h"

void send_pos(const int msg_id, const unsigned int pos,
	      const unsigned int rank)
{
	struct msgbuf buff;

	memset(&buff, 0, sizeof(buff));
	buff.mtype = rank;
	sprintf(buff.mtext, "%u", pos);
	msgsnd(msg_id, &buff, sizeof(buff.mtext), rank);
}

/*
 *	Piece of code used many times in cross_bridge(), worth grouping it.
 */

static char *update_track(char *track, char *save, const unsigned int pos)
{
	if (pos > 0)
		track[pos - 1] = *save;
	*save = track[pos];
	track[pos] = '#';
	return (track);
}

/*
 *	Advance and update position. When trying to cross the bridge,
 *	lower the semaphore in order to make sure not too many trains
 *	cross in the same time.
 *	Then, increment it to allow the next train to come.
 */

static char *cross_bridge(char *track, const int msg_id,
			  const int sem_id, struct sembuf *sem,
			  const unsigned int rank)
{
	char save_char = 0;
	unsigned int pos = 0;

	for (; pos < BRIDGE_BEG; ++pos) {
		send_pos(msg_id, pos, rank + 1);
		track = update_track(track, &save_char, pos);
		sleep(1);
	}
	semop(sem_id, sem, 1);
	for (; pos < BRIDGE_END; ++pos) {
		send_pos(msg_id, pos, rank + 1);
		track = update_track(track, &save_char, pos);
		sleep(1);
	}
	sem->sem_op = 1;
	semop(sem_id, sem, 1);
	for (; pos < TOTAL_SIZE; ++pos) {
		send_pos(msg_id, pos, rank + 1);
		track = update_track(track, &save_char, pos);
		sleep(1);
	}
}

/*
 *	Retrieve the semaphore and shared memory ids.
 *	Attach, cross the bridge, detach.
 *	exit() mustn't be forgotten: it is a process, a return
 *	wouldn't terminate it.
 */

void train_proc(const char *path, const unsigned int rank)
{
	key_t key = xftok(path, 0);
	int sem_id = xsemget(key, 1, SHM_RW);
	int msg_id = xmsgget(key, SHM_RW);
	int shm_id = xshmget(key, MEM_SIZE, SHM_RW);
	struct sembuf sem = { 0, -1, 0 };
	char *tracks = xshmat(shm_id, NULL, 0);
	char *track = TRACKS(rank);

	cross_bridge(track, msg_id, sem_id, &sem, rank);
	shmdt((void *) tracks);
	exit(0);
}
