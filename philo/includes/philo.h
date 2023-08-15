/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 15:20:37 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/13 15:12:40 by jmolenaa      ########   odam.nl         */
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
# define DEAD "died"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define THINK "is thinking"
# define FORK "has taken a fork"

# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				id;
	int				right_fork;
	int				left_fork;
	struct s_data	*data_struct;
}	t_philo;

typedef struct s_data
{
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_of_eats;
	int					error;
	long unsigned int	start_of_sim;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printing;
	t_philo				*philos;
}						t_data;

bool				run_simulation(t_data *data_struct);
long unsigned int	get_time();
void				wrong_input(char *error_type);
bool				parse_and_validate_input(int argc, char *argv[], t_data *data_struct);
size_t				ft_strlen(char *str);
void				better_usleep(long unsigned int time);
bool				initialize_simulation(t_data *data_struct);
void				*philo_life_cycle(void *data_struct);
void				error_message(char *message);
void				print_message(unsigned int time, int philo, char *message);

#endif
