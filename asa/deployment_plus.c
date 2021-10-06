#include "header.h"

void    *entry_point(void   *ptr)
{
    t_philo_data *data;

    while (1)
    {
        data = (t_philo_data *)ptr;
        pthread_mutex_lock(&data->forks[data->philo_fork_1]);
        print_status("has taken a fork", data->philo_index);
        pthread_mutex_lock(&data->forks[data->philo_fork_2]);
        print_status("has taken a fork", data->philo_index);
        
        data->meal_counter++;
        data->last_meal_timestamp = (get_current_time_micro_seconds() - g_start_time) / 1000;
        data->next_meal_timestamp = data->last_meal_timestamp + data->game_args->time_to_die;
        print_status("is eating", data->philo_index);
        my_sleep(data->game_args->time_to_eat * 1000);

        pthread_mutex_unlock(&data->forks[data->philo_fork_1]);
        print_status("has dropped a fork", data->philo_index);
        pthread_mutex_unlock(&data->forks[data->philo_fork_2]);
        print_status("has dropped a fork", data->philo_index);

        print_status("is sleeping", data->philo_index);
        my_sleep(data->game_args->time_to_sleep * 1000);
    
        print_status("is thinking", data->philo_index);
    }
    return (NULL);
}

void    my_sleep(long time)
{
    long    start_time;

    start_time = get_current_time_micro_seconds();
    usleep((90 * time) / 100);
    while (get_current_time_micro_seconds() - start_time < time)
        continue ;
}

void    deploy_philosophers(t_argv  *game_args, pthread_t *philosophers, t_philo_data  *data)
{
    int     i;
    void    *ptr;

    i = 0;
    while (2 * i < game_args->number_of_philosophers)
    {
        ptr = &data[i * 2];
        pthread_create(&philosophers[i * 2], NULL, entry_point, ptr);
        i++;
    }
    my_sleep(100);//leave this one here--solves the problem of race
    i = 0;
    while (2 * i + 1 < game_args->number_of_philosophers)
    {
        ptr = &data[i * 2 + 1];
        pthread_create(&philosophers[i * 2 + 1], NULL, entry_point, ptr);
        i++;
    }
}

void    print_status(char *str, int x)
{
    pthread_mutex_lock(&g_lock_1);
    printf("[%ld ms] Philospher %d %s.\n",(get_current_time_micro_seconds() - g_start_time) / 1000, x + 1, str);
    pthread_mutex_unlock(&g_lock_1);
}

// void    join_the_bunch(pthread_t    *philosophers, t_argv   *game_args)
// {
//     int     i;
//     void    *ptr;
//     i = 0;
//     while (i < game_args->number_of_philosophers)
//     {
//         pthread_join(philosophers[i], NULL);
//         i++;
//     }
// }
