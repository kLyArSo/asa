#include "header.h"

ssize_t	get_current_time_micro_seconds(void)
{
	struct timeval	current_time;
	ssize_t			time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 * 1000 + current_time.tv_usec;
	return (time);
}

int	game_args_error(void)
{
	printf("ERROR : MALLOC\n");
	return (ERROR_DETECTED);
}

int	invalid_value_error(t_argv	*game_args)
{
	free(game_args);
	printf("ERROR : INVALID VALUE\n");
	return (ERROR_DETECTED);
}

int	philo_malloc_err(t_argv	*game_args)
{
	free(game_args);
	return (ERROR_DETECTED);
}

int	philos_data_malloc_err(t_argv	*game_args, pthread_t	*philosophers)
{
	free(game_args);
	free(philosophers);
	return (ERROR_DETECTED);
}
