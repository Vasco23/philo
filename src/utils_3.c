/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:41:59 by vcacador          #+#    #+#             */
/*   Updated: 2023/10/01 15:12:10 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_help_last_philo(int i, int j)
{
	if (check_dead(i))
		return (1);
	pthread_mutex_lock(&forks()[0][j].fork);
	print_stuff(philo()[0][i].id, "has taken a fork");
	while (utils()->n_f == 1)
	{
		if (check_dead(i))
		{
			pthread_mutex_unlock(&forks()[0][j].fork);
			return (1);
		}
	}
	pthread_mutex_lock(&forks()[0][i].fork);
	print_stuff(philo()[0][i].id, "has taken a fork");
	print_stuff(philo()[0][i].id, "is eating");
	return (0);
}

int	eat_help_philo(int i, int j)
{
    if (check_dead(i))
		return (1);
	pthread_mutex_lock(&forks()[0][i].fork);
	print_stuff(philo()[0][i].id, "has taken a fork");
	while (utils()->n_f == 1)
	{
		if (check_dead(i))
		{
			pthread_mutex_unlock(&forks()[0][i].fork);
			return (1);
		}
	}
	pthread_mutex_lock(&forks()[0][j].fork);
	print_stuff(philo()[0][i].id, "has taken a fork");
	print_stuff(philo()[0][i].id, "is eating");
	return (0);
}

void	mutex_unlock(int first, int second)
{
	pthread_mutex_unlock(&forks()[0][first].fork);
	pthread_mutex_unlock(&forks()[0][second].fork);
}

void	mutex_unlock2(int i, int j)
{
	if (j == 0)
		mutex_unlock(i, j);
	else
		mutex_unlock(j, i);
}
