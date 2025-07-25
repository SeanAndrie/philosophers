# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42.abudhabi.ae> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 12:54:04 by sgadinga          #+#    #+#              #
#    Updated: 2025/07/24 22:56:52 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibcore/includes

SRCS_DIR = src
OBJS_DIR = obj

SRCS = $(addprefix $(SRCS_DIR)/, philo.c philo_init.c debug.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: libcore $(NAME)

libcore:
	@make -C libcore

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibcore -lcore

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@make -C libcore clean

fclean: clean
	@rm -f $(NAME)
	@make -C libcore fclean

re: fclean all

.PHONY: re fclean clean libcore all
