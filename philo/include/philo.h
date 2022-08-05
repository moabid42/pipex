/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 09:27:57 by athirion          #+#    #+#             */
/*   Updated: 2022/08/05 17:15:51 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define THREAD_ERR			"\033[31mError:\033[0m Thread error\n"
# define MALLOC_ERR			"\033[31mError:\033[0m Malloc error\n"
# define ARGUMENT_ERROR		"\033[31mError:\033[0m Please feed me valid numbers\n"
# define NEGATIVE_ERROR		"\033[31mError:\033[0m Please feed me \
								positive numbers only\n"
# define OVERFLOW_ERROR		"\033[31mError:\033[0m Please don't overflow me\n"
# define FOOD_ERROR 		"\033[31mError:\033[0m Please feed me at least once\n"
# define SYNTAX_ERROR		"\033[31mError:\033[0m ./philo num_p time_d time_e time_s \
								[philo_eat_num]\n"
# define DATA_ERROR			"\033[31mError:\033[0m Initialization error.\n"
# define THREADING_ERROR	"\033[31mError:\033[0m Thread error.\n"

# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define FORK	"has taken a fork"
# define DEATH	"died"

//////////////////////////////////////////////////////////////////
//					[    DATA ST								//
//					       	    RUCTES  ]					    //
//////////////////////////////////////////////////////////////////

typedef enum e_limits{
	MAX = 2147483647,
	MIN = -2147483648
}	t_limits;

struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meal;
	bool			created;
	bool			dead;

	long long		start_time;
	long long		death_time;

	pthread_mutex_t	*fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	death;
	pthread_mutex_t	log;
	pthread_mutex_t wait;

	struct s_philo	*philo;
};

struct s_philo
{
	int					l_fork;
	int					r_fork;
	int					meal_eaten;
	int					philo_id;

	long long			last_eating_time;

	pthread_t			philo_thread;
	struct s_data		*data;

};

//////////////////////////////////////////////////////////////////
//						[  ACT									//
//					       	  IONS  ]						    //
//////////////////////////////////////////////////////////////////

void		philo_sleep(struct s_data *data, struct s_philo *philo);
void		philo_think(struct s_data *data, struct s_philo *philo);		
void		philo_eat_cycle(struct s_data *data, struct s_philo *philo);
void		philo_take_forks(struct s_data *data, struct s_philo *philo);
void		philo_eat(struct s_data *data, struct s_philo *philo);
void		philo_leave_forks(struct s_data *data, struct s_philo *philo);

//////////////////////////////////////////////////////////////////
//							[  CO								//
//					       	 	 RE  ]							//
//////////////////////////////////////////////////////////////////

void		data_threads_destory(struct s_data *data);
void		data_mutex_destory(struct s_data *data);
void		data_destroy(struct s_data *data);

void		data_create(struct s_data *data, int ac, char **av);
bool		data_init(struct s_data *data, int ac, char **av);
bool		mutex_init(struct s_data *data);
bool		threads_init(struct s_data *data);
void		philo_init(struct s_data *data, struct s_philo *philo);

bool		threading(struct s_data *data);
bool		threading_launch(struct s_data *data, struct s_philo *philo);
void		*life_cycle(void *philo_void);
void		francisco_is_watching(struct s_data *data, \
							struct s_philo *philo, int i);

//////////////////////////////////////////////////////////////////
//							[  UTI								//
//					       	 	  LS  ]							//
//////////////////////////////////////////////////////////////////

bool		philo_meals_check(struct s_data *data, struct s_philo *philo);
int			ft_eat_enough(struct s_data *data, struct s_philo *philo);

void		print_state(struct s_data *data, int id, char *action);
long long	ft_gettime(void);
void		ft_check_time(int time_to, struct s_data *data);

void		data_sanitize(int ac, char **av);

int			ft_strlen(const char *str);
void		ft_swap(int *a, int *b);
void		ft_error(char *error);
void		*ft_malloc(size_t size);
void		ft_usleep(long int time_in_ms);
void		smart_sleep(long long time, struct s_data *data);

int			ft_atoi(const char *str);

#endif
