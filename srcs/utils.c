/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:15:48 by cguiot            #+#    #+#             */
/*   Updated: 2021/12/02 18:40:27 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

void	new_sleep(long long max)
{
	long long	time;

	time = get_time();
	while (get_time() - time < max)
		usleep(50);
}

void	put(char c)
{
	write(1, &c, 1);
}

void	putst(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		put(str[i]);
		i++;
	}
}

void	phi_say(t_rules *rules, char *str, int id)
{
	if (rules->first == 0)
	{
		if (rules->is_death == 1)
			rules->first = 1;
		pthread_mutex_lock(&rules->iswait);
		ft_putnbr(get_time() - rules->first_meal_time);
		put(' ');
		ft_putnbr(id);
		put(' ');
		putst(str);
		put('\n');
		pthread_mutex_unlock(&rules->iswait);
	}
}
