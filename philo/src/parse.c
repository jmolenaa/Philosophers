/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 17:16:30 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/31 09:30:07 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "defines.h"
#include <stdlib.h>

static bool	numbers_are_valid(t_data d_struct)
{
	if (d_struct.error == 1)
		wrong_input("Arguments should contain only digits");
	else if (d_struct.error == 2)
		wrong_input("One of the arguments is 0");
	else if (d_struct.philo_nb > 3000)
		wrong_input("Table too small for this many philosophers");
	else if (d_struct.time_to_die > DAY)
		wrong_input("Saving electricity by not running a simulation for a day");
	else if (d_struct.time_to_eat > DAY \
			|| d_struct.time_to_sleep > DAY)
		wrong_input("Please use smaller numbers"
			", philos don't need more than a day to eat or sleep");
	else if (d_struct.nbr_of_eats > DAY)
		wrong_input("Philosophers exploded after too many meals");
	else
		return (true);
	return (false);
}

static void	ft_atoi(char *argv, int *nbr, int *error)
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

static bool	strings_are_empty_or_have_leading_zeros(char *argv[])
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
		return (true);
	}
	return (false);
}

bool	parse_and_validate_input(char *argv[], t_data *d_struct)
{
	if (strings_are_empty_or_have_leading_zeros(argv) == true)
		return (false);
	d_struct->error = 0;
	ft_atoi(argv[1], &(d_struct->philo_nb), &(d_struct->error));
	ft_atoi(argv[2], &(d_struct->time_to_die), &(d_struct->error));
	ft_atoi(argv[3], &(d_struct->time_to_eat), &(d_struct->error));
	ft_atoi(argv[4], &(d_struct->time_to_sleep), &(d_struct->error));
	ft_atoi(argv[5], &(d_struct->nbr_of_eats), &(d_struct->error));
	if (numbers_are_valid(*d_struct) == false)
		return (false);
	return (true);
}
