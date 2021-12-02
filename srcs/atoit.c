/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguiot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:42:34 by cguiot            #+#    #+#             */
/*   Updated: 2021/12/02 18:39:42 by cguiot           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr(long long int n)
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
		put((n % 10 + 48));
	}
	return ;
}

void	test(int nb, int pn)
{
	if ((pn < 0) || ((nb * pn) > 2147483647 || (nb * pn) < -2147483648))
	{
		exit(0);
	}
}

static int	check(int tmp, long int nb, long int pn)
{
	if ((nb < tmp) && (pn == -1))
		return (0);
	else if (nb < tmp && pn == 1)
		return (-1);
	return (1);
}

long long int	ft_atoit(const char *str, int pn)
{
	long long int	nb;
	long int		tmp;

	tmp = 0;
	nb = 0;
	while ((*str == ' ') || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			pn = pn * -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		nb = (nb * 10) + *str++ - 48;
		if (check(tmp, nb, pn) == -1)
			return (-1);
		if (check(tmp, nb, pn) == 0)
			return (0);
		tmp = nb;
	}
	test(nb, pn);
	return ((int)(nb * pn));
}
