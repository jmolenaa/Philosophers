/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:03:02 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/18 09:31:09 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

// void	*ft_calloc(size_t size)
// {
// 	void	*ptr;
// 	size_t	i;

// 	ptr = malloc(size);
// 	if (ptr == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < size)
// 	{
// 		((char *)ptr)[i] = 0;
// 		i++;
// 	}
// 	return (ptr);
// }

static bool	initialize_data_struct(t_data *data_struct)
{
	data_struct->stop_sim = false;
	data_struct->full_philos = 0;
	data_struct->philos = ft_calloc(sizeof(t_philo) * data_struct->philo_nbr);
	data_struct->forks = ft_calloc(sizeof(pthread_mutex_t) * data_struct->philo_nbr);
	if (data_struct->philos == NULL || data_struct->forks == NULL)
	{
		error_message("malloc failure\n");
		return (false);
	}
	if (pthread_mutex_init(&data_struct->printing, NULL) != 0 || \
		pthread_mutex_init(&data_struct->death, NULL) != 0 || \
		pthread_mutex_init(&data_struct->start, NULL) != 0)
	{
		error_message("mutex initialization failure\n");
		return (false);
	}
	return (true);
}

// static void	assign_forks(t_philo *philo, int philo_nbr, int i)
// {
// 	if (i % 2 == 0)
// 	{
// 		philo->right_fork = i;
// 		philo->left_fork = (i + 1) % philo_nbr;
// 	}
// 	else
// 	{
// 		philo->left_fork = i;
// 		philo->right_fork = (i + 1) % philo_nbr;
// 	}
// }

static bool	initialize_philos(t_philo *philos, t_data *data_struct)
{
	int	i;

	i = 0;
	while (i < data_struct->philo_nbr)
	{
		philos[i].id = i + 1;
		// assign_forks(&philos[i], data_struct->philo_nbr, i);
		philos[i].right_fork = i;
		philos[i].left_fork = (i + 1) % data_struct->philo_nbr;
		philos[i].data_struct = data_struct;
		philos[i].time_of_last_eat = 0;
		philos[i].times_eaten = 0;
		if (pthread_mutex_init(&data_struct->forks[i], NULL) != 0)
		{
			error_message("mutex initialization failure\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	initialize_simulation(t_data *data_struct)
{
	if (initialize_data_struct(data_struct) == false)
		return (false);
	if (initialize_philos(data_struct->philos, data_struct) == false)
		return (false);
	return (true);
}
