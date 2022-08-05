/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_destory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:19:28 by moabid            #+#    #+#             */
/*   Updated: 2022/08/05 17:16:46 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_threads_destory(struct s_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].philo_thread, NULL);
		i++;
	}
}

void	data_mutex_destory(struct s_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->log);
	pthread_mutex_destroy(&data->wait);
}

void	data_destroy(struct s_data *data)
{
	data_threads_destory(data);
	data_mutex_destory(data);
	free(data->fork);
	free(data->philo);
}
