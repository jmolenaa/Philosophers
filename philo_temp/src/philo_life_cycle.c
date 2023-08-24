/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life_cycle.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 11:22:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/24 15:40:20 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "defines.h"
#include <unistd.h>

void	eat(t_philo *philo)
{
	print_message(philo, EAT, GREEN);
	pthread_mutex_lock(&philo->data_struct->death);
	philo->time_of_last_eat = timestamp(philo->data_struct);
	pthread_mutex_unlock(&philo->data_struct->death);
	better_usleep(philo->data_struct->time_to_eat * 1000, philo);
	philo->times_eaten++;
	pthread_mutex_lock(&philo->data_struct->death);
	if (philo->times_eaten == philo->data_struct->nbr_of_eats)
	{
		philo->data_struct->full_philos++;
		if (philo->data_struct->full_philos == philo->data_struct->philo_nbr)
			philo->data_struct->stop_sim = true;
	}
	pthread_mutex_unlock(&philo->data_struct->death);
}

static bool	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_struct->forks[philo->right_fork]);
	print_message(philo, FORK, YELLOW);
	pthread_mutex_lock(&philo->data_struct->forks[philo->left_fork]);
	print_message(philo, FORK, YELLOW);
	return (true);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data_struct->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data_struct->forks[philo->left_fork]);
}

static void	_sleep(t_philo *philo)
{
	print_message(philo, SLEEP, CYAN);
	better_usleep(philo->data_struct->time_to_sleep * 1000, philo);
	print_message(philo, THINK, MAGENTA);
}

void	*philo_life_cycle(void *philo)
{
	pthread_mutex_lock(&((t_philo *)philo)->data_struct->start);
	pthread_mutex_unlock(&((t_philo *)philo)->data_struct->start);
	if (((t_philo *)philo)->id % 2 == 0)
		better_usleep(((t_philo *)philo)->data_struct->time_to_eat * 100, ((t_philo *)philo));
	while (sim_should_stop(((t_philo *)philo)->data_struct) == false)
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		_sleep(philo);
	}
	return (NULL);
}
