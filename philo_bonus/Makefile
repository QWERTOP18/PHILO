NAME    =  ./philo_bonus
CC      =  cc
FLAGS   =  -Wall -Wextra -Werror -fsanitize=thread

HELGRIND = valgrind --tool=helgrind -q
VALGRIND = valgrind -q# --leak-check=full --show-leak-kinds=all --track-origins=yes

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
	setarch $(uname -m) -R $(NAME) 4 310 200 100 

clean:
	@echo "$(MAGENTA)Cleaning up object files...$(RESET)"
	rm -f $(OBJ)

fclean: clean
	@echo "$(MAGENTA)Cleaning up executable...$(RESET)"
	rm -f $(NAME)

val: $(NAME)
	@echo "$(BLUE)Running $(NAME) with Valgrind...$(RESET)"
	setarch $(uname -m) -R $(VALGRIND) $(NAME) 5 310 200 100 


hel: $(NAME)
	@echo "$(BLUE)Running $(NAME) with Helgrind...$(RESET)"
	$(HELGRIND) $(NAME) 5 310 200 100 


re: fclean all

all: $(NAME)
