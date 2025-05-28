/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:13:43 by jnauroy           #+#    #+#             */
/*   Updated: 2025/05/27 18:00:25 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) == -1)
			return (1);
		data->philos[i].meals = 0;
		data->philos[i].tt_thk = 0;
		data->philos[i].tt_thk = 0;
		data->philos[i].index = i + 1;
		data->philos[i].last_meal = gettime_ms();
		data->philos[i].data = data;
		data->philos[i].l_fork = &data->forks[i];
		if (i + 1 == data->n_phil)
			data->philos[i].r_fork = &data->forks[0];
		else
			data->philos[i].r_fork = &data->forks[i + 1];
		i++;
	}
	return (0);
}

unsigned long	gettime_ms(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

int	ft_parsing(char **argv, t_data *data)
{
	data->stop = 0;
	data->lunches = 0;
	if (data_argv(argv, data) == -1)
		return (-1);
	data->tt_slp = ft_atoi_philo(argv[4]);
	if (data->tt_slp == -1)
		return (-1);
	if (argv[5] != NULL)
	{
		data->nt_eat = ft_atoi_philo(argv[5]);
		if (data->nt_eat < 1)
			return (-1);
	}
	else
		data->nt_eat = -1;
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
