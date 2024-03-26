# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 11:36:49 by emimenza          #+#    #+#              #
#    Updated: 2024/03/26 14:01:33 by emimenza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definir colores
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No color (reiniciar)

#Comandos
DEL			=	rm -f
CC			=	gcc 
CCFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-lreadline -L/Users/$(USER)/.brew/opt/readline/lib
RLFLAGS		=	-I /Users/$(USER)/.brew/opt/readline/include

# -g3 -fsanitize=address

#Nombre ejecutable
NAME		=	minishell

#Ficheros
SRC_FILES	=	00_main 00_main_utils 01_history 02_signal 03_variables 04_look_for_equals 05_look_for_dollars1 05_look_for_dollars2 06_read_table 07_analyzer 08_steps 09_steps_utils 10_actions 11_built_in 12_read_tree 13_pipex_utils 14_bash_split 15_tokenization 16_free 17_pipex 18_process 19_error
SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
LIBFT		=	libs/Libft
GNL			=	libs/GNL
# PIPEX		=	libs/pipex_wenisimo

#Librerias 
LIBS		= $(LIBFT)/libft.a $(GNL)/gnl.a

# Header Files (dedicated and from libraries):
HEADERS		=  $(LIBFT)/libft.h $(INC)/minishell.h 

#Directorios
SRC_DIR = srcs/
OBJ_DIR = objs/
OBJF = objs
INC = incs

# REGLAS # 
all: libft gnl $(NAME)

#Compilar 
$(NAME):$(OBJ)
		@$(CC) $(OBJ) $(LIBS) $(LDFLAGS) -o $(NAME)
		@echo "$(GREEN)MINISHELL HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $<$(NC)"
	@$(CC) $(CFLAGS) $(RLFLAGS) -o $@ -c $<
	@echo "$(YELLOW)Compiled!$(NC)"


# $@ : The file name of the target of the rule. If the target is an archive member, then ‘$@’ is the name of the archive file.
# $< : The name of the first prerequisite.

#compilar librerias individuales
libft:
	@echo "$(YELLOW)COMPILING LIBFT...$(NC)"
	@$(MAKE) -C ./$(LIBFT)
	@echo "$(GREEN)LIBFT HAS BEEN COMPILED$(NC)"

# pipex:
# 	@echo "$(YELLOW)COMPILING PIPEX...$(NC)"
# 	@$(MAKE) -C ./$(PIPEX)
# 	@echo "$(GREEN)PIPEX HAS BEEN COMPILED$(NC)"

gnl:
	@echo "$(YELLOW)COMPILING GNL...$(NC)"
	@$(MAKE) -C ./$(GNL)
	@echo "$(GREEN)GNL HAS BEEN COMPILED$(NC)"

# Eliminar tmp libft
fclean_libft:
	@make fclean -C ./$(LIBFT)
	@echo "$(RED)LIBFT FULL CLEANED!$(NC)"

# Eliminar tmp gnl
fclean_gnl:
	@make fclean -C ./$(GNL)
	@echo "$(RED)GNL FULL CLEANED!$(NC)"

# fclean_pipex:
# 	@make fclean -C ./$(PIPEX)
# 	@echo "$(RED)PIPEX FULL CLEANED!$(NC)"

# Eliminar temporales
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)OBJS AND DIRECTORY CLEANED!$(NC)"

# Eliminar temporales y ejecutable fclean_mlx
fclean: clean fclean_libft fclean_gnl
	@$(RM) $(NAME)
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"

re: fclean all