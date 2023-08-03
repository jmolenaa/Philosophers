/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 15:20:37 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/03 16:04:58 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define END "\033[0m"
# define DAY 86400000

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_data
{
	unsigned int	nbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nbr_of_eats;
	int				error;
}				t_data;

typedef struct s_philo
{
	int	asd;
}	t_philo;

void	wrong_input(char *error_type);
bool	parse_and_validate_input(int argc, char *argv[], t_data *data_struct);
size_t	ft_strlen(char *str);
bool	initialize_simulation(t_data *data_struct);

#endif
