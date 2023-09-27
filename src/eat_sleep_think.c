/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:19:30 by vcacador          #+#    #+#             */
/*   Updated: 2023/09/20 16:25:27 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	xonar(int i)
{
	if (check_dead(i))
		return (1);
	print_stuff(philo()[0][i].id, "is sleeping");
	philo()[0][i].sleep += utils()->tts;
	philo()[0][i].sleep = 1;
	if (sleep_op(utils()->tts, i))
		return (1);
	return (0);
}

int eat_help_last_philo(int i, int j)
{
	check_dead(i);
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

int	eat_help(int i)
{
	int	j;

	philo()[0][i].last_meal = time_now();
	if (i + 1 == utils()->n_f)
		j = 0;
	else
		j = i + 1;
	if (j == 0)
	{
		if (eat_help_last_philo(i, j))
			return (1);
	}
	else
		if (eat_help_philo(i, j))
			return (1);
	philo()[0][i].eat_t++;
	if (sleep_op(utils()->tte, i))
	{
		mutex_unlock2(i, j);
		return (1);
	}
	mutex_unlock2(i, j);
	return (0);
}

int	eat(int i)
{
	if (check_dead(i))
		return (1);
	if (eat_help(i))
		return (1);
	if (xonar(i))
		return (1);
	if (think(i))
		return (1);
	return (0);
}

int	think(int i)
{
	if (check_dead(i))
		return (1);
	print_stuff(philo()[0][i].id, "is thinking");
	return (0);
}

