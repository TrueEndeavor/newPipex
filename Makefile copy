# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 13:43:15 by lannur-s          #+#    #+#              #
#    Updated: 2023/10/24 08:40:45 by lannur-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
LIBFTNAME = libft.a

CC = cc -g3
CCFLAGS = -Wall -Werror -Wextra

AR = ar
ARFLAGS = -rcs

LIBFT_DIR = ./include/libft_combined

INCLUDES = -I./include -I$(LIBFT_DIR)/include

SRCS = src/mandatory/pipex.c \
		src/mandatory/validator.c \
		src/mandatory/pipex_utils.c \
		src/mandatory/free_resources.c \
		src/mandatory/close_fd.c \

BONUS_SRCS = src/bonus/pipex_bonus.c \
		src/bonus/validator_bonus.c \
		src/bonus/free_resources_bonus.c \
		src/bonus/close_fd_bonus.c \
		src/bonus/utils_1_bonus.c \
		src/bonus/utils_2_bonus.c \
		
OBJS = $(SRCS:%.c=%.o)

BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

$(NAME): $(OBJS) $(LIBFT_DIR)/$(LIBFTNAME)
	$(CC) $(CCFLAGS) $(SRCS) $(LIBFT_DIR)/$(LIBFTNAME) $(INCLUDES) -o ${NAME}

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT_DIR)/$(LIBFTNAME)
	$(CC) $(CCFLAGS) $(BONUS_SRCS) $(LIBFT_DIR)/$(LIBFTNAME) $(INCLUDES) -o ${BONUS_NAME}

$(LIBFT_DIR)/$(LIBFTNAME):
	make -C $(LIBFT_DIR)

%.o: %.c $(HEADERS)
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

bonus: $(BONUS_NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	cd $(LIBFT_DIR) && make clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	cd $(LIBFT_DIR) && make fclean

re: fclean
	${make}

.PHONY: all clean fclean re
