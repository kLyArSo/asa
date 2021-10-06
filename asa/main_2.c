#include "header.h"

int	un_init_forks(t_philo_data	*philos_data, t_argv	*game_args
			, pthread_t	*philosophers)
{
	pthread_mutex_destroy(&g_lock_1);
	free(philos_data);
	free(game_args);
	free(philosophers);
	return (ERROR_DETECTED);
}

void	detach(t_philo_data	*philos_data, pthread_t	*philosophers)
{
	int	i;

	i = 0;
	while (i < philos_data->game_args->number_of_philosophers)
	{
		pthread_detach(philosophers[i]);
		i++;
	}
}

void	destroy(t_philo_data	*philos_data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&g_lock_1);
	while (i < philos_data->game_args->number_of_forks)
	{
		pthread_mutex_destroy(&philos_data->forks[i]);
		i++;
	}
}

int	infinite_loop(t_argv	*game_args, pthread_t	*philosophers
		, t_philo_data	*philos_data, t_checkers	*check)
{
	while (1)
	{
		if ((g_notification == MIN_MEAL_REACHED
				&& game_args->last_arg_presence == 1)
			|| g_notification == PHILO_DEATH)
		{
			if (philos_data->game_args->last_arg_presence == 1)
				pthread_detach(check->min_meal);
			pthread_detach(check->death);
			detach(philos_data, philosophers);
			destroy(philos_data);
			free(game_args);
			free(philosophers);
			free(philos_data->forks);
			free(philos_data);
			free(check);
			return (1);
		}
	}
}

int	last_three(t_argv	*game_args, pthread_t	*philosophers
, t_philo_data	*philos_data, t_checkers	*check)
{
	check = malloc(sizeof(t_checkers));
	if (check == NULL)
		return (game_args_error());
	deploy_philosophers(game_args, philosophers, philos_data);
	checker_wave_deployment(philos_data, &check->min_meal, &check->death);
	infinite_loop(game_args, philosophers, philos_data, check);
	return (0);
}
