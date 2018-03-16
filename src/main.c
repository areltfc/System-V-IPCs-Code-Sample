/*
** EPITECH PROJECT, 2018
** Sys V IPCs
** File description:
** Created by arthur,
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "ipcs_defines.h"
#include "ipcs_funcs.h"

/*
 *	fork() once for every train, and print their advancement, before
 *	waiting for everyone.
 *
 * 	For simplicity's sake, the trains will all use both shared memory
 * 	and message queues, only the printing mechanism will change.
 * 	If you want to change the method used, set USE_SHM to either a
 * 	positive or a null value.
 *
 *	The sample used by the printing function is created here in order
 *	to avoid a race condition: we do not want a 'tainted' railroad
 *	sample. It is also free()'d here in order to group declaration &
 *	destruction in the same place.
 *
 *	If one fork() fails, kill all of them and leave.
 */

static int launch_processes(char *tracks, const int msg_id, const char *path)
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
#if USE_SHM
	display_procs_shm(tracks, sample);
#else
	display_procs_msq(tracks, sample, msg_id);
#endif
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
	int msg_id;
	char *tracks = init_tracks(&shm_id, token);

	msg_id = xmsgget(token, IPC_CREAT | IPC_EXCL | SHM_RW);
	sem_id = xsemget(token, 1, IPC_CREAT | IPC_EXCL | SHM_RW);
	semctl(sem_id, 0, SETVAL, NB_RAILWAYS);
	launch_processes(tracks, msg_id, av[1]);
	msgctl(msg_id, IPC_RMID, NULL);
	semctl(sem_id, 0, IPC_RMID);
	shmdt((void *) tracks);
	shmctl(shm_id, IPC_RMID, NULL);
	return (0);
}