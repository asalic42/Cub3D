# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 12:06:39 by rciaze            #+#    #+#              #
#    Updated: 2023/06/14 17:13:51 by rciaze           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -c -g3
COMP = cc $(FLAGS)
all : $(NAME)
CLEANF = rm -f *.o

SRCS =	ft_atoi.c \
ft_tolower.c \
ft_toupper.c \
ft_itoa.c \
ft_isalpha.c \
ft_isascii.c \
ft_isalnum.c \
ft_isdigit.c \
ft_isprint.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlen.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_strmapi.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_bzero.c \
ft_memcpy.c \
ft_memset.c \
ft_memmove.c \
ft_memchr.c \
ft_memcmp.c \
ft_calloc.c \
ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c \
ft_printf.c \
ft_putchar.c \
ft_putnbr.c \
ft_putstr.c \
ft_print_adress.c \
ft_strlen.c \
ft_putnbru.c \
ft_printhexa.c \
get_next_line.c \
get_next_line_utils.c 
OBJ = ${SRCS:.c=.o}

clean : 
	$(CLEANF)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

fclean : clean
	rm -f $(NAME)
re : fclean all


.PHONY : all re clean fclean 
