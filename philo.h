#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>


typedef struct tabphilo {
    int nophilo;
    int todie;
    int toeat;
    int tosleep;
    int notep_mush_eat;
    pthread_mutex_t *tabfork;
} t_tabphilo;

typedef struct philo{
    t_tabphilo *tab;
    int id;
}	t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
#endif