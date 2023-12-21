/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:17:57 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/12/21 21:19:22 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] == '\n' || (str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = (res * 10) + str[i] - 48;
		i++;
	}
	return (res);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (write(2, "Wrong number of arguments!\n", 28), 0);
	while (i < argc)
	{
		if ((ft_atoi(argv[i]) == -1 || (ft_atoi(argv[i]) == 0)))
			return (write(2, "Wrong argments!\n", 17), 0);
		i++;
	}
	if ((ft_atoi(argv[1]) == 1))
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]));
		printf("%d ", ft_atoi(argv[2]));
		printf("1 has died\n");
		return (0);
	}
	return (1);
}
