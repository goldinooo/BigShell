NAME = Minishell
CC = cc
LIBS = -lreadline
SRCS = src/utils/str_man.c src/utils/signals.c src/utils/env.c src/utils/env_utils.c \
		main.c \

HEADER = minishell.h
FLAGS = -Wall -Wextra -Werror -g
OBJS = $(SRCS:.c=.o)


all: banner $(NAME) finish

banner:
	@echo "\066[1;35m"
	@echo " __  __ _       _     _          _ _ "
	@echo "|  \/  (_)     (_)   | |        | | |"
	@echo "| \  / |_ _ __  _ ___| |__   ___| | |"
	@echo "| |\/| | | '_ \| / __| '_ \ / _ \ | |"
	@echo "| |  | | | | | | \__ \ | | |  __/ | |"
	@echo "|_|  |_|_|_| |_|_|___/_| |_|\___|_|_|"
	@echo ""
	@echo "          Minishell compiling..."
	@echo "\033[0m"

finish:
	@echo "\033[1;32m✔️ Minishell Compiled\033[0m"


$(NAME): $(OBJS)
	@$(CC) $(OBJS) -L ~/.brew/opt/readline/lib/ -lreadline $(FLAGS) $(LIBS) -o $(NAME)

.c.o: $(HEADER)
	@$(CC) $(FLAGS) -I ~/.brew/opt/readline/include/ -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Cleaned :3"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all