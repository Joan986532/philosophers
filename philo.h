/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:48:38 by jnauroy           #+#    #+#             */
/*   Updated: 2025/03/31 13:42:57 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft_philo/libft.h"

typedef struct s_philo
{
	int	numb_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	notepme;
}		t_philo;

int	ft_atoi_safe(char *nptr);
#endif
