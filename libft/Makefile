# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 10:59:42 by maximemarti       #+#    #+#              #
#    Updated: 2025/03/02 12:13:02 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c		\
		ft_bzero.c		\
		ft_memcpy.c		\
		ft_memmove.c 	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_strlen.c		\
		ft_isalpha.c 	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strncmp.c	\
		ft_strlcpy.c	\
		ft_strndup.c    \
		ft_strlcat.c	\
		ft_strnstr.c	\
		ft_atoi.c		\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_substr.c		\
		ft_strjoin.c 	\
		ft_strtrim.c	\
		ft_split.c		\
		ft_itoa.c		\
		ft_strmapi.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_striteri.c	\
		ft_putnbr_fd.c  \
		ft_lstnew.c			\
		ft_lstadd_front.c 	\
		ft_lstsize.c 		\
		ft_lstlast.c 		\
		ft_lstadd_back.c 	\
		ft_lstdelone.c 		\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\
		ft_printf.c \
		print_cs.c \
		print_di.c \
		print_x.c \
		print_ptr.c \
		get_next_line.c \
		get_next_line_utils.c \


NAME = libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : clean fclean all re