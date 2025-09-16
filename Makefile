NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

SRCS = minishell.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(NAME)

re: clean all

.PHONY: all clean re
