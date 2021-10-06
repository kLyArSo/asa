#include "header.h"

long		ft_atoi(char *src)
{
	size_t			i;
	size_t			s;
	size_t			res;

	i = 0;
	res = 0;
	s = 1;
	while ((src[i] >= 9 && src[i] <= 13) || (src[i] == 32))
		i++;
	if (src[i] == '+')
		i++;
	else if (src[i] == '-')
	{
		s = -1;
		i++;
	}
	if (src[i] < 48 && src[i] > 57)
		return (0);
	else
		while ((src[i] >= 48) && (src[i] <= 57))
		{
			res = res * 10 + src[i] - '0';
			i++;
		}
	return (res * s);
}

t_argv      *fetch_args(int argc, char **argv)
{
    t_argv  *game_args;

    game_args = malloc(sizeof(t_argv));
    if (game_args == NULL)
        return (NULL);
    game_args->number_of_philosophers = ft_atoi(argv[1]);
    game_args->number_of_forks = game_args->number_of_philosophers;
    game_args->time_to_die = ft_atoi(argv[2]);
    game_args->time_to_eat = ft_atoi(argv[3]);
    game_args->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
    {
        game_args->last_arg_presence = LAST_ARG_PRESENT;
        game_args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    }
    return (game_args);
}

int     check_ints(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
    {
        i++;
        if (str[i] == '+' || str[i] == '-')
            return (ERROR_DETECTED);
    }
    while (str[i] != 0 && str[i] >= '0' && str[i] <= '9')
        i++;
    if (str[i] == 0)
        return (NO_ERRORS_DETECTED);
    else
        return (ERROR_DETECTED);
}

int     argv_error_handling(int argc, char **argv)
{
    int i;

    i = 1;
    if (argc != 5 && argc != 6)
    {
        printf("ERROR: NUMBER OF ARGS\n");
        return(ERROR_DETECTED);
    }
    while (argv[i] != NULL)
    {
        if (check_ints(argv[i]) == ERROR_DETECTED)
        {
            printf("ERROR: NON-INTEGER ARG(S)\n");
            return (ERROR_DETECTED);
        }
        else
            i++;
    }
    return (NO_ERRORS_DETECTED);
}

int     last_check(t_argv  *game_args)
{
    if (game_args->number_of_philosophers <= 0 || game_args->time_to_die < 0
     || game_args->time_to_eat < 0 || game_args->time_to_sleep < 0)
        return (ERROR_DETECTED);
    if (game_args->last_arg_presence == LAST_ARG_PRESENT)
    {
        if(game_args->number_of_times_each_philosopher_must_eat < 0)
            return (ERROR_DETECTED);
    }
    return (NO_ERRORS_DETECTED);
}