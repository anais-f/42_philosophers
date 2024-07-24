# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:29:13 by anfichet          #+#    #+#              #
#    Updated: 2024/04/15 17:29:13 by anfichet         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo

# *********************************VARIABLES**************************************** #

SRCS_DIR = ./srcs

SRCS =\
		philo.c \
		utils.c \
		utils_time.c \
		utils_routine.c \
		initialisation.c \
		routine.c \
		monitoring.c \


SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS_DIR = ./objs

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INCS = ./incs

DEPS = $(OBJS:.o=.d)

# **********************************COMMANDS**************************************** #

CC = cc

CFLAGS = -Werror -Wextra -Wall -ofast -g3 -MMD -MP -pthread

CPPFLAGS = -I$(INCS)

CFSIGSEV = -fsanitize=thread

VALGRIND = valgrind -q --leak-check=full --show-reachable=yes

RM = rm -rf

DIR_DUP = mkdir -p $(@D)

MAKEFLAGS += --no-print-directory

# **********************************RULES**************************************** #

all:	$(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

fsanitize : fclean $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(CFSIGSEV) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

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
