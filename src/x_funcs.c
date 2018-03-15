/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** Created by arthur,
*/

#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

/*
 *	Security wrap for ftok(). Exit program if something bad occurred,
 *	and print why.
 */

key_t xftok(const char *path, int proj_id)
{
	key_t token;

	token = ftok(path, proj_id);
	if (token == -1) {
		fprintf(stderr, "ftok: %s\n", strerror(errno));
		exit(84);
	}
	return (token);
}

/*
 *	Security wrap for semget(). Exit program if something bad occurred,
 *	and print why.
 */

int xsemget(key_t key, int nsems, int semflg)
{
	int sem_id;

	sem_id = semget(key, nsems, semflg);
	if (sem_id == -1) {
		fprintf(stderr, "semget: %s\n", strerror(errno));
		exit(84);
	}
	return (sem_id);
}

/*
 *	Security wrap for shmget(). Exit program if something bad occurred,
 *	and print why.
 */

int xshmget(key_t key, size_t size, int shmflg)
{
	int shm_id;

	shm_id = shmget(key, size, shmflg);
	if (shm_id == -1) {
		fprintf(stderr, "shmget: %s\n", strerror(errno));
		exit(84);
	}
	return (shm_id);
}

/*
 *	Security wrap for shmat(). Exit program if something bad occurred,
 *	and print why.
 */

void *xshmat(int shmid, const void *shmaddr, int shmflg)
{
	void *addr = NULL;

	addr = shmat(shmid, shmaddr, shmflg);
	if (addr == (void *) -1) {
		fprintf(stderr, "shmat: %s\n", strerror(errno));
		exit(84);
	}
}