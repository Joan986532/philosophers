/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:05:31 by jnauroy           #+#    #+#             */
/*   Updated: 2025/04/28 17:35:32 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_messages(t_data *data)
{
	printf("Number of philosophers: %s%d%s\n", YELLOW, data->n_phil, NC);
	printf("N of times each philosophers must eat: %s%d%s\n",
		YELLOW, data->nt_eat, NC);
	printf("Total lunches: %s%d%s\n", YELLOW, data->lunches, NC);
}
