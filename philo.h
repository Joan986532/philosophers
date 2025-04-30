/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:48:38 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/28 18:19:50 by jnauroy          ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_philo;

typedef struct s_data
{
	pthread_t			thread;
	int					n_phil;
	int					tt_die;
	int					tt_eat;
	int					tt_slp;
	int					nt_eat;
	int					actual;
	int					stop;
	int					lunches;
	int					dead;
	pthread_mutex_t		*forks;
}						t_data;

void	ft_free_philo(t_philo **philo, int limit);
void	*routine_manager(void *arg);
void	join_threads(t_data *data, pthread_t *th);
void	*routine(void *arg);
void	create_threads(t_data *data, pthread_t *th);
int		ft_parsing(char **argv, t_data *data);
int		ft_atoi_philo(char *nptr);
void	print_messages(t_data *data);

#endif
