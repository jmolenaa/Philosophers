/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life_cycle.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 11:22:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/30 15:25:16 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "defines.h"

static void	count_meals(t_philo *philo)
{
	philo->times_eaten++;
	pthread_mutex_lock(&philo->d_struct->death);
	if (philo->d_struct->nbr_of_eats != 0 && \
		philo->times_eaten == philo->d_struct->nbr_of_eats \
		&& philo->full == false)
	{
		philo->d_struct->full_philos++;
		philo->full = true;
		if (philo->d_struct->full_philos == philo->d_struct->philo_nb)
			philo->d_struct->stop_sim = true;
	}
	pthread_mutex_unlock(&philo->d_struct->death);
}

static void	eat(t_philo *philo)
{
	print_message(philo, EAT, GREEN);
	pthread_mutex_lock(&philo->d_struct->death);
	philo->time_of_last_eat = timestamp(philo->d_struct);
	pthread_mutex_unlock(&philo->d_struct->death);
	better_usleep(philo->d_struct->time_to_eat * 1000, philo);
	count_meals(philo);
}

static bool	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->d_struct->forks[philo->right_fork]);
	print_message(philo, FORK, YELLOW);
	pthread_mutex_lock(&philo->d_struct->forks[philo->left_fork]);
	print_message(philo, FORK, YELLOW);
	return (true);
}

static void	drop_forks_and_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->d_struct->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->d_struct->forks[philo->left_fork]);
	print_message(philo, SLEEP, CYAN);
	better_usleep(philo->d_struct->time_to_sleep * 1000, philo);
	print_message(philo, THINK, MAGENTA);
}

void	*philo_life_cycle(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	pthread_mutex_lock(&philo->d_struct->start);
	pthread_mutex_unlock(&philo->d_struct->start);
	if (philo->id % 2 == 0)
		better_usleep(philo->d_struct->time_to_eat * 100, philo);
	while (sim_should_stop(philo->d_struct) == false)
	{
		take_forks(philo);
		eat(philo);
		drop_forks_and_sleep(philo);
	}
	return (NULL);
}
