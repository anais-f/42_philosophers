/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:33:52 by anfichet          #+#    #+#             */
/*   Updated: 2024/06/14 13:33:52 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_input(int argc, char **argv)
{
	int i;

	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			if (ft_atoi(argv[i]) > 0 && ft_atoi(argv[i]) <= INT_MAX)
				i++;
			else
			{
				printf("Argument %d must be a positive number\n", i);
				return (EXIT_FAILURE);
			}
		}
	}
	else
	{
		write(1, "Wrong numbers of arguments, please check your input\n", 52);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
// gerer max int pour le bloquer dans le parsing

int	ft_atoi(const char *str)
{
	size_t		i;
	long int	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((nb * 10 + str[i] - '0') / 10) != nb)
		{
			if (sign < 0)
				return ((int)LONG_MIN);
			return ((int)LONG_MAX);
		}
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * sign);
}

int get_error_message(int code)
{
	if (code == ERROR_INIT_MUTEX)
	{
		printf("Error init mutex: %s\n", strerror(errno));
		return (ERROR_INIT_MUTEX);
	}
	else if (code == ERROR_DESTROY_MUTEX)
	{
		printf("Error destroy mutex: %s\n", strerror(errno));
		return (ERROR_DESTROY_MUTEX);
	}
	else if (code == ERROR_THREAD)
	{
		printf("Error thread: %s\n", strerror(errno));
		return (ERROR_THREAD);
	}
	return (EXIT_SUCCESS);
}
