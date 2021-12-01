/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:15:48 by cguiot            #+#    #+#             */
/*   Updated: 2021/12/01 18:15:27 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long 	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

void	new_sleep(long long max)
{
	long long time;

	time = get_time();
	while (get_time() - time < max)
		usleep(50);
}

/*void	printt(t_rules *rules, char *s, int id)
{
	pthread_mutex_lock(&rules->iswait);
	if (rules->nb_meal != rules->nb_phi && !rules->is_death)
	{
		printf("%lli ", get_time() - rules->lm_time);
		printf("%d %s\n", id, s);
	}
	else if (s[3] == 'd')
	{
		printf("%lli ", get_time() - rules->lm_time);
		printf("%d %s\n", id, s);
	}
	pthread_mutex_unlock(&rules->iswait);
}*/
