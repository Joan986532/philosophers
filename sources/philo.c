/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:47:17 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/21 14:30:52 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_parsing(char **argv, t_philo *data)
{
	data->n_phil = ft_atoi_philo(argv[1]);
	if (data->n_phil == -1)
		return (-1);
	data->tt_die = ft_atoi_philo(argv[2]);
	if (data->tt_die == -1)
		return (-1);
	data->tt_eat = ft_atoi_philo(argv[3]);
	if (data->tt_eat == -1)
		return (-1);
	data->tt_slp = ft_atoi_philo(argv[4]);
	if (data->tt_slp == -1)
		return (-1);
	data->nt_eat = ft_atoi_philo(argv[5]);
	if (data->nt_eat == -1)
		return (-1);
	return (0);
}

void	*routine_eat(void *arg)
{
	pthread_mutex_t	mutex;
	int				i;

	i = *(int *)arg;
	printf("philo %d is eating\n", i);
	return (0);
}

void	*routine_sleep(void *arg)
{
	int	i;

	i = *(int *)arg;
	printf("philo %d is sleeping\n", i);
	return (0);
}

void	*routine_die(void *arg)
{
	int	i;

	i = *(int *)arg;
	printf("philo %d is dying\n", i);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		*th;
	t_philo			data;
	int				i;

	i = 0;
	if (argc != 6)
		return (1);
	if (ft_parsing(argv, &data) == -1)
		return (1);
	th = malloc(sizeof(int) * data.n_phil);
	printf("times each philosophers must eat: %d\n", data.nt_eat);
	while (i < data.nt_eat)
	{
		if (pthread_create(&th[i], NULL, &routine_eat, &i) != 0)
			return (1);
		if (pthread_create(&th[i], NULL, &routine_sleep, &i) != 0)
			return (1);
		if (pthread_create(&th[i], NULL, &routine_die, &i) != 0)
			return (1);
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
