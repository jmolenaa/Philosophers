/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 11:20:11 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/31 09:37:07 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads_back(t_data *d_struct, int i)
{
	int	j;

	d_struct->stop_sim = true;
	pthread_mutex_unlock(&d_struct->start);
	j = 0;
	while (j < i)
	{
		if (pthread_join(d_struct->philos[j].philo_thread, NULL) != 0)
		{
			error_message("error joining threads\n");
			return ;
		}
		j++;
	}
}

static bool	create_philo_threads(t_data *d_struct)
{
	int	i;

	i = 0;
	while (i < d_struct->philo_nb)
	{
		if (pthread_create(&(d_struct->philos[i].philo_thread), \
			NULL, philo_life_cycle, &d_struct->philos[i]) != 0)
		{
			error_message("thread creation failure\n");
			join_threads_back(d_struct, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	join_threads(t_data *d_struct)
{
	int	i;

	if (pthread_join(d_struct->big_brother, NULL) != 0)
	{
		error_message("error joining threads\n");
		return (false);
	}
	i = 0;
	while (i < d_struct->philo_nb)
	{
		if (pthread_join(d_struct->philos[i].philo_thread, NULL) != 0)
		{
			error_message("error joining threads\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	run_simulation(t_data *d_struct)
{
	pthread_mutex_lock(&d_struct->start);
	if (create_philo_threads(d_struct) == false)
		return (false);
	if (create_big_brother(d_struct) == false)
	{
		join_threads_back(d_struct, d_struct->philo_nb);
		return (false);
	}
	d_struct->start_of_sim = timestamp(d_struct);
	pthread_mutex_unlock(&d_struct->start);
	if (join_threads(d_struct) == false)
		return (false);
	return (true);
}
