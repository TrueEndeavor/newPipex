# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 12:46:34 by lannur-s          #+#    #+#              #
#    Updated: 2023/10/10 10:26:54 by lannur-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Usage:
#   - Run 'make' to build the $(NAME) target (default)
#   - Run 'make clean' to remove object files
#   - Run 'make fclean' to remove object files and the $(NAME) archive
#   - Run 'make re' to perform a clean build by removing all generated files 
#     and rebuilding the project
#   - Run 'make so' to create a shared library using the object files
#   - Run 'make all' to build the $(NAME) target (same as the default 'make')
#
# Note: Adjust variables $(CC), $(CFLAGS), $(AR), $(ARFLAGS), $(SRCS), $(BONUS)
#       according to project requirements

# Name of the archive
NAME = libft.a

# Compiler options
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Archive options
AR = ar
ARFLAGS = rcs

INCLUDES = -I./include

# Mandatory source (.c) files
SRCS = src/conversion/ft_atoi.c \
		src/conversion/ft_itoa.c \
		src/ctype/ft_isalnum.c \
		src/ctype/ft_isalpha.c \
		src/ctype/ft_isascii.c \
		src/ctype/ft_isdigit.c \
		src/ctype/ft_isprint.c \
		src/ctype/ft_tolower.c \
		src/ctype/ft_toupper.c \
		src/env/ft_path_utils.c \
		src/io/ft_printf/ft_printf.c \
		src/io/ft_printf/print_char.c \
		src/io/ft_printf/print_nbr_base.c \
		src/io/ft_printf/print_nbr_signed.c \
		src/io/ft_printf/print_string.c \
		src/io/get_next_line/get_next_line.c \
		src/io/ft_putchar_fd.c \
		src/io/ft_putendl_fd.c \
		src/io/ft_putstr_fd.c \
		src/io/ft_putnbr_fd.c \
		src/linkedlist/ft_lstadd_back.c \
		src/linkedlist/ft_lstadd_front.c \
		src/linkedlist/ft_lstdelone.c \
 		src/linkedlist/ft_lstiter.c \
		src/linkedlist/ft_lstlast.c \
		src/linkedlist/ft_lstmap.c \
		src/linkedlist/ft_lstnew.c \
		src/linkedlist/ft_lstclear.c \
		src/linkedlist/ft_lstsize.c \
		src/memory/ft_bzero.c \
		src/memory/ft_calloc.c \
		src/memory/ft_memchr.c \
		src/memory/ft_memcmp.c \
		src/memory/ft_memcpy.c \
		src/memory/ft_memmove.c \
		src/memory/ft_memset.c \
		src/string/ft_split.c \
		src/string/ft_strchr.c \
		src/string/ft_strcmp.c \
		src/string/ft_strdup.c \
		src/string/ft_striteri.c \
		src/string/ft_strjoin.c \
		src/string/ft_strlcat.c \
		src/string/ft_strlcpy.c \
		src/string/ft_strlen.c \
		src/string/ft_strmapi.c \
		src/string/ft_strncmp.c \
		src/string/ft_strnstr.c \
		src/string/ft_strrchr.c \
		src/string/ft_strtrim.c \
		src/string/ft_substr.c \

# Variable assignment with pattern substitution:
# Generate a list of object files 
# by replacing the ".c" extension with ".o" for each source file
OBJS = $(SRCS:%.c=%.o)

# Target rule: $(NAME)
# Builds the final archive by linking object files 
# $(OBJS)
$(NAME): $(OBJS) 
	@echo "Linking $@"
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "Done!"

# Pattern rule: %.o
# Generic rule to compile source files to object files.
# Uses the compiler $(CC) with flags $(CFLAGS) to compile 
# the source file ($<) and produce the object file ($@)
%.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	
# Target rule: all
# Builds the default target $(NAME) by invoking the target $(NAME)
all: $(NAME)

# Target rule: clean
# Removes object files $(OBJS) and $(BONUSOBJS) 
# from the current directory
clean:
	rm -f $(OBJS)

# Target rule: fclean
# Removes object files $(OBJS) and $(BONUSOBJS), 
# and the archive $(NAME) from the current directory
# Calls the target 'clean' to remove object files first	
fclean: clean
	rm -f $(NAME)

# Target rule: re
# Performs a clean build by removing all generated files 
# (object files and the archive) and rebuilding the project 
# from scratch by invoking the targets 'fclean' and 'all'
re: fclean all

# Target rule: .PHONY
# Specifies phony targets that do not represent actual files.
# 'all', 'clean', 'fclean', and 're' are marked as phony targets.
# This prevents conflicts if there are files with the same names.
.PHONY: all clean fclean re
