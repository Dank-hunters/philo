/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:33:38 by cguiot            #+#    #+#             */
/*   Updated: 2021/11/30 18:25:01 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put(char c)
{
		write(1, &c, 1);
}
void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	else
	{
		if (n < 0)
		{
			n = n * -1;
			write(1, "-", 1);
		}
		if (n >= 10)
			ft_putnbr(n / 10);
		put((n%10 + 48));
	}
	return ;
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

void printll(long long int i)
{
	if (i >= 10)
		printll(i/10);
	put((i % 10 + 48));
}

void	phi_say(t_rules *rules, char *str, int id)
{
	pthread_mutex_lock(&rules->iswait);
	//printll(get_time() - rules->first_meal_time);
	put(' ');
	ft_putnbr(id);
	put(' ');
	putst(str);
	put('\n');
//	(void)id;
//	(void)str;
	pthread_mutex_unlock(&rules->iswait);
}


void	eating(t_philo *philo)
{
	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(&philo->rules->forks[philo->rf]);
		phi_say(philo->rules, "has taken a fork", philo->name);
		pthread_mutex_lock(&philo->rules->forks[philo->lf]);
		phi_say(philo->rules, "has taken a fork", philo->name);
	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->lf]);
		phi_say(philo->rules, "has taken a fork", philo->name);
		if (philo->rules->nb_phi == 1)
			return ;
		pthread_mutex_lock(&philo->rules->forks[philo->rf]);
		phi_say(philo->rules, "has taken a fork", philo->name);
	}
	pthread_mutex_lock(&philo->eating);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->eating);
	phi_say(philo->rules, "is eating", philo->name);
	//usleep(philo->rules->tte);
	usleep(philo->rules->tte);
	pthread_mutex_unlock(&philo->rules->forks[philo->rf]);
	pthread_mutex_unlock(&philo->rules->forks[philo->lf]);	
}


void	*action(void	*t)
{
	t_philo *philo;

	philo = (t_philo *)t;
	while(philo->rules->rdy == 0)
		;
	while (philo->rules->is_death == 0)
	{
		eating(philo);
		philo->meal++;
		if (philo->rules->max_meal == philo->meal && philo->rules->nb_phi > 1)
		{
			philo->rules->nb_meal++;
		}
		if (philo->rules->nb_meal == philo->rules->nb_phi)//on check si ils ont tous manger ou pas , le cas echeant on arrete de toiurner sur cve thread et on ;aisse le check death si charger de leave 
			return(NULL);	
	phi_say(philo->rules, "is sleeping", philo->name);
	usleep(philo->rules->tts);
	// attendre philo->tts
	if (philo->rules->nb_meal == philo->rules->nb_phi || philo->rules->is_death == 1)
			return (NULL);	
	phi_say(philo->rules, "is thinking", philo->name);
	}
	return (NULL);
}	



void	philo_death(t_philo *philo)
{	
	int	i;

	i = 0;
	while (!philo->rules->is_death && philo->rules->nb_meal != philo->rules->nb_phi)
	{
		i = 0;
		while (i < philo->rules->nb_phi)
		{
			pthread_mutex_lock(&philo->eating);
			if (get_time() - philo[i].last_meal > philo->rules->ttk && philo->rules->nb_meal != philo->rules->nb_phi)
			{
				philo->rules->is_death = 1;
				dprintf(1, "%lli | philo :%i  | is dead", (get_time() - philo->rules->first_meal_time), philo->name);//printf l action "is dead"
				pthread_mutex_unlock(&philo->eating);
				return ;
			}
			pthread_mutex_unlock(&philo->eating);
			i++;
		}
	}
	usleep(50);
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
/*
int main()
{
	int i = 0;
	while(i < 150)
	{
		ft_putnbr(i++);
		dprintf(1, "\n");
	}	
	return(0);
}*/
