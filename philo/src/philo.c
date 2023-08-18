/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 13:51:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/18 12:46:29 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

// static void	safe_mutex_destroy(pthread_mutex_t *mutex);
// {
// 	if (pthread_mutex_lock(mutex))
// }

void	free_struct(t_data *data_struct)
{
	int	i;

	i = 0;
	while (data_struct->forks != NULL && i < data_struct->philo_nbr)
	{
		pthread_mutex_destroy(&data_struct->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data_struct->printing);
	pthread_mutex_destroy(&data_struct->death);
	pthread_mutex_destroy(&data_struct->start);
	free(data_struct->philos);
	free(data_struct->forks);
	free(data_struct);
}

void	lks(void)
{
	system("leaks philo");
}

int	main(int argc, char *argv[])
{
	t_data	*data_struct;

	// atexit(lks);
	if (argc != 5 && argc != 6)
	{
		wrong_input("Incorrect amount of arguments");
		return (1);
	}
	data_struct = ft_calloc(sizeof(t_data));
	if (data_struct == NULL)
	{
		error_message("malloc failure\n");
		return (1);
	}
	if (parse_and_validate_input(argc, argv, data_struct) == false)
	{
		free_struct(data_struct);
		return (1);
	}
	if (initialize_simulation(data_struct) == false)
	{
		free_struct(data_struct);
		return (1);
	}
	if (run_simulation(data_struct) == false)
	{
		free_struct(data_struct);
		return (1);
	}
	free_struct(data_struct);
	return (0);
}
