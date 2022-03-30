MAKEFLAGS = --silent

CC = 		gcc

CFLAGS =	-Wall -Werror -Wextra

IFLAGS = 	-I ./includes/

NAME = 		libft.a

RM =		rm -rf

HEADER = 	includes/libft.h \
			includes/list.h \
			includes/ft_printf.h \
			includes/ft_struct.h

OBJS_PATH = objs/

_GREY=	$'\033[30m
_RED=	$'\033[31m
_GREEN=	$'\033[32m
_YELLOW=$'\033[33m
_BLUE=	$'\033[34m
_PURPLE=$'\033[35m
_CYAN=	$'\033[36m
_WHITE=	$'\033[37m
_END= 	$'\033[37m

SRC =		mem/ft_bzero.c\
			mem/ft_memset.c\
			mem/ft_memcpy.c\
			mem/ft_memmove.c\
			mem/ft_memchr.c\
			mem/ft_calloc.c\
			mem/ft_memcmp.c \
			str/ft_isalnum.c\
			str/ft_isalpha.c\
			str/ft_isascii.c\
			str/ft_isdigit.c\
			str/ft_isprint.c\
			str/ft_strlen.c\
			str/ft_strlcpy.c\
			str/ft_strlcat.c\
			str/ft_toupper.c\
			str/ft_tolower.c\
			str/ft_strchr.c\
			str/ft_strrchr.c\
			str/ft_strncmp.c\
			str/ft_strnstr.c\
			str/ft_atoi.c\
			str/ft_strdup.c\
			str/ft_substr.c\
			str/ft_strjoin.c\
			str/ft_strtrim.c\
			str/ft_split.c\
			str/ft_itoa.c\
			str/ft_strmapi.c\
			str/ft_striteri.c\
			print/ft_putchar_fd.c\
			print/ft_putstr_fd.c\
			print/ft_putendl_fd.c\
			print/ft_putnbr_fd.c\
			print/ft_putchar.c\
			print/ft_putstr.c\
			print/ft_putendl.c\
			print/ft_putnbr.c\
			gnl/get_next_line.c \
			gnl/free_str.c

LIST =		list/ft_lstadd_back.c\
			list/ft_lstadd_front.c\
			list/ft_lstclear.c\
			list/ft_lstdelone.c\
			list/ft_lstiter.c\
			list/ft_lstlast.c\
			list/ft_lstmap.c\
			list/ft_lstnew.c\
			list/ft_lstsize.c\

PRINTF = printf/srcs/ft_printf.c \
		printf/srcs/ft_putstr.c \
		printf/srcs/ft_flags.c \
		printf/srcs/ft_strrchr.c \
		printf/srcs/ft_toupper.c \
		printf/srcs/ft_unsi_itoa.c \
		printf/srcs/ft_address.c \
		printf/srcs/ft_c_to_str.c \
		printf/srcs/ft_hexa.c \
		printf/srcs/ft_itoa.c \
		printf/srcs/ft_strlen.c \
		printf/srcs/ft_strjoin.c \
		printf/srcs/ft_putargs.c \
		printf/srcs/ft_ini_struct.c \
		printf/srcs/ft_write_args.c \
		printf/srcs/ft_strcpy.c \
		printf/srcs/ft_strncmp.c \
		printf/srcs/ft_sign.c \
		printf/srcs/ft_pre.c


OBJ = $(addprefix $(OBJS_PATH), $(SRC:.c=.o))
OBJL = $(addprefix $(OBJS_PATH), $(LIST:.c=.o))
OBJP = $(addprefix $(OBJS_PATH), $(PRINTF:.c=.o))

$(OBJS_PATH)%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"			

$(NAME): 	$(OBJ) $(OBJL) $(OBJP) $(HEADER)
	@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
	@ar rc $(NAME) $(OBJ) $(OBJL) $(OBJP)
	@printf "\n${_GREEN}${_BOLD}[Libft OK]${_END}\n"
	
all: $(NAME)

clean:
	@$(RM) $(OBJS_PATH)
	
fclean:		clean
	@$(RM) $(NAME)
	
re: 	fclean all

.PHONY: 	clean fclean re all