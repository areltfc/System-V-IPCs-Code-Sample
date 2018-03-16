##
## EPITECH PROJECT, 2018
## Sys V IPCs
## File description:
## Created by arthur,
##

SRCS	=	src/main.c		\
		src/x_funcs.c		\
		src/init.c		\
		src/processes.c		\
		src/printing.c		\
		src/destroy.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	trains

CC	=	gcc

CFLAGS	=	-I include/

LDFLAGS	=	-Wall -Wextra

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
