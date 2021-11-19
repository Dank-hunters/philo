/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:33:38 by cguiot            #+#    #+#             */
/*   Updated: 2021/11/12 18:50:04 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	philo_death(t_philo *philo)
{	
	int	i;

	i = 0;
	while (!philo->rules->is_death && philo->rules->nb_meal != philo->rules->nb_phi)
	{
		i = 0;
		while (i < philo->rules->nb_phi)
		{
			pthread_mutex_lock(&philo->rules->eating);
			if (get_time() - philo[i].last_meal > philo->rules->ttk && philo->rules->nb_meal != philo->rules->nb_phi)
			{
				philo->rules->is_death = 1;
				printt(philo->rules, "is dead", i + 1);
				pthread_mutex_unlock(&philo->rules->eating);
				return ;
			}
			pthread_mutex_unlock(&philo->rules->eating);
			i++;
		}
	}
	//usleep(50);
}

int	main(int ac, char **av)
{
	t_rules	rules;
	int		i;

	i = 0;
	if (ac <= 4 || ac >= 7)
		return (0);
	else if (ac == 6 && av[5][0] == '0' && !av[5][1])
		return (0);
	init_struct(&rules, ac, av);
	philo_death(rules.philo);
	while (i < rules.nb_phi)
	{
		if (rules.philo->thread)
			pthread_join(rules.philo[i].thread, NULL);
		i++;
	}
	//il fau freeeeeee
	write(1, "lol\n", 3);
	return(0);

}

