/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:47:17 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/25 18:15:26 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_parsing(char **argv, t_philo *data)
{
	data->actual = 1;
	data->stop = 0;
	data->lunches = 0;
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
	t_philo	*data;
	int		i;
	int		num;	

	data = (t_philo *)arg;
	i = 0;
	pthread_mutex_lock(data->mutex);
	num = data->actual;
	printf("%sPhilo %d%s\n", GREEN, num, NC);
	pthread_mutex_unlock(data->mutex);
	while (i < data->nt_eat)
	{
		printf("%d has taken a fork\n", num);
		printf("%d has taken a fork\n", num);
		printf("%d is eating\n", num);
		printf("%d is sleeping\n", num);
		printf("%d is thinking\n", num);
		printf("%d died\n", num);
		printf("%sLunches: [ %d ]%s\n", YELLOW, data->lunches, NC);
		data->lunches++;
		i++;
		usleep(1);
	}
	return (0);
}

void	*routine_manager(void *arg)
{
	(void)arg;
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
	th = malloc(sizeof(pthread_t) * data.n_phil + 1);
	if (!th)
		return (1);
	data.mutex = malloc(sizeof(pthread_mutex_t) * data.n_phil);
	if (!data.mutex)
		return (1);
	pthread_mutex_init(data.mutex, NULL);
	while (data.actual <= data.n_phil + 1)
	{
		if (data.actual != data.n_phil + 1)
		{
			if (pthread_create(&th[data.actual - 1], NULL, &routine, &data) != 0)
				return (1);
			usleep(1000);
			printf("Thread %d has started\n", data.actual);
		}
		else
		{
			if (pthread_create(th + (data.actual - 1), NULL, &routine_manager, &data) != 0)
				return (1);
			printf("%sThread manager %d has started%s\n", GREEN, data.actual + 1, NC);
		}
		data.actual++;
	}
	data.actual = 1;
	usleep(500);
	while (data.actual <= data.n_phil + 1)
	{
		if (pthread_join(th[data.actual - 1], NULL) != 0)
			return (1);
		printf("Thread %d has stopped\n", data.actual);
		data.actual++;
	}
	printf("%sLunch [%d]%s\n", YELLOW, data.lunches, NC);
	usleep(500);
	printf("Number of philosophers: %s%d%s\n", YELLOW, data.n_phil, NC);
	printf("N of times each philosophers must eat: %s%d%s\n", YELLOW, data.nt_eat, NC);
	printf("Total lunches: %s%d%s\n", YELLOW, data.lunches, NC);
	pthread_mutex_destroy(data.mutex);
	return (0);
}
