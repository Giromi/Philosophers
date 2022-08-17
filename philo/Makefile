# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 02:03:01 by minsuki2          #+#    #+#              #
#    Updated: 2022/08/17 14:50:48 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo
CFLAGS = -Wall -Werror -Wextra
# CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g
# CFLAGS = -Wall -Werror -Wextra -fsanitize=address

SRCS = philo.c			\
	   philo_utils.c	\
	   routine.c		\
	   print_out.c		\
	   ft_postive_atoi.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -lpthread -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

lldb: $(NAME)
	$(CC) $(CFLAGS) $(SRCS) -g -lpthread -o $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
