/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:37:18 by vcacador          #+#    #+#             */
/*   Updated: 2023/10/03 17:18:43 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int			id;
	int			think;
	int			eat_t;
	uint64_t	last_meal;
	int			sleep;
	pthread_t	thread;

}		t_philo;

typedef struct s_fork
{
	int					id;
	int					forks;
	pthread_mutex_t		fork;
}		t_fork;

typedef struct s_utils
{
	int					n_f;
	int					ttd;
	int					tte;
	int					tts;
	int					tfme;
	uint64_t			start;
	pthread_mutex_t		dead;
	int					dead2;
	pthread_mutex_t		write;

}		t_utils;

t_utils		*utils(void);
t_philo		**philo(void);
t_fork		**forks(void);
void		make_structs(void);
void		print_stuff(int id, char *str);
uint64_t	get_time(void);
int			xonar(int i);
int			eat(int i);
int			think(int i);
uint64_t	time_now(void);
int			sleep_op(__useconds_t ms, int id);
int			check_dead(int id);
void		free_all(void);
int			is_num(char *str);
int			eat_help_last_philo(int i, int j);
int			eat_help_philo(int i, int j);
void		mutex_unlock(int first, int second);
void		mutex_unlock2(int i, int j);

#endif