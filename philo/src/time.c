/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/06 18:05:46 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/15 15:12:14 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long unsigned int	get_time()
{
	struct timeval		d;

	gettimeofday(&d, NULL);
	return (d.tv_sec * 1000 + d.tv_usec / 1000);
}

void	better_usleep(long unsigned int time)
{
	long unsigned int	start;

	// printf("%lu\n", time);
	start = get_time() * 1000;
	usleep(time / 2);
	while(get_time() * 1000 - start < time) 
		usleep(100);
}
