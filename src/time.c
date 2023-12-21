/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:47:25 by sal-zuba          #+#    #+#             */
/*   Updated: 2023/12/21 18:25:51 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_init_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long	get_actual_time(long start)
{
	struct timeval		end;
	long				time;
	long				actual;

	gettimeofday(&end, NULL);
	time = (end.tv_sec) * 1000000 + (end.tv_usec);
	actual = time - start;
	return (actual / 1000);
}

void	smart_sleep(long time)
{
	long	i;

	i = get_init_time();
	while (1)
	{
		if ((get_init_time() - i) >= time)
			break ;
		usleep(time / 2);
	}
}
