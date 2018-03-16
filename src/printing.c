/*
** EPITECH PROJECT, 2018
** Sys V IPCs
** File description:
** Created by arthur,
*/

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "ipcs_defines.h"

/*
 *	Function used to retrieve the message from the message queue.
 *
 *	Using IPC_NOWAIT flag so that if no message was sent (the train is
 *	either waiting or done), just keep going and do not hang: the case
 *	is handled in display_procs_msq().
 */

static unsigned int receive_pos(const int msg_id, const unsigned int rank)
{
	struct msgbuf buff;
	ssize_t ret = 0;

	ret = msgrcv(msg_id, &buff, sizeof(buff.mtext), rank, IPC_NOWAIT);
	if (ret == -1)
		return ((unsigned) -1);
	return ((unsigned) atoi(buff.mtext));
}

/*
 *	Receive the position of moving trains, and print them.
 *	Only moving trains are printed, as they are the only one
 *	to send messages to the message queue, and storing old values
 *	stopped trains would be pointless.
 *
 *	A difference with the shm counterpart is the use for done_count.
 *	It is not reset in our main loop as the end-of-road message is
 *	received once, whereas shared memory does not rely on sent pieces
 *	of information, but rather gathered pieces of information.
 */

void display_procs_msq(char *tracks, char *sample, const int msg_id)
{
	char save = 0;
	unsigned int pos = 0;

	for (unsigned int done_count = 0; done_count < NB_TRAINS;) {
		for (unsigned int i = 0; i < NB_TRAINS; ++i) {
			pos = receive_pos(msg_id, i + 1);
			if (pos == (unsigned) -1)
				continue;
			save = sample[i];
			sample[i] = '#';
			printf("%u:\t%s\n", i, TRACKS(i));
			if (pos == TOTAL_SIZE - 1)
				++done_count;
			sample[i] = save;
		}
		printf("\n");
		sleep(1);
	}
}

/*
 *	Display every railroad, count how many trains are done, sleep,
 *	rinse and repeat.
 */

void display_procs_shm(char *tracks, char *sample)
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