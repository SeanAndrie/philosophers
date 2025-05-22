# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 20:08:14 by sgadinga          #+#    #+#              #
#    Updated: 2025/05/23 02:25:06 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -Ilibcore/includes -Iincludes -DEXEC_NAME=\"$(NAME)\"

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(addprefix $(SRC_DIR)/, philo.c philo_init.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libcore $(NAME)

libcore:
	@make -C libcore

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibcore -lcore

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libcore clean

fclean: clean
	@rm -f $(NAME)
	@make -C libcore fclean

re: fclean all

.PHONY: all clean fclean re libcore
