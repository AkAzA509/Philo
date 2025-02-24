# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggirault <ggirault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 11:22:10 by ggirault          #+#    #+#              #
#    Updated: 2025/02/24 13:43:19 by ggirault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=address

OBJ_DIR = obj/

SRCS = main.c sim.c routine.c utils.c init_struct.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)

NAME = philo

GREEN = \033[0;32m
RESET = \033[0m
RED = \033[38;5;1m
WHITE = \033[38;5;7m
CYAN = \033[38;5;6m
YELLOW = \033[38;5;3m
MAGENTA = \033[38;5;5m

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: clean $(OBJS_BN)
	$(CC) $(CFLAGS) $(OBJS_BN) -o $(NAME)
	
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus