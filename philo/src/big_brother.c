/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   big_brother.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 10:35:34 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/30 13:49:43 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static bool	are_all_philos_alive(t_data *d_struct)
{
	int	i;

	i = 0;
	while (i < d_struct->ph_nb)
	{
		am_i_dead(&d_struct->philos[i]);
		pthread_mutex_lock(&d_struct->death);
		if (d_struct->stop_sim == true)
		{
			pthread_mutex_unlock(&d_struct->death);
			return (false);
		}
		pthread_mutex_unlock(&d_struct->death);
		i++;
	}
	return (true);
}

static void	*invigilation(void *d_struct)
{
	pthread_mutex_lock(&((t_data *)d_struct)->start);
	pthread_mutex_unlock(&((t_data *)d_struct)->start);
	while (1)
	{
		if (are_all_philos_alive(d_struct) == false)
			break ;
		usleep(100);
	}
	if (((t_data *)d_struct)->ph_nb == 1)
		pthread_mutex_unlock(&((t_data *)d_struct)->forks[0]);
	return (NULL);
}

bool	create_big_brother(t_data *d_struct)
{
	if (pthread_create(&d_struct->big_brother, \
		NULL, invigilation, d_struct) != 0)
	{
		error_message("Observing unsuccesful\n");
		return (false);
	}
	return (true);
}
