/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:48:38 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/25 18:04:09 by jnauroy          ###   ########.fr       */
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
	pthread_t			thread;
	int					n_phil;
	int					tt_die;
	int					tt_eat;
	int					tt_slp;
	int					nt_eat;
	int					actual;
	int					stop;
	int					lunches;
	pthread_mutex_t		*mutex;
}						t_philo;

int	ft_atoi_philo(char *nptr);
int	main(int argc, char **argv);

#endif
