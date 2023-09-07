

#include "../headers/philo.h"

int philo(char *number_of_philosophers, char *time_to_die, char *time_to_eat,
          char *time_to_sleep, char *number_of_time_each_philosopher_must_eat)
{

}

main(int argc, char **argv)
{
    if (argc == 5)
        philo(argv[1], argv[2], argv[3], argv[4], NULL);
    else if (argc == 6)
        philo(argv[1], argv[2], argv[3], argv[4], argv[5]);
    else
        return (printf("Error: Wrong number of args!"), 1)
    return (0)
}