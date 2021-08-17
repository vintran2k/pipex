# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintran <vintran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/06 17:52:33 by vintran           #+#    #+#              #
#    Updated: 2021/08/07 18:07:09 by vintran          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	pipex
SRCS_DIR			=	./srcs/
INC_DIR				=	./inc/
SRCS				=	main.c			\
						ft_split.c		\
						get_cmd.c		\
						utils.c			\
						init.c			\
						close.c
SRCS_BASENAME		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS				=	$(SRCS_BASENAME:.c=.o)
CC					=	clang
FLAGS				=	-Wall -Wextra -I $(INC_DIR)

.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME)
				@echo [$(NAME)] : Created !

clean			:
				rm -f $(OBJS)

fclean			:	clean
				rm -f $(NAME)

re				:	fclean all

.PHONY: 		clean fclean all re