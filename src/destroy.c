/*
** EPITECH PROJECT, 2018
** Sys V IPCs
** File description:
** Created by arthur,
*/

#include <stdlib.h>
#include <signal.h>
#include <wait.h>

#include "ipcs_defines.h"

/*
 *	Wait for all of the processes.
 */

void wait_procs(const pid_t procs [NB_TRAINS])
{
	for (unsigned int i = 0; i < NB_TRAINS; ++i) {
		waitpid(procs[i], NULL, 0x0);
	}
}

/*
 *	SIGKILL and wait for all started processes.
 */

void kill_unfinished_procs(const pid_t procs [NB_TRAINS])
{
	for (unsigned int i = 0; i < NB_TRAINS; ++i) {
		if (procs[i] != 0) {
			kill(procs[i], SIGKILL);
			waitpid(procs[i], NULL, 0x0);
		}
	}
}
