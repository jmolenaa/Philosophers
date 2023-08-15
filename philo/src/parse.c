/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 17:16:30 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/08 14:57:37 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static bool	numbers_are_valid(t_data data_struct)
{
	if (data_struct.error == 1)
		wrong_input("Arguments should contain only digits");
	else if (data_struct.error == 2)
		wrong_input("One of the arguments is 0");
	else if (data_struct.philo_nbr > 3000)
		wrong_input("Table too small for this many philosophers");
	else if (data_struct.time_to_die > DAY)
		wrong_input("Saving electricity by not running a simulation for a day");
	else if (data_struct.time_to_eat > DAY \
			|| data_struct.time_to_sleep > DAY)
		wrong_input("Please use smaller numbers"
			", philos don't need more than a day to eat or sleep");
	else if (data_struct.nbr_of_eats > DAY)
		wrong_input("Philosophers exploded after too many meals");
	else
		return (true);
	return (false);
}

static void	ft_atou(char *argv, int *nbr, int *error)
{
	int	i;

	i = 0;
	*nbr = 0;
	if (argv == NULL)
		return ;
	while (*(argv + i) >= '0' && *(argv + i) <= '9')
	{
		*nbr = *nbr * 10 + *(argv + i) - 48;
		i++;
	}
	if (*(argv + i) != '\0' && *error == 0)
		*error = 1;
	else if (*nbr == 0 && *error == 0)
		*error = 2;
	else if (i > 9 && *error == 0)
		*nbr = INT32_MAX;
}

static bool	strings_are_valid(char *argv[])
{
	int	i;

	i = 1;
	while (*(argv + i) != NULL)
	{
		if (**(argv + i) == '\0')
			wrong_input("One of the arguments is empty");
		else if (**(argv + i) == '0' && *(*(argv + i) + 1) != '\0')
			wrong_input("One of the arguments has leading zeros");
		else
		{
			i++;
			continue ;
		}
		return (false);
	}
	return (true);
}

bool	parse_and_validate_input(int argc, char *argv[], t_data *data_struct)
{
	(void)argc;
	if (strings_are_valid(argv) == false)
		return (false);
	data_struct->error = 0;
	ft_atou(argv[1], &(data_struct->philo_nbr), &(data_struct->error));
	ft_atou(argv[2], &(data_struct->time_to_die), &(data_struct->error));
	ft_atou(argv[3], &(data_struct->time_to_eat), &(data_struct->error));
	ft_atou(argv[4], &(data_struct->time_to_sleep), &(data_struct->error));
	ft_atou(argv[5], &(data_struct->nbr_of_eats), &(data_struct->error));
	if (numbers_are_valid(*data_struct) == false)
		return (false);
	return (true);
}
