/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 13:51:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/13 13:45:55 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

void	free_struct(t_data *data_struct)
{
	int	i;

	i = 0;
	while (i < data_struct->philo_nbr)
	{
		// printf("%d\n", pthread_mutex_destroy(&data_struct->forks[i]));
		pthread_mutex_destroy(&data_struct->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data_struct->printing);
	free(data_struct->philos);
	free(data_struct->forks);
}

int	main(int argc, char *argv[])
{
	t_data	data_struct;

	if (argc != 5 && argc != 6)
	{
		wrong_input("Incorrect amount of arguments");
		return (1);
	}
	if (parse_and_validate_input(argc, argv, &data_struct) == false)
		return (1);
	if (initialize_simulation(&data_struct) == false)
	{
		free_struct(&data_struct);
		return (1);
	}
	if (run_simulation(&data_struct) == false)
	{
		free_struct(&data_struct);
		return (1);
	}
	// printf("lol\n");
	// printf("%d\n", pthread_mutex_lock(&data_struct.forks[0]));
	pthread_mutex_lock(&data_struct.printing);
	error_message("hi\n");
	pthread_mutex_unlock(&data_struct.printing);
	free_struct(&data_struct);
	usleep(10000);
	data_struct.start_of_sim = get_time();
	// int i = pthread_mutex_init(&(data_struct.forks[0]), NULL);
	// printf("%d\n", i);
	// i = pthread_mutex_destroy(&(data_struct.forks[0]));
	// printf("%d\n", i);
	// i = pthread_mutex_destroy(&(data_struct.forks[0]));
	// printf("%d\n", i);

	// printf("%lu\n", data_struct.start_of_sim);
	// while (get_time() - data_struct.start_of_sim <= data_struct.time_to_die)
	// {
		// usleep(10000000);
	// }
	// printf("philo died\n");
	// printf("%lu\n", get_time() - data_struct.start_of_sim);
	// printf("lol\n");
	return (0);
}
