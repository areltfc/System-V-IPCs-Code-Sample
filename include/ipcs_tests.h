/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** Created by arthur,
*/

#ifndef IPCS_TESTS_H_
# define IPCS_TESTS_H_

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
 *	Wraps for IPCs functions.
 */

key_t xftok(const char *path, int proj_id);
int xsemget(key_t key, int nsems, int semflg);
int xshmget(key_t key, size_t size, int shmflg);
void *xshmat(int shmid, const void *shmaddr, int shmflg);

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
 *	Destruction functions.
 */

void kill_unfinished_procs(const pid_t procs [NB_TRAINS]);
void wait_procs(const pid_t procs [NB_TRAINS]);

#endif /* !IPCS_TESTS_H_ */
