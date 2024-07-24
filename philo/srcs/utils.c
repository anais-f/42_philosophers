/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:33:52 by anfichet          #+#    #+#             */
/*   Updated: 2024/07/24 21:45:30 by anfichet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	int	i;
	int	result;

	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			result = ft_pos_atoi(argv[i]);
			if (result > 0)
				i++;
			else if (result == -2)
				return (get_input_message(-2, i));
			else if (result == -3)
				return (get_input_message(-3, i));
			else
				return (get_input_message(-4, i));
		}
	}
	else
		return (get_input_message(-5, 0));
	return (EXIT_SUCCESS);
}

int	get_input_message(int code, int i)
{
	if (code == -2)
	{
		printf("Argument %d must be less than int_max\n", i);
		return (EXIT_FAILURE);
	}
	else if (code == -3)
	{
		printf("Argument %d must contain only number\n", i);
		return (EXIT_FAILURE);
	}
	else if (code == -4)
	{
		printf("Argument %d must be a positive number\n", i);
		return (EXIT_FAILURE);
	}
	else if (code == -5)
	{
		write(1, "Wrong numbers of arguments, please check your input\n", 52);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_pos_atoi(const char *str)
{
	size_t	i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((nb * 10 + str[i] - '0') / 10) != nb)
			return (-2);
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '\0')
		return (nb);
	else
		return (-3);
}

int	get_error_message(int code)
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
