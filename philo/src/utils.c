/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 16:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/30 13:55:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"
#include "defines.h"
#include <stdio.h>
#include <string.h>

void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, size);
	return (ptr);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

bool	am_i_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->d_struct->death);
	if (timestamp(philo->d_struct) - philo->time_of_last_eat \
		>= (unsigned long int)philo->d_struct->time_to_die \
		&& philo->d_struct->stop_sim == false)
	{
		philo->d_struct->stop_sim = true;
		pthread_mutex_unlock(&philo->d_struct->death);
		print_message(philo, DEAD, RED);
		return (true);
	}
	pthread_mutex_unlock(&philo->d_struct->death);
	return (false);
}

bool	sim_should_stop(t_data *d_struct)
{
	pthread_mutex_lock(&d_struct->death);
	if (d_struct->stop_sim == true)
	{
		pthread_mutex_unlock(&d_struct->death);
		return (true);
	}
	pthread_mutex_unlock(&d_struct->death);
	return (false);
}

// printf("%s%lu %d %s%s\n", colour, timestamp(philo->d_struct),
// 				philo->id, message, END);

// printf("%lu %d %s\n", timestamp(philo->d_struct),
// 				philo->id, message);

void	print_message(t_philo *philo, char *message, char *colour)
{
	(void)colour;
	pthread_mutex_lock(&philo->d_struct->printing);
	if (sim_should_stop(philo->d_struct) == false || message == DEAD)
		printf("%s%lu %d %s%s\n", colour, timestamp(philo->d_struct), \
				philo->id, message, END);
	pthread_mutex_unlock(&philo->d_struct->printing);
}
