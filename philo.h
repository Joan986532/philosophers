/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:27:53 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/09 14:54:38 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft_philo/libft.h"

# define NC		"\e[0m"
# define YELLOW "\e[33m"
# define GREEN	"\e[32m"
# define RED	"\e[31m"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					n_phil;
	int					n_thread;
	int					tt_die;
	int					tt_eat;
	int					tt_slp;
	int					nt_eat;
	int					stop;
	int					lunches;
	unsigned long		start;
	t_philo				*philos;
	pthread_mutex_t		print;
	pthread_mutex_t		mutmeal;
	pthread_mutex_t		*forks;
}						t_data;

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				index;
	int				meals;
	t_data			*data;
	unsigned long	last_meal;
}					t_philo;

unsigned long	gettime_ms(void);
void			init_philos(t_data *data);
int				manager(t_data *data, int argc);
void			join_threads(pthread_t *th, int n_th);
void			*routine(void *arg);
int				create_threads(t_data *data, pthread_t *th);
int				ft_parsing(char **argv, t_data *data);
int				ft_atoi_philo(char *nptr);
int				print_messages(t_philo *philo, char *str);
int				print_messages_eating(t_philo *philo, char *str);

#endif
