NAME    =  ./philo_bonus
CC      =  cc
FLAGS   =  -Wall -Wextra -fsanitize=thread

RED     =  \033[31m
GREEN   =  \033[32m
YELLOW  =  \033[33m
BLUE    =  \033[34m
MAGENTA =  \033[35m
CYAN    =  \033[36m
WHITE   =  \033[37m
RESET   =  \033[0m

SRC     =  daemon_bonus.c loop_bonus.c main_bonus.c system_bonus.c utils_bonus.c
OBJ     =  $(SRC:.c=.o)

$(NAME): $(OBJ)
	@echo "$(CYAN)Compiling $(NAME)...$(RESET)"
	$(CC) $(OBJ) -o $(NAME) $(FLAGS)
	@echo "$(GREEN)Compilation complete!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) -c $< -o $@ $(FLAGS)

run: $(NAME)
	@echo "$(BLUE)Running $(NAME)...$(RESET)"
	./$(NAME) 2 2 2 2 2

clean:
	@echo "$(MAGENTA)Cleaning up object files...$(RESET)"
	rm -f $(OBJ)

fclean: clean
	@echo "$(MAGENTA)Cleaning up executable...$(RESET)"
	rm -f $(NAME)

re: fclean all

all: credit $(NAME)

credit:

	@echo 'Try'
	@echo "Marry()"
	@echo "If you marry a good wife,"
	@echo "you will be happy."
	@echo "If a bad wife,"
	@echo "you will become a"
	@echo ""
	@echo "philosopher"
	@echo ""
	@sleep 1
	@echo ""
	@echo "except SpouseNotFound"
	@echo "you shall be a"
	@echo "Hacker!"
