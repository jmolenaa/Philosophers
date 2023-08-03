/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 13:51:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/03 16:02:53 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data_struct;

	if (argc != 5 && argc != 6)
	{
		wrong_input("Incorrect amount of arguments");
		return (1);
	}
	if (parse_and_validate_input(argc, argv, &data_struct) == false)
		return (1);
	if (initialize_simulation(&data_struct) == false)
		return (1);
	printf("lol\n");
	return (0);
}
