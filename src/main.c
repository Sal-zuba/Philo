/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:56:36 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/12/21 20:20:31 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	destory(t_general *g)
{
	int	i;

	i = -1;
	while (++i < g->number_of_p)
	{
		pthread_mutex_destroy(&g->forks[i]);
		pthread_mutex_destroy(&g->philo[i].makla);
		pthread_mutex_destroy(&g->philo[i].tmp);
	}
	pthread_mutex_destroy(&g->t);
	pthread_mutex_destroy(&g->print);
}

void	leaks()
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_general	g;

	// atexit(leaks);
	if (check_args(argc, argv) == 0)
		return (1);
	if (init(&g, argv) == 1)
		return (1);
	if (init_threads(&g) == 1)
		return (1);
	destory(&g);
	return (0);
}