# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 10:27:31 by jnauroy           #+#    #+#              #
#    Updated: 2025/05/16 15:23:47 by jnauroy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = sources
HEAD_DIR = headers

NAME = philo

SOURCES = $(SRC_DIR)/philo.c \
		  $(SRC_DIR)/philo_utils.c \
		  $(SRC_DIR)/philo_utils2.c \
		  $(SRC_DIR)/print_messages.c \
		  $(SRC_DIR)/routine.c \
		  $(SRC_DIR)/threads.c \
		  $(SRC_DIR)/manager.c \

LIBFT = libft_philo/libft.a

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -g -Wall -Wextra -Werror

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -s -C libft_philo
	cc $(OBJECTS) $(LIBFT) $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) -s clean -C libft_philo
	rm -f $(OBJECTS)
fclean: clean
	$(MAKE) -s fclean -C libft_philo
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
