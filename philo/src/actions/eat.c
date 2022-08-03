/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:25:05 by moabid            #+#    #+#             */
/*   Updated: 2022/08/03 23:20:18 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_cycle(struct s_data *data, struct s_philo *philo)
{
	philo_take_forks(data, philo);
	philo_eat(data, philo);
	philo_leave_forks(data, philo);
}

void	philo_take_forks(struct s_data *data, struct s_philo *philo)
{
	if (philo->r_fork < philo->l_fork)
		ft_swap(&(philo->r_fork), &(philo->l_fork));
	pthread_mutex_lock(&(data->fork[philo->r_fork]));
	print_state(data, philo->philo_id, FORK);
	if (data->nb_philo == 1)
	{
		pthread_mutex_unlock(&(data->fork[philo->r_fork]));
		return ;
	}
	pthread_mutex_lock(&(data->fork[philo->l_fork]));
	print_state(data, philo->philo_id, FORK);
}

void	philo_eat(struct s_data *data, struct s_philo *philo)
{
	pthread_mutex_lock(&(data->eat));
	print_state(data, philo->philo_id, EAT);
	philo->last_eating_time = ft_gettime();
	pthread_mutex_unlock(&(data->eat));
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&(data->eat));
	philo->meal_eaten += 1;
	pthread_mutex_unlock(&(data->eat));
}

void	philo_leave_forks(struct s_data *data, struct s_philo *philo)
{
	pthread_mutex_unlock(&(data->fork[philo->l_fork]));
	pthread_mutex_unlock(&(data->fork[philo->r_fork]));
}
