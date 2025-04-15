/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:48:38 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/11 17:31:52 by jnauroy          ###   ########.fr       */
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
	int	n_phil;
	int	tt_die;
	int	tt_eat;
	int	tt_slp;
	int	nt_eat;
}		t_philo;

int	ft_atoi_philo(char *nptr);
int	main(int argc, char **argv);

#endif
