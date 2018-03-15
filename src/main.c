/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** Created by arthur,
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ipcs_tests.h"

/*
 *	Display every railroad, count how many trains are done, sleep,
 *	rinse and repeat.
 */

static void display_procs(char *tracks, char *sample)
{
	sample[TOTAL_SIZE - 1] = '#';
	for (unsigned int done_count = 0; done_count < NB_TRAINS;) {
		done_count = 0;
		for (unsigned int i = 0; i < NB_TRAINS; ++i) {
			printf("%u:\t%s\n", i, TRACKS(i));
			if (strcmp(TRACKS(i), sample) == 0)
				++done_count;
		}
		printf("\n");
		sleep(1);
	}
}

/*
 *	fork() once for every train, and print their advancement, before
 *	waiting for everyone.
 *
 *	The sample used by the printing function is created here in order
 *	to avoid a race condition: we do not want a 'tainted' railroad
 *	sample. It is also free()'d here in order to group declaration &
 *	destruction in the same place.
 *
 *	If one fork() fails, kill all of them and leave.
 */

static int launch_processes(char *tracks, const char *path)
{
	pid_t processes [NB_TRAINS];
	pid_t current = 0;
	char *sample = strdup(tracks);

	if (!sample)
		return (84);
	memset(processes, 0, sizeof(processes));
	for (unsigned int i = 0; i < NB_TRAINS; ++i) {
		current = fork();
		if (current == -1) {
			kill_unfinished_procs(processes);
			return (84);
		} else if (current == 0) {
			train_proc(path, i);
		} else {
			processes[i] = current;
		}
	}
	display_procs(tracks, sample);
	free(sample);
	wait_procs(processes);
	return (0);
}

/*
 *	Init everything the head into the algorithm.
 */

int main(int ac, char **av)
{
	key_t token = xftok(av[1], 0);
	int sem_id;
	int shm_id;
	char *tracks = init_tracks(&shm_id, token);

	sem_id = xsemget(token, 1, IPC_CREAT | IPC_EXCL | SHM_RW);
	semctl(sem_id, 0, SETVAL, NB_RAILWAYS);
	launch_processes(tracks, av[1]);
	semctl(sem_id, 0, IPC_RMID);
	shmdt((void *) tracks);
	shmctl(shm_id, IPC_RMID, NULL);
	return (0);
}