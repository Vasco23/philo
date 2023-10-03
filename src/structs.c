/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:03:12 by vcacador          #+#    #+#             */
/*   Updated: 2023/10/03 17:19:44 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_utils	*utils(void)
{
	static t_utils	utils;

	return (&utils);
}

t_philo	**philo(void)
{
	static t_philo	*philo;

	return (&philo);
}

t_fork	**forks(void)
{
	static t_fork	*fork;

	return (&fork);
}

void	make_structs(void)
{
	int	i;

	i = -1;
	pthread_mutex_init(&utils()->write, NULL);
	pthread_mutex_init(&utils()->dead, NULL);
	*philo() = malloc(sizeof(t_philo) * utils()->n_f);
	*forks() = malloc(sizeof(t_fork) * utils()->n_f);
	while (++i < utils()->n_f)
	{
		pthread_mutex_init(&forks()[0][i].fork, NULL);
		philo()[0][i].id = i;
		forks()[0][i].id = i;
	}
}
