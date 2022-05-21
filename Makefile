CC = CC
NAME = philo
FLAGS = -Wall -Wextra -Werror

SRC = philo.c libft/ft_atoi.c libft/ft_isdigit.c util_philo.c philo_print.c ft_uslep.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) philo.h
		$(CC) $(SRC) -o  $(NAME)
%.o : %.c philo.h
		$(CC) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all