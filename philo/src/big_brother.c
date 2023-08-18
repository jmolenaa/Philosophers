/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   big_brother.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 10:35:34 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/18 11:43:52 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "defines.h"

static bool	are_all_philos_alive(t_data *data_struct)
{
	int	i;

	i = 0;
	while (i < data_struct->philo_nbr)
	{
		pthread_mutex_lock(&data_struct->death);
		if (get_time_ms() - data_struct->start_of_sim - data_struct->philos[i].time_of_last_eat \
			>= (unsigned long int)data_struct->time_to_die)
		{
			data_struct->stop_sim = true;
			pthread_mutex_unlock(&data_struct->death);
			print_message(&data_struct->philos[i], DEAD, RED);
			return (false);
		}
		if (data_struct->stop_sim == true)
		{
			pthread_mutex_unlock(&data_struct->death);
			return (false);
		}
		pthread_mutex_unlock(&data_struct->death);
		i++;
	}
	return (true);
}

static void	*invigilation(void *data_struct)
{
	pthread_mutex_lock(&((t_data *)data_struct)->start);
	pthread_mutex_unlock(&((t_data *)data_struct)->start);
	while (1)
	{
		if (are_all_philos_alive(data_struct) == false)
			break ;
		better_usleep(1000, data_struct);
	}
	return (NULL);
}

bool	create_big_brother(t_data *data_struct)
{
	if (pthread_create(&data_struct->big_brother, NULL, invigilation, data_struct) != 0)
	{
		error_message("Observing unsuccesful\n");
		return (false);
	}
	return (true);
}