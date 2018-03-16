/*
** EPITECH PROJECT, 2018
** Sys V IPCs
** File description:
** Created by arthur,
*/

#ifndef IPCS_DEFINES_H_
# define IPCS_DEFINES_H_

/*
 *	Parameters macro, feel free to change them
 *	in order to test the program.
 */

# define NB_TRAINS	7
# define NB_RAILWAYS	3
# define BRIDGE_BEG	3
# define BRIDGE_END	5
# define TOTAL_SIZE	9

/*
 *	Wrapping the IPCs flags into one for convenience.
 */

#ifndef SHM_RW
# define SHM_RW		(SHM_R | SHM_W)
#endif

/*
 *	Convenience macros, shortening and clarifying the code.
 */

# define MEM_SIZE	(sizeof(char) * ((NB_TRAINS * TOTAL_SIZE) + 1))
# define TRACKS(i)	(tracks + ((i) * (TOTAL_SIZE + 1)))

/*
 *	Change this flag's value to:
 *		→ 0 to use the shared memory-centered printing
 *		→ > 0 to use the message queue-centered printing
 */

# define USE_SHM	1

/*
 *	User-defined message queue buffer. For more information,
 *	read `man msgsnd`
 */

struct msgbuf
{
	long mtype;
	char mtext[32];
};

#endif /* !IPCS_DEFINES_H_ */
