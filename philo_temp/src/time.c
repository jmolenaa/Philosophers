/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/06 18:05:46 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/24 17:55:11 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "philo.h"

static long unsigned int	get_time_ms(void)
{
	struct timeval		d;

	gettimeofday(&d, NULL);
	return (d.tv_sec * 1000 + d.tv_usec / 1000);
}

long unsigned int	timestamp(t_data *data_struct)
{
	return (get_time_ms() - data_struct->start_of_sim);
}

void	better_usleep(long unsigned int time, t_philo *philo)
{
	long unsigned int	start;

	if (sim_should_stop(philo->data_struct) == true)
		return ;
	start = get_time_ms() * 1000;
	usleep(time / 2);
	while (get_time_ms() * 1000 - start < time)
	{
		usleep(100);
	}
}
