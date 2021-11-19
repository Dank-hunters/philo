/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:12:07 by cguiot            #+#    #+#             */
/*   Updated: 2021/11/12 18:50:05 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	init_phi(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_phi)
	{
		rules->philo[i].name = i + 1;
		rules->philo[i].rf = i;
		if (i == 0)
			rules->philo[i].lf = rules->nb_phi - 1;
		else
			rules->philo[i].lf = i - 1;
		rules->philo[i].rules = rules;
		rules->philo[i].meal = 0;
		rules->philo[i].last_meal = get_time();
	//	pthread_create(&rules->philo[i].thread, NULL, /*une fonction*/, &rules->philo[i]);
		i++;
	}
}

void	last_meal(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_phi)
	{
		rules->philo[i].last_meal = rules->lm_time;
		i++;	
	}
}

void	init_fork(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_phi)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
}


void	init_struct(t_rules *rules, int ac, char **av)
{
	rules->nb_phi = ft_atoit(av[1], 1);
	rules->ttk = ft_atoit(av[2], 1);
	rules->tte = ft_atoit(av[3], 1);
	rules->tts = ft_atoit(av[4], 1);
	rules->nb_meal = 0;
	if (ac == 6)
		rules->nb_meal = ft_atoit(av[5], 1);
	dprintf(1, "ttk : %i\ntts : %i\n tte : %i\n nb phi : %i\n,\
		   	nb meal : %i\n", rules->ttk, rules->tts, rules->tte, \
			rules->nb_phi, rules->nb_meal);
	rules->is_death = 0;
	rules->nb_meal = 0;
	//init mutex pour state et eating
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_phi);
	init_fork(rules);
	init_phi(rules);
	rules->lm_time = get_time();
	rules->rdy = 1;
	last_meal(rules);
}
