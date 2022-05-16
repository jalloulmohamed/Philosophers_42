#include "philo.h"


void *philosopher(void *var)
{
    int i ;
    t_philo *philos; 

    philos = (t_philo *)var;
    i = 0;
    while (i < philos->tab->notep_mush_eat)
    {   /* code */ 
        
        pthread_mutex_lock(&philos->tab->tabfork[philos->id - 1]);
        printf("timestamp_in_ms %d has taken a fork\n",philos->id);
        if(philos->id == philos->tab->nophilo)
            pthread_mutex_lock(&philos->tab->tabfork[0]);
        else
            pthread_mutex_lock(&philos->tab->tabfork[philos->id]);
        printf("timestamp_in_ms %d has taken a fork\n",philos->id);
        printf("timestamp_in_ms %d is eating\n",philos->id);
        usleep(philos->tab->toeat*1000);
        i++;
        pthread_mutex_unlock(&philos->tab->tabfork[philos->id - 1]);
        if(philos->id == philos->tab->nophilo)
            pthread_mutex_unlock(&philos->tab->tabfork[0]);
        else
            pthread_mutex_unlock(&philos->tab->tabfork[philos->id ]);
        printf("timestamp_in_ms %d is sleeping\n",philos->id);
        usleep(philos->tab->tosleep*1000);
        printf("timestamp_in_ms %d is thinking\n",philos->id);
    }
    
    
  
    return (0);
}

int checkarg(char ** argv)
{
    int i;
    int j;

    j = 0;
    i = 1;
    while(argv[i])
    {
        while(argv[i][j]){
            if(ft_isdigit(argv[i][j]) == 0 )
                return(1);
            j++;
        }
        j = 0;
        i++;
    }
    return(0);
}

int checkarg2(char **argv){
    if( ( ft_atoi(argv[1]) > 0 && ft_atoi(argv[1]) < 200 && ft_atoi(argv[2]) > 60 && ft_atoi(argv[3]) > 60 && ft_atoi(argv[4]) > 60) ||
     (ft_atoi(argv[1]) >0 && ft_atoi(argv[1]) < 200 && ft_atoi(argv[2]) > 60 && ft_atoi(argv[3]) > 60 && ft_atoi(argv[4]) > 60 && ft_atoi(argv[5]) >= 0) )
    {
        return(0); 
    }
    return(1);
}

int main(int argc, char **argv)
{
    t_philo *philo;
    pthread_t *th_id;
    t_tabphilo tab;

    int i;

    i = 0;
    if(argc == 6 ||  argc == 5)
    {
        if(checkarg(argv) == 1 || checkarg2(argv) == 1)
            return 1;    
        tab.nophilo = ft_atoi(argv[1]);
        tab.todie = ft_atoi(argv[2]);
        tab.toeat = ft_atoi(argv[3]);
        tab.tosleep = ft_atoi(argv[4]);
        if(argc == 6)
            tab.notep_mush_eat = ft_atoi(argv[5]);
        th_id = malloc(tab.nophilo * sizeof(pthread_t));
        philo = malloc(tab.nophilo * sizeof(t_philo));
        tab.tabfork = malloc(tab.nophilo * sizeof(pthread_mutex_t));
        while(i < tab.nophilo)
        {
            philo[i].tab = &tab;
            pthread_mutex_init(&philo->tab->tabfork[i],NULL);
            philo[i].id= i +1;
            i++; 
        }
        i = 0;
        while(i < tab.nophilo )
        {
            if(pthread_create(&th_id[i],NULL,philosopher,(void *)&philo[i]) != 0)
                return (1);
            usleep(100);
            i++;
        }
        pthread_exit(NULL);
    }
    else
        return (1);
}