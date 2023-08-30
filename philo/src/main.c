/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 13:51:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/30 13:52:59 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) == 0)
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_destroy(mutex);
	}
}

static void	free_struct(t_data *d_struct)
{
	int	i;

	i = 0;
	while (d_struct->forks != NULL && i < d_struct->ph_nb)
	{
		safe_mutex_destroy(&d_struct->forks[i]);
		i++;
	}
	safe_mutex_destroy(&d_struct->printing);
	safe_mutex_destroy(&d_struct->death);
	safe_mutex_destroy(&d_struct->start);
	free(d_struct->philos);
	free(d_struct->forks);
	free(d_struct);
}

void	lks(void)
{
	system("leaks -q philo");
}

	// atexit(lks);

int	main(int argc, char *argv[])
{
	t_data	*d_struct;
	int		return_value;

	return_value = 0;
	if (argc != 5 && argc != 6)
	{
		wrong_input("Incorrect amount of arguments");
		return (1);
	}
	d_struct = ft_calloc(sizeof(t_data));
	if (d_struct == NULL)
	{
		error_message("malloc failure\n");
		return (1);
	}
	else if (parse_and_validate_input(argv, d_struct) == false)
		return_value = 1;
	else if (initialize_simulation(d_struct) == false)
		return_value = 1;
	else if (run_simulation(d_struct) == false)
		return_value = 1;
	free_struct(d_struct);
	return (return_value);
}
