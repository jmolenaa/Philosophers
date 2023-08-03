/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 14:05:22 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/03 13:18:31 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	wrong_input(char *error_type)
{
	write(2, RED"philo: ", 14);
	write(2, error_type, ft_strlen(error_type));
	write(2, END"\nusage: ./philo [number_of_philosophers]"
		" [time_to_die] [time_to_eat] \n	[time_to_sleep]"
		" [number_of_times_each_philosopher_must_eat]\n\n"
		"number_of_philosophers			(1 to 3000)\n"
		"time_to_die				(1 to 86400000)\n"
		"time_to_eat				(1 to 86400000)\n"
		"time_to_sleep				(1 to 86400000)\n"
		"nbr_of_times_each_philosopher_must_eat	(1 to 86400000)\n", 323);
}
