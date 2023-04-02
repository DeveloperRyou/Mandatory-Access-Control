NAME = mac
CC = gcc
CFLAGS = -Wall -Werror -Wextra

INCLUDE = ./include

SRCS_DIR = ./src
SRCS = src/main.c \
		src/parse.c \
		src/file.c \
		src/mac.c \
		src/print.c \
		src/authority.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : 
	make fclean
	make all

.PHONY: all clean fclean re
