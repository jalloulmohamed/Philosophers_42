CC = CC
NAME = philo
BONUS = philo_bonus
FLAGS = -Wall -Wextra -Werror

SRC = philo.c util_philo.c philo_print.c ft_uslep.c libft/ft_atoi.c libft/ft_isdigit.c 
SRCB =  bonus/philo_bonus.c libft/ft_atoi.c libft/ft_isdigit.c bonus/util_philo_bonus.c bonus/philo_bonus_print.c ft_uslep.c

OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) philo.h
		$(CC) $(SRC)-o  $(NAME)

bonus: $(BONUS)

$(BONUS) : $(OBJB) bonus/philo_bonus.h
		$(CC) $(SRCB) -o  $(BONUS)

%.o : %.c 
		$(CC) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ) $(OBJB)

fclean: clean
		rm -rf $(NAME) $(BONUS)

re: fclean all