# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 18:25:46 by anfichet          #+#    #+#              #
#    Updated: 2024/03/25 18:56:11 by anfichet         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

LIBS = libft.a

# *********************************VARIABLES**************************************** #

SRCS_DIR = ./srcs

SRCS =\
		main.c \
		utils.c \
		children.c \
		parsing.c \

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

SRCS_BONUS =\
		main_bonus.c \
		utils_bonus.c \
		children_bonus.c \
		parsing_bonus.c \
		
SRCS_BONUS := $(SRCS_BONUS:%=$(SRCS_DIR)/%)

OBJS_DIR = ./objs

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

OBJS_BONUS = $(SRCS_BONUS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INCS = ./incs

INCS_LIBS = ./libft/INCS

DEPS = $(OBJS:.o=.d)

DEPS_BONUS = $(OBJS_BONUS:.o=.d)

LIBS_TARGET = ./libft/libft.a

# **********************************COMMANDS**************************************** #

CC = cc

CFLAGS = -Werror -Wextra -Wall -g3 -MMD -MP

CPPFLAGS = -I$(INCS) -I$(INCS_LIBS)

CFSIGSEV = -fsanitize=address

VALGRIND = valgrind -q --leak-check=full --show-reachable=yes

RM = rm -rf

DIR_DUP = mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

# **********************************RULES**************************************** #

all:	$(NAME)

bonus:	$(NAME_BONUS)

-include $(DEPS)
-include $(DEPS_BONUS)

$(NAME): $(LIBS_TARGET) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -L$(dir $(LIBS_TARGET)) -lft -o $(NAME)

$(NAME_BONUS): $(LIBS_TARGET) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS_BONUS) -L$(dir $(LIBS_TARGET)) -lft -o $(NAME_BONUS)

$(LIBS_TARGET): FORCE
	@echo " "
	@echo "\033[1m\033[32m#-------------------------[COMPILATION LIBFT]-------------------------#\033[0m"
	$(MAKE) -C $(@D)
	@echo "\033[1m\033[32m#---------------------------[LIBFT COMPILED]--------------------------#\033[0m"
	@echo " "

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

fsanitize : fclean $(LIBS_TARGET) $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(CFSIGSEV) $(CPPFLAGS) $(OBJS) -L$(dir $(LIBS_TARGET)) -lft -o $(NAME)

# fsanitize_bonus : fclean $(LIBS_TARGET) $(OBJS_BONUS) $(INCS)
# 	$(CC) $(CFLAGS) $(CFSIGSEV) $(CPPFLAGS) $(OBJS_BONUS) -L$(dir $(LIBS_TARGET)) -lft -o $(CHECKER)

clean :
	$(RM) $(OBJS_DIR)
	$(MAKE) $@ -C ./libft

fclean : clean
	$(RM) $(NAME)
	$(MAKE) $@ -C ./libft

re : fclean all

print% :
	@echo $(patsubst print%,%,$@)=
	@echo $($(patsubst print%,%,$@))

.PHONY: all clean fclean re FORCE bonus fsanitize print%
FORCE:

# Colors
BLACK=\033[30m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
PURPLE=\033[35m
CYAN=\033[36m
WHITE=\033[37m

# Text
ERASE=\033[2K\r
RESET=\033[0m
BOLD=\033[1m
FAINT=\033[2m
ITALIC=\033[3m
UNDERLINE=\033[4m
