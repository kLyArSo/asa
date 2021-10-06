#include "header.h"

void	set_philo_data(t_philo_data	*data
		, t_argv	*game_args, pthread_mutex_t	*fork)
{
	int	i;

	i = 0;
	while (i < game_args->number_of_philosophers)
	{
		data[i].philo_index = i;
		if (i == 0)
		{
			data[i].philo_fork_1 = i;
			data[i].philo_fork_2 = game_args->number_of_philosophers - 1;
		}
		else
		{
			data[i].philo_fork_1 = i;
			data[i].philo_fork_2 = i - 1;
		}
		data[i].meal_counter = 0;
		data[i].last_meal_timestamp = 0;
		data[i].next_meal_timestamp = data[i].last_meal_timestamp
			+ game_args->time_to_die;
		data[i].forks = fork;
		data[i].game_args = game_args;
		i++;
	}
}

pthread_mutex_t	*forks_init(t_argv	*game_args)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(game_args->number_of_forks * sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (NULL);
	while (i < game_args->number_of_forks)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
