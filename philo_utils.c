/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:40:51 by jnauroy           #+#    #+#             */
/*   Updated: 2025/03/31 11:11:47 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_safe(char *nptr)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i] != '\0')
	{
		if (nb > INT_MAX / 10)
			return (-1);
		nb *= 10;
		if (nb > INT_MAX - (nptr[i] - 48))
			return (-1);
		nb += nptr[i] - 48;
		i++;
	}
	return (nb);
}
