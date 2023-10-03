/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:19:30 by vcacador          #+#    #+#             */
/*   Updated: 2023/10/03 17:26:26 by vcacador         ###   ########.fr       */
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

int	eat_help(int i)
{
	int	j;

	if (check_dead(i))
		return (1);
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
	philo()[0][i].last_meal = time_now();
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
	print_stuff(philo()[0][i].id, "is thinking");
	if (check_dead(i))
		return (1);
	if (utils()->n_f % 2 != 0)
	{
		if (((philo()[0][i].last_meal - time_now()) + \
			(uint64_t)utils()->tte) > (uint64_t)utils()->ttd && \
				(((uint64_t)utils()->tte) * 3 > (uint64_t)utils()->ttd))
		{
			if (sleep_op((uint64_t)utils()->ttd - time_now() + 5, i))
				return (1);
		}
	}
	else
	{
		if (((philo()[0][i].last_meal - time_now()) + \
			(uint64_t)utils()->tte) > (uint64_t)utils()->ttd && \
				(((uint64_t)utils()->tte) * 2 > (uint64_t)utils()->ttd))
		{
			if (sleep_op((uint64_t)utils()->ttd - time_now() + 5, i))
				return (1);
		}
	}
	return (0);
}
