# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintran <vintran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/06 17:52:33 by vintran           #+#    #+#              #
#    Updated: 2021/08/18 20:02:15 by vintran          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	pipex
SRCS_DIR			=	./srcs/
INC_DIR				=	./inc/
SRCS				=	main.c			\
						ft_split.c		\
						get_cmd.c		\
						utils.c			\
						utils2.c		\
						fork.c			\
						init.c			\
						error.c			\
						close.c			\
						exit.c
SRCS_BASENAME		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS				=	$(SRCS_BASENAME:.c=.o)
CC					=	clang
FLAGS				=	-Wall -Wextra -Werror -I $(INC_DIR)

.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME)
				@echo [$(NAME)] : Created !

clean			:
				rm -f $(OBJS)
				@echo [$(OBJS)] : Deleted !

fclean			:	clean
				rm -f $(NAME)
				@echo [$(NAME)] : Deleted !

re				:	fclean all

.PHONY: 		clean fclean all re