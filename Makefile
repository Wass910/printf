SRC=    ft_accessories.c	\
		ft_atoi.c       		\
		ft_itoa.c      \
		ft_itoa2.c      \
		ft_no_zer.c    \
		ft_printf.c    	\
		ft_putchar.c     \
		ft_putstr.c     \
		ft_strdup.c     \
		ft_strlen.c     \
		ft_norme.c		\

BONUS=	ft_zero.c	\
		ft_tiret.c	\
		ft_space.c	\
		ft_space2.c	\
		ft_point.c	\

NAME= libftprintf.a

OBJETS= ${SRC:.c=.o}

OBJETS_BONUS= $(BONUS:.c=.o)

gcc=gcc -Werror -Wall -Wextra

$(NAME):    ${OBJETS}	$(OBJETS_BONUS)
			ar -rc ${NAME} $^
			ranlib ${NAME}

%.o: %.c
	${gcc} -o $@ -c $<

bonus: $(OBJETS) $(OBJETS_BONUS)
	@touch $@
	ar rc $(NAME) $^
	ranlib $(NAME)
	

all: ${NAME}

re: fclean all

clean:
		rm -f ${OBJETS} $(OBJETS_BONUS)

fclean: clean
		rm -f ${NAME}

.PHONY: all clean fclean re