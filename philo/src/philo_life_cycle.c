/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life_cycle.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 11:22:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/15 14:58:42 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_struct->printing);
	print_message(get_time() - philo->data_struct->start_of_sim, philo->id, EAT);
	pthread_mutex_unlock(&philo->data_struct->printing);
	better_usleep(philo->data_struct->time_to_eat * 1000);
}

void	*philo_life_cycle(void *philo)
{
	while (1)
	{
		eat(philo);
		// sleep(philo);
		// think(philo);
	}
	return (NULL);
}
