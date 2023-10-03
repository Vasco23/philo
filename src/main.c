/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:44:47 by vcacador          #+#    #+#             */
/*   Updated: 2023/10/03 17:21:04 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	int		sinal;
	long	result;

	i = 0;
	sinal = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sinal = -sinal;
		i++;
		if (nptr[i] == '-' || nptr[i] == '+')
			return (0);
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result * sinal >= -2147483648 && result * sinal <= 2147483647)
			result = (result * 10) + (nptr[i++] - '0');
		else
			return (-2147483656);
	}
	return (result * sinal);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		if (is_num(av[i]))
			return (1);
	if (ac < 5 || ac > 6)
		return (1);
	utils()->n_f = ft_atoi(av[1]);
	utils()->ttd = ft_atoi(av[2]);
	utils()->tte = ft_atoi(av[3]);
	utils()->tts = ft_atoi(av[4]);
	if (ac == 6)
	{
		utils()->tfme = ft_atoi(av[5]);
		if (utils()->tfme < 0)
			return (1);
	}
	else
		utils()->tfme = INT_MAX;
	if (utils()->n_f < 0 || utils()->ttd < 0 || \
		utils()->tte < 0 || utils()->tts < 0)
		return (1);
	return (0);
}

void	*f_thread_runs(void *ola)
{
	int	*y;
	int	i;

	y = (int *)ola;
	i = *y;
	philo()[0][i].think = 0;
	philo()[0][i].last_meal = time_now();
	philo()[0][i].eat_t = 0;
	if (i % 2 == 0)
	{
		if (i + 1 == utils()->n_f)
			think(i);
		if (eat(i))
			return (NULL);
	}
	if (i % 2 != 0)
	{
		if (think(i))
			return (NULL);
		sleep_op(utils()->tte, i);
	}
	while (philo()[0][i].eat_t < utils()->tfme && !check_dead(i))
		if (eat(i))
			return (NULL);
	return (NULL);
}

void	c_threads(void)
{
	int	i;

	i = -1;
	while (++i < utils()->n_f)
		pthread_create(&philo()[0][i].thread, NULL, \
			&f_thread_runs, &philo()[0][i].id);
	i = -1;
	while (++i < utils()->n_f)
		pthread_join(philo()[0][i].thread, NULL);
	i = -1;
	while (++i < utils()->n_f)
	{
		pthread_mutex_destroy(&forks()[0][i].fork);
	}
	pthread_mutex_destroy(&utils()->write);
	pthread_mutex_destroy(&utils()->dead);
}

int	main(int ac, char **av)
{
	if (check_args(ac, av) == 1)
		return (1);
	make_structs();
	utils()->start = get_time();
	c_threads();
	free_all();
	return (0);
}
