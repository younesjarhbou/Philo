# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/25 21:22:37 by yjarhbou          #+#    #+#              #
#    Updated: 2022/08/25 21:22:38 by yjarhbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 		= main.c utils_1.c utils_2.c init_check.c
OBJES 		=   ${SRCS:.c=.o}

NAME 		=   philo
CC 			=   cc
CFLAGS 		=   -Wall -Wextra -Werror
RM 			=   rm -rf



%.o			:	%.c philo.h
				$(CC) ${CFLAGS} -c $< -o $@
	



all			:	$(NAME)

$(NAME)		:	$(OBJES) 
				$(CC) $(OBJES) -o $(NAME)
				clear



clean		:
				$(RM) $(OBJES)



fclean		:	clean
				$(RM) $(NAME)



re			:	clean all



.PHONY		:	all clean fclean re