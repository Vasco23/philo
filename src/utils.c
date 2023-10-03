/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:30:52 by vcacador          #+#    #+#             */
/*   Updated: 2023/10/03 17:22:08 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

uint64_t	time_now(void)
{
	return ((get_time() - utils()->start));
}

int	sleep_op(__useconds_t ms, int id)
{
	uint64_t	time;

	time = get_time();
	while (get_time() - time < ms)
	{
		usleep(ms / 10);
		if (check_dead(id))
			return (1);
	}
	return (0);
}

int	check_dead(int id)
{
	pthread_mutex_lock(&utils()->dead);
	if ((time_now() - philo()[0][id].last_meal) > \
		(uint64_t)utils()->ttd || utils()->dead2 == 1)
	{
		if (utils()->dead2 == 1)
		{
			pthread_mutex_unlock(&utils()->dead);
			return (1);
		}
		if (utils()->dead2 == 0)
		{
			printf("%ld %d died\n", time_now(), id + 1);
			utils()->dead2 = 1;
		}
		pthread_mutex_unlock(&utils()->dead);
		return (1);
	}
	pthread_mutex_unlock(&utils()->dead);
	return (0);
}

void	print_stuff(int id, char *str)
{
	int	i;

	i = id + 1;
	pthread_mutex_lock(&utils()->dead);
	if (utils()->dead2)
	{
		pthread_mutex_unlock(&utils()->dead);
		return ;
	}
	pthread_mutex_lock(&utils()->write);
	printf("%lu %d %s\n", time_now(), i, str);
	pthread_mutex_unlock(&utils()->write);
	pthread_mutex_unlock(&utils()->dead);
}
