/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 16:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/17 17:05:26 by jmolenaa      ########   odam.nl         */
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
	unsigned long int	time;

	time = get_time_ms() - philo->data_struct->start_of_sim;
	pthread_mutex_lock(&philo->data_struct->printing);
	if (sim_should_stop(philo->data_struct) == false || message == DEAD)
		printf("%s%lu %d %s%s\n", colour, time, philo->id, message, END);
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
