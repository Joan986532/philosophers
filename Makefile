# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 16:49:14 by jnauroy           #+#    #+#              #
#    Updated: 2025/04/24 19:05:30 by jnauroy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = sources
HEAD_DIR = headers

NAME = philo

SOURCES = $(SRC_DIR)/philo.c \
		  $(SRC_DIR)/philo_utils.c

LIBFT = libft_philo/libft.a

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -fsanitize=thread -g -Wall -Wextra -Werror

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C libft_philo
	cc $(OBJECTS) $(LIBFT) $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C libft_philo
	rm -f $(OBJECTS)
fclean: clean
	$(MAKE) fclean -C libft_philo
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
