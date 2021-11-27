NAME		=	philo_bonus
HEADER		=	./includes/
CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra -I $(HEADER)
SRCS		=	main.c \
				utils.c \
				parser.c \
				eat_process.c

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC)  $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm $(NAME)

re			:	fclean all