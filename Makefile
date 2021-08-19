# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintran <vintran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/06 17:52:33 by vintran           #+#    #+#              #
#    Updated: 2021/08/19 00:34:38 by vintran          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	pipex
NAME_BONUS			=	pipex_bonus
SRCS_DIR			=	./srcs/
INC_DIR				=	./inc/
MAIN				=	./srcs/main.c
MAIN_BONUS			=	./bonus/main_bonus.c
SRCS				=	ft_split.c		\
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
MAIN_O				=	$(MAIN:.c=.o)
MAIN_BONUS_O		=	$(MAIN_BONUS:.c=.o)
CC					=	clang
FLAGS				=	-Wall -Wextra -Werror -I $(INC_DIR)


.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(MAIN_O)
				$(CC) $(FLAGS) $(OBJS) $(MAIN_O) -o $(NAME)
				@echo [$(NAME)] : Created !

bonus			:	$(OBJS) $(MAIN_BONUS_O)
				$(CC) $(FLAGS) $(OBJS) $(MAIN_BONUS_O) -o $(NAME_BONUS)
				@echo [$(NAME_BONUS)] : Created !

clean			:
				rm -f $(OBJS) $(MAIN_O) $(MAIN_BONUS_O)
				@echo [.o] : Deleted !

fclean			:	clean
				rm -f $(NAME) $(NAME_BONUS)
				@echo [$(NAME)] : Deleted !

re				:	fclean all

.PHONY: 		clean fclean all re