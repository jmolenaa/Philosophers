/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:03:02 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/31 09:27:55 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	initialize_d_struct(t_data *d_struct)
{
	d_struct->philos = ft_calloc(sizeof(t_philo) * d_struct->philo_nb);
	d_struct->forks = ft_calloc(sizeof(pthread_mutex_t) * d_struct->philo_nb);
	if (d_struct->philos == NULL || d_struct->forks == NULL)
	{
		error_message("malloc failure\n");
		return (false);
	}
	if (pthread_mutex_init(&d_struct->printing, NULL) != 0 || \
		pthread_mutex_init(&d_struct->death, NULL) != 0 || \
		pthread_mutex_init(&d_struct->start, NULL) != 0)
	{
		error_message("mutex initialization failure\n");
		return (false);
	}
	return (true);
}

static bool	initialize_philos(t_philo *philos, t_data *d_struct)
{
	int	i;

	i = 0;
	while (i < d_struct->philo_nb)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = i;
		philos[i].left_fork = (i + 1) % d_struct->philo_nb;
		philos[i].d_struct = d_struct;
		if (pthread_mutex_init(&d_struct->forks[i], NULL) != 0)
		{
			error_message("mutex initialization failure\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	initialize_simulation(t_data *d_struct)
{
	if (initialize_d_struct(d_struct) == false)
		return (false);
	if (initialize_philos(d_struct->philos, d_struct) == false)
		return (false);
	return (true);
}
