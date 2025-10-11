NAME= minishell

CC= cc

# BUILD_FLAGS= -lreadline -L/goinfre/retahri/homebrew/opt/readline/lib
CFLAGS= -Wall -Wextra -fsanitize=address -ggdb3
BUILD_FLAGS= -lreadline -L/Users/abraimi/homebrew/opt/readline/lib

CWD=.
BUILD_DIR= build

INCLUDES= -I./include -I/Users/abraimi/homebrew/opt/readline/include
HEADERS= $(shell find $(CWD) -type f -name "*.h")


SRCS= $(shell find $(CWD) -type f -name "*.c")
OBJS= $(addprefix $(BUILD_DIR)/, $(SRCS:$(CWD)/%.c=%.o))

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(NAME): $(BUILD_DIR) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(BUILD_FLAGS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re