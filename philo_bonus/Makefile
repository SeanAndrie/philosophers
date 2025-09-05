# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 15:42:20 by sgadinga          #+#    #+#              #
#    Updated: 2025/09/05 17:08:06 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibcore/includes

SRCS_DIR = src
OBJS_DIR = obj

SRCS = $(addprefix $(SRCS_DIR)/, \
		 main.c initialize.c parsing.c \
		 simulate.c simulate_utils.c actions.c cleanup.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME) libcore

libcore/libcore.a:
	@make -C libcore

$(NAME): libcore/libcore.a $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibcore -lcore

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@make -C libcore clean

fclean: clean
	@rm -f $(NAME)
	@make -C libcore fclean

re: fclean all

.PHONY: re fclean clean libcore all