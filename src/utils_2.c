/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:37:55 by vcacador          #+#    #+#             */
/*   Updated: 2023/09/25 15:14:20 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(void)
{
	if (*philo())
		free(*philo());
}

void	free_forks(void)
{
	if (*forks())
		free(*forks());
}

void	free_all(void)
{
	free_philo();
	free_forks();
}

int	is_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

