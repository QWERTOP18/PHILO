NAME    =  ./philo
CC      =  cc
FLAGS   =  -Wall -Wextra -Werror -pthread -fsanitize=thread
HELGRIND = valgrind --tool=helgrind -q#--history-level=none
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q

RED     =  \033[31m
GREEN   =  \033[32m
YELLOW  =  \033[33m
BLUE    =  \033[34m
MAGENTA =  \033[35m
CYAN    =  \033[36m
WHITE   =  \033[37m
RESET   =  \033[0m

SRC     =  daemon.c loop.c main.c system.c utils.c
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
	setarch $(uname -m) -R  $(NAME) 5 800 200 200


test:: $(NAME)
	@echo "$(BLUE)Running $(NAME)...$(RESET)"
	setarch $(uname -m) -R  $(NAME) 4 310 200 100
	setarch $(uname -m) -R  $(NAME) 1 800 200 200
	setarch $(uname -m) -R  $(NAME) 4 410 200 200 5

val: $(NAME)
	@echo "$(BLUE)Running $(NAME) with Valgrind...$(RESET)"
	$(VALGRIND) setarch $(uname -m) -R $(NAME) 4 310 200 100


# hel: $(NAME)
# 	@echo "$(BLUE)Running $(NAME) with Helgrind...$(RESET)"
# 	$(VALGRIND) setarch $(uname -m) -R $(HELGRIND) $(NAME) 5 800 200 200

clean:
	@echo "$(MAGENTA)Cleaning up object files...$(RESET)"
	rm -f $(OBJ)

fclean: clean
	@echo "$(MAGENTA)Cleaning up executable...$(RESET)"
	rm -f $(NAME)

re: fclean all

all: $(NAME)

