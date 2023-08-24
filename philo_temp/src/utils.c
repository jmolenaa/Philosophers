/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 16:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/24 15:52:21 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"
#include "defines.h"
#include <stdio.h>

void	*ft_calloc(size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

bool	am_i_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_struct->death);
	if (timestamp(philo->data_struct) - philo->time_of_last_eat \
		>= (unsigned long int)philo->data_struct->time_to_die \
		&& philo->data_struct->stop_sim == false)
	{
		philo->data_struct->stop_sim = true;
		pthread_mutex_unlock(&philo->data_struct->death);
		print_message(philo, DEAD, RED);
		return (true);
	}
	pthread_mutex_unlock(&philo->data_struct->death);
	return (false);
}

bool	sim_should_stop(t_data *data_struct)
{
	pthread_mutex_lock(&data_struct->death);
	if (data_struct->stop_sim == true)
	{
		pthread_mutex_unlock(&data_struct->death);
		return (true);
	}
	pthread_mutex_unlock(&data_struct->death);
	return (false);
}

void	print_message(t_philo *philo, char *message, char *colour)
{
	pthread_mutex_lock(&philo->data_struct->printing);
	if (sim_should_stop(philo->data_struct) == false || message == DEAD)
		printf("%s%lu %d %s%s\n", colour, timestamp(philo->data_struct), philo->id, message, END);
	pthread_mutex_unlock(&philo->data_struct->printing);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}
