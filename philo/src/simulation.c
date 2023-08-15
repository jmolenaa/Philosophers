/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 11:20:11 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/13 15:01:59 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	create_threads(t_data *data_struct)
{
	int	i;

	i = 0;
	while (i < data_struct->philo_nbr)
	{
		printf("%d\n", i);
		if (pthread_create(&(data_struct->philos[i].philo_thread), NULL, philo_life_cycle, &data_struct->philos[i]) != 0)
		{
			// pthread_mutex_lock(&data_struct->printing);
			error_message("thread creation failure");
			// pthread_mutex_unlock(&data_struct->printing);
			return (false);
		}
		// printf("%d\n", j);
		i++;
	}
	return (true);

}

static bool	join_threads(t_data *data_struct)
{
	int	i;

	i = 0;
	while (i < data_struct->philo_nbr)
	{
		if (pthread_join(data_struct->philos[i].philo_thread, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

bool run_simulation(t_data *data_struct)
{
	int	i;

	i = 0;
	data_struct->start_of_sim = get_time();
	if (create_threads(data_struct) == false)
		return (false);
	if (join_threads(data_struct) == false)
		return (false);
	return (true);
}