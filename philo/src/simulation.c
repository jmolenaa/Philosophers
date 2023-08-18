/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 11:20:11 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/18 11:46:15 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	join_threads_back(t_data *data_struct, int i)
{
	int	j;

	data_struct->stop_sim = true;
	pthread_mutex_unlock(&data_struct->start);
	j = 0;
	while (j < i)
	{
		if (j == 3)
			return ;
		if (pthread_join(data_struct->philos[j].philo_thread, NULL) != 0)
		{
			error_message("error joining threads\n");
			return ;
		}
		j++;
	}
}

static bool	create_philo_threads(t_data *data_struct)
{
	int	i;

	i = 0;
	while (i < data_struct->philo_nbr)
	{
		if (i == 5)
		{
			error_message("thread creation failure\n");
			join_threads_back(data_struct, i);
			return (false);
		}
		if (pthread_create(&(data_struct->philos[i].philo_thread), \
			NULL, philo_life_cycle, &data_struct->philos[i]) != 0)
		{
			error_message("thread creation failure\n");
			join_threads_back(data_struct, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	join_threads(t_data *data_struct)
{
	int	i;

	if (pthread_join(data_struct->big_brother, NULL) != 0)
	{
		error_message("error joining threads\n");
		return (false);
	}
	i = 0;
	while (i < data_struct->philo_nbr)
	{
		if (pthread_join(data_struct->philos[i].philo_thread, NULL) != 0)
		{
			error_message("error joining threads\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	run_simulation(t_data *data_struct)
{
	pthread_mutex_lock(&data_struct->start);
	if (create_philo_threads(data_struct) == false)
		return (false);
	if (create_big_brother(data_struct) == false)
	{
		join_threads_back(data_struct, data_struct->philo_nbr);
		return (false);
	}
	data_struct->start_of_sim = get_time_ms();
	pthread_mutex_unlock(&data_struct->start);
	if (join_threads(data_struct) == false)
		return (false);
	return (true);
}
