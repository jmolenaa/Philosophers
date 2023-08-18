/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 15:21:07 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/31 17:01:46 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

void	*func(void *j)
{
	*(int *)j = 4;
	return (j);
}

int	main(void)
{
	pthread_t	huh;
	int			j;
	void		*p;
	int			i;

	i = pthread_create(&huh, NULL, func, &j);
	sleep (5);
	j = pthread_join(huh, &p);
	j = pthread_join(huh, &p);
	printf("%p\n", p);
	printf("%d\n", i);
	printf("%d\n", j);
}
