/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:22:42 by moabid            #+#    #+#             */
/*   Updated: 2022/08/03 23:36:05 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	threading(struct s_data *data)
{
	data->start_time = ft_gettime();
	if (threading_launch(data, data->philo) == false)
	{
		free(data->fork);
		free(data->philo);
		return (false);
	}
	francisco_is_watching(data, data->philo, 0);
	return (true);
}

bool	threading_launch(struct s_data *data, struct s_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(philo[i].philo_thread),
				NULL, life_cycle, &(philo[i])) != 0)
			ft_error(THREAD_ERR);
		pthread_mutex_lock(&(data->eat));
		philo[i].last_eating_time = ft_gettime();
		pthread_mutex_unlock(&(data->eat));
		i += 1;
	}
	return (true);
}

void	*life_cycle(void *philo_void)
{
	struct s_philo	*philo;
	struct s_data	*data;

	philo = (struct s_philo *) philo_void;
	data = philo->data;
	if ((philo->philo_id + 1) % 2 == 0)
		ft_usleep(data->time_to_die);
	while (1)
	{
		// pthread_mutex_lock(&(data->death));
		if (data->dead)
		{
			// pthread_mutex_unlock(&(data->death));
			return (NULL);
		}
		// pthread_mutex_unlock(&(data->death));
		philo_eat_cycle(data, philo);
		if (philo_meals_check(data, philo) == true || data->nb_philo == 1)
			return (NULL);
		philo_sleep(data, philo);
		philo_think(data, philo);
	}
	return (NULL);
}

void	francisco_is_watching(struct s_data *data, struct s_philo *philo, int i)
{
	while (1)
	{
		i = 0;
		while (i < data->nb_philo && !data->dead)
		{
			data->death_time = ft_gettime() - philo[i].last_eating_time;
			if (data->death_time > data->time_to_die)
			{
				pthread_mutex_lock(&(data->eat));
				print_state(data, philo[i].philo_id, DEATH);
				pthread_mutex_lock(&(data->death));
				data->dead = true;
				pthread_mutex_unlock(&(data->death));
				pthread_mutex_unlock(&(data->eat));
			}
			i++;
		}
		if (data->dead)
			return ;
		if (data->nb_of_meal != -1
			&& ft_eat_enough(data, philo) == data->nb_philo)
			break ;
	}
}
