# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 07:10:48 by anurtiag          #+#    #+#              #
#    Updated: 2024/01/09 06:48:51 by anurtiag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

NAME_BONUS		=	pipex_bonus

LIBFT			=	./lib/Libft

PRINTF			= 	./lib/ft_printf

GNL				=	./lib/gnl

LIBS			=	$(LIBFT)/libft.a $(PRINTF)/libftprintf.a

LIBS_BONUS		=	$(LIBFT)/libft.a $(PRINTF)/libftprintf.a $(GNL)/gnl.a

HEADERS			=	-I $(LIBFT) -I $(PRINTF)

HEADERS_BONUS	=	-I $(LIBFT) -I $(PRINTF) -I $(GNL)

SRCS			=	pipex.c utils.c process.c

SRCS_BONUS		=	pipex_bonus.c utils_bonus.c here_doc_bonus.c process_bonus.c

OBJ				=	$(SRCS:.c=.o)

OBJ_BONUS		=	$(SRCS_BONUS:.c=.o)

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror #-g3 -fsanitize=address

RM				=	rm -rf



all:			$(NAME)

$(NAME):		libft printf $(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

bonus:			libft printf gnl
				@$(CC) -g $(CFLAGS) -c $(SRCS_BONUS) $(HEADERS_BONUS)
				@$(CC) -g $(CFLAGS) $(OBJ_BONUS) $(LIBS_BONUS) -o $(NAME_BONUS)

libft:
				@$(MAKE) -C $(LIBFT)
printf:
				@$(MAKE) -C  $(PRINTF)
gnl:
				@$(MAKE) -C  $(GNL)
clean:
				@$(RM) $(OBJ)
				@$(RM) $(OBJ_BONUS)
				@$(MAKE) -C $(LIBFT) clean
				@$(MAKE) -C $(PRINTF) clean
				@$(MAKE) -C $(GNL) clean

fclean:			clean
				@$(MAKE) -C $(LIBFT) fclean
				@$(MAKE) -C $(PRINTF) fclean
				@$(MAKE) -C $(GNL) fclean
				@$(RM) $(NAME)
				@$(RM) $(NAME_BONUS)

re:				fclean all

.PHONY:			all clean fclean re libft libmlx printf