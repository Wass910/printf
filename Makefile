SRC=    ft_accessories.c	\
		ft_atoi.c       		\
		ft_itoa.c      \
		ft_itoa2.c      \
		ft_no_zer.c    \
		ft_point.c       \
		ft_printf.c    	\
		ft_putchar.c     \
		ft_putstr.c     \
		ft_space.c     \
		ft_space2.c     \
		ft_strdup.c     \
		ft_strlen.c     \
		ft_tiret.c     \
		ft_zero.c     \

NAME= libftprintf.a

OBJETS= ${SRC:.c=.o}


gcc=gcc -Werror -Wall -Wextra

%.o: %.c
	${gcc} -o $@ -c $<

$(NAME):    ${OBJETS}
			ar -rc ${NAME} $^
			ranlib ${NAME}

all: ${NAME}

re: fclean all

clean:
		rm -f ${OBJETS}

fclean: clean
		rm -f ${NAME}

.PHONY: all clean fclean re