# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 23:37:23 by minsuki2          #+#    #+#              #
#    Updated: 2022/08/20 02:54:52 by minsuki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo_bonus
CFLAGS = -Wall -Werror -Wextra

SRCS = philo_bonus.c	 		\
	   philo_utils_bonus.c		\
	   routine_bonus.c			\
	   print_out_bonus.c		\
	   ft_postive_atoi_bonus.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
