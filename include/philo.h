/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:32:43 by cguiot            #+#    #+#             */
/*   Updated: 2021/12/02 18:40:07 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo
{
	int				name;
	int				rf;
	int				lf;
	int				meal;
	int				fork;
	long long int	last_meal;
	pthread_t		thread;
	pthread_mutex_t	eating;
	struct s_rules	*rules;
}			t_philo;

typedef struct s_rules
{
	long long int	first_meal_time;
	int				nb_phi;
	int				ttk;
	int				tts;
	int				tte;
	int				max_meal;
	int				nb_meal;
	int				is_death;
	int				rdy;
	int				first;
	t_philo			*philo;	
	pthread_mutex_t	*forks;
	pthread_mutex_t	iswait;
}			t_rules;

void			ft_putnbr(long long int n);
void			init_struct(t_rules *rules, int ac, char **av);

void			printt(t_rules *rules, char *s, int id);
void			new_sleep(long long max);
long long int	get_time(void);
long long int	ft_atoit(const char *str, int pn);
void			*action(void	*t);

void			phi_say(t_rules *rules, char *str, int id);
#endif
