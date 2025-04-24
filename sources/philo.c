/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:47:17 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/24 20:23:01 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_parsing(char **argv, t_philo *data)
{
	data->actual = 0;
	data->stop = 0;
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

void	*routine(void *arg)
{
	t_philo			*data;
	int				lunch;

	lunch = 0;
	data = (t_philo *)arg;
	while (lunch < data->nt_eat && data->stop == 0)
	{
		printf("%d has taken a fork\n", data->actual);
		printf("%d is sleeping\n", data->actual);
		printf("%d is eating\n", data->actual);
		printf("%d is thinking\n", data->actual);
		printf("%d died\n", data->actual);
		lunch++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		*th;
	t_philo			data;

	if (argc != 6)
		return (1);
	if (ft_parsing(argv, &data) == -1)
		return (1);
	th = malloc(sizeof(int) * data.n_phil + 1); //+ 1 for control thread
	pthread_mutex_init(&data.mutex, NULL);
	printf("times each philosophers must eat: %d\n", data.nt_eat);
	while (data.actual < data.n_phil)
	{
		if (pthread_create(&th[data.actual], NULL, &routine, &data) != 0)
		{
			free(th);
			return (1);
		}
		data.actual++;
	}
	while (data.actual > 0)
	{
		if (pthread_join(th[data.actual], NULL) != 0)
		{
			free(th);
			return (1);
		}
		data.actual--;
	}
	pthread_mutex_destroy(&data.mutex);
	return (0);
}
