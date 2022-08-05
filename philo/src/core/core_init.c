/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:18:57 by moabid            #+#    #+#             */
/*   Updated: 2022/08/05 17:16:24 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_create(struct s_data *data, int ac, char **av)
{
	if (data_init(data, ac, av))
		if (mutex_init(data))
			if (threads_init(data))
				return ;
	ft_error(DATA_ERROR);
}

bool	data_init(struct s_data *data, int ac, char **av)
{
	data_sanitize(ac, av);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->dead = false;
	data->created = false;
	data->start_time = 0;
	if (ac == 6)
		data->nb_of_meal = ft_atoi(av[5]);
	else
		data->nb_of_meal = -1;
	return (true);
}

bool	mutex_init(struct s_data *data)
{
	int	i;

	i = 0;
	data->fork = (pthread_mutex_t *)
		ft_malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (false);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL) != 0)
			return (false);
		i ++;
	}
	if (pthread_mutex_init(&(data->eat), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(data->death), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(data->log), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(data->wait), NULL) != 0)
		return (false);
	return (true);
}

bool	threads_init(struct s_data *data)
{
	struct s_philo	*philo;

	philo = ft_malloc(sizeof(struct s_philo) * data->nb_philo);
	if (!philo)
	{
		free(data->fork);
		ft_error(MALLOC_ERR);
	}
	data->philo = philo;
	philo_init(data, philo);
	return (true);
}

void	philo_init(struct s_data *data, struct s_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].last_eating_time = 0;
		philo[i].l_fork = i;
		philo[i].r_fork = (i + 1) % data->nb_philo;
		philo[i].philo_id = i;
		philo[i].meal_eaten = 0;
		i ++;
	}
}
