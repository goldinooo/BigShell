NAME= minishell

CC= cc
CFLAGS= -Wall -Wextra -fsanitize=address
BUILD_FLAGS= -lreadline

INCLUDES= -I./include
HEADERS= $(shell find $(CWD) -type f -name "*.h")

CWD=.
BUILD_DIR= build

SRCS= $(shell find $(CWD) -type f -name "*.c")
OBJS= $(addprefix $(BUILD_DIR)/, $(SRCS:$(CWD)/%.c=%.o))

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(NAME): $(BUILD_DIR) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(BUILD_FLAGS) $(INCLUDES) $(OBJS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re