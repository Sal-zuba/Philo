/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:48:01 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/12/21 21:08:51 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init(t_general *g, char **argv)
{
	int	i;

	i = -1;
	if (set_rules(g, argv) == 1)
		return (1);
	while (++i < g->number_of_p)
	{
		pthread_mutex_init(&g->forks[i], NULL);
		pthread_mutex_init(&g->philo[i].makla, NULL);
		pthread_mutex_init(&g->philo[i].tmp, NULL);
		g->philo[i].t = &g->t;
		g->philo[i].print = &g->print;
	}
	g->philo[0].r_fork = &g->forks[0];
	g->philo[0].l_fork = &g->forks[g->number_of_p - 1];
	i = 0;
	while (++i < g->number_of_p)
	{
		g->philo[i].r_fork = &g->forks[i];
		g->philo[i].l_fork = &g->forks[i - 1];
	}
	init_philos(g);
	return (0);
}

int	set_rules(t_general *g, char **argv)
{
	g->number_of_p = ft_atoi(argv[1]);
	g->time_to_die = (long) ft_atoi(argv[2]);
	g->time_to_eat = (long) ft_atoi(argv[3]);
	g->time_to_sleep = (long) ft_atoi(argv[4]);
	g->all_ate = 0;
	if (argv[5])
		g->number_of_meals = ft_atoi(argv[5]);
	else
		g->number_of_meals = -1;
	if (g->number_of_p < 2 || g->number_of_p > 200 || g->time_to_die < 60
		|| g->time_to_eat < 0 || g->time_to_sleep < 0)
		return (1);
	g->died = 0;
	g->n_forks = ft_atoi(argv[1]);
	pthread_mutex_init(&g->print, NULL);
	pthread_mutex_init(&g->t, NULL);
	return (0);
}

int	init_philos(t_general *g)
{
	int	i;

	i = -1;
	while (++i < g->number_of_p)
	{
		g->philo[i].id = i + 1;
		g->philo[i].eating = 0;
		g->philo[i].time_to_eat = g->time_to_eat;
		g->philo[i].time_to_sleep = g->time_to_sleep;
		g->philo[i].time_to_die = g->time_to_die;
		g->philo[i].number_of_meals = g->number_of_meals;
		g->philo[i].dead = &g->died;
		g->philo[i].ate = 0;
	}
	return (1);
}

void	check(t_general *g)
{
	int	i;
	int	number;

	number = 0;
	i = -1;
	while (++i < g->number_of_p)
	{
		pthread_mutex_lock(&g->philo[i].makla);
		if (g->philo[i].ate == g->number_of_meals)
			number++;
		pthread_mutex_unlock(&g->philo[i].makla);
	}
	if (number == g->number_of_p)
		g->all_ate = 1;
}

void	death_print(t_philo philo)
{
	pthread_mutex_lock(philo.print);
	printf("%li ", get_init_time() - philo.start);
	printf("%d ", philo.id);
	printf("%s\n", "has died");
}

void	check_death(t_general *g)
{
	int	i;

	i = -1;
	while (++i < g->number_of_p)
	{
		pthread_mutex_lock(&g->philo[i].tmp);
		pthread_mutex_lock(&g->philo[i].makla);
		if ((!g->philo[i].eating && get_init_time() >= g->philo[i].ttd))
		{
			pthread_mutex_unlock(&g->philo[i].makla);
			pthread_mutex_unlock(&g->philo[i].tmp);
			pthread_mutex_lock(&g->t);
			g->died = 1;
			pthread_mutex_unlock(&g->t);
			death_print(g->philo[i]);
			break ;
		}
		pthread_mutex_unlock(&g->philo[i].tmp);
		pthread_mutex_unlock(&g->philo[i].makla);
	}
}

void	death(t_general *g)
{
	int	i;

	i = -1;
	usleep(g->time_to_die);
	while (1)
	{
		check(g);
		check_death(g);
		if (g->died)
			break ;
		if (g->all_ate)
			break ;
		usleep(g->time_to_die / 2);
	}
}
int	init_threads(t_general *g)
{
	int		i;

	i = -1;
	g->start_time = get_init_time();
	while (++i < g->number_of_p)
		g->philo[i].start = g->start_time;
	i = -1;
	while (++i < g->number_of_p)
	{
			g->philo[i].last_meal = get_init_time();
			g->philo[i].ttd = g->philo[i].last_meal + g->philo[i].time_to_die;
		if (pthread_create(&g->tmp[i], NULL, &routine, &g->philo[i]) == 1)
			return (1);
	}
	death(g);
	i = -1;
	while (++i < g->number_of_p)
	{
		if (pthread_join(g->tmp[i], NULL))
		{
			pthread_mutex_unlock(&g->print);
			return (1);
		}
	}
	pthread_mutex_unlock(&g->print);
	return (0);
}
