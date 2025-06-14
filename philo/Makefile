# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 18:28:42 by gade-oli          #+#    #+#              #
#    Updated: 2025/06/14 15:57:41 by gade-oli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#colors-------------------------------------------------------------------------

RED     = '\033[1;31m'
GREEN   = '\033[1;32m'
BLUE    = '\033[1;34m'
RESET   = '\033[0;0m'

#variables----------------------------------------------------------------------

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

SRC = main.c utils.c parser.c routines.c async.c async_handler.c

BIN = $(SRC:%.c=%.o)

#recipes------------------------------------------------------------------------

all: $(NAME)

%.o: %.c
	@echo $(BLUE)"compiling binaries..."$(RESET)
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(BIN)
	$(CC) $(BIN) -o $@ $(CFLAGS)
	@echo $(GREEN)"$(NAME) compiled!"$(RESET)

clean:
	rm -rf $(BIN)
	@echo $(RED)"binaries deleted"$(RESET)

fclean:	clean
	rm -rf $(NAME)
	@echo $(RED)"$(NAME) deleted!"$(RESET)

re:	fclean all

.PHONY: all clean fclean re
