NAME = libft.a

SRC = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_printf.c \
ft_putchar_fd.c \
ft_putdigits.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putsc.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_lstnew.c \
ft_lstsize.c \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstlast.c \
ft_lstiter.c \
ft_lstmap.c\
get_next_line.c \
get_next_line_utils.c \
get_next_line_bonus.c \
get_next_line_utils_bonus.c \
utils_hex_fd.c \
utils_num_fd.c \
ft_atof.c \
ft_dprintf.c \
ft_putchar_fdl.c \
ft_putnbr_fdl.c \
ft_putstr_fdl.c \
ft_strcmp.c \

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

DEL = rm -rf

AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(DEL) $(OBJ)

fclean: clean
	$(DEL) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus