/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/06 18:05:46 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/30 13:54:37 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

static long unsigned int	get_time_ms(void)
{
	struct timeval	d;

	gettimeofday(&d, NULL);
	return (d.tv_sec * 1000 + d.tv_usec / 1000);
}

long unsigned int	timestamp(t_data *d_struct)
{
	return (get_time_ms() - d_struct->start_of_sim);
}

void	better_usleep(long unsigned int time, t_philo *philo)
{
	long unsigned int	start;

	if (sim_should_stop(philo->d_struct) == true)
		return ;
	start = get_time_ms() * 1000;
	while (get_time_ms() * 1000 - start < time \
			&& am_i_dead(philo) == false)
		usleep(500);
}
