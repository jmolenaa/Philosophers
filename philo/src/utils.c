/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 16:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/13 14:06:24 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	print_message(unsigned int time, int philo, char *message)
{
	printf("%u %d %s\n", time, philo, message);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}
