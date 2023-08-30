/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 15:20:37 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/30 13:53:38 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t			philo_thread;
	bool				full;
	int					id;
	int					right_fork;
	int					left_fork;
	int					times_eaten;
	long unsigned int	time_of_last_eat;
	struct s_data		*d_struct;
}	t_philo;

typedef struct s_data
{
	int					ph_nb;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_of_eats;
	int					error;
	int					full_philos;
	bool				stop_sim;
	long unsigned int	start_of_sim;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printing;
	pthread_mutex_t		death;
	pthread_mutex_t		start;
	t_philo				*philos;
	pthread_t			big_brother;
}						t_data;

void				*ft_calloc(size_t size);
bool				sim_should_stop(t_data *d_struct);
bool				run_simulation(t_data *d_struct);
void				wrong_input(char *error_type);
bool				parse_and_validate_input(char *argv[], t_data *d_struct);
size_t				ft_strlen(char *str);
void				better_usleep(long unsigned int time, t_philo *philo);
bool				initialize_simulation(t_data *d_struct);
void				*philo_life_cycle(void *d_struct);
void				error_message(char *message);
void				print_message(t_philo *philo, char *message, char *colour);
bool				create_big_brother(t_data *d_struct);
bool				am_i_dead(t_philo *philo);
long unsigned int	timestamp(t_data *d_struct);

#endif
