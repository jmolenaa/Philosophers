/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:03:02 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/03 16:08:41 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	initialize_simulation(t_data *data_struct)
{
	(void)data_struct;
	printf("%d\n%d\n%d\n%d\n%d\n", data_struct->nbr_of_philos, data_struct->time_to_die, \
	data_struct->time_to_eat, data_struct->time_to_sleep, data_struct->nbr_of_eats);
	return (true);
}
