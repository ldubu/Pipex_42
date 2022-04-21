#MAKEFLAGS = --silent

CC =		cc

CFLAGS =	-Wall -Wextra -Werror
FSAN =		-g -fsanitize=address

IFLAGS = 	-I includes -I libft/includes

NAME = 		pipex

RM =		rm -rf

HEADER = 	includes/pipex.h includes/struct.h 

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

SRC =	sources/childs.c \
		sources/free.c \
		sources/here_docs.c \
		sources/main.c
OBJ = $(addprefix $(OBJS_PATH), $(SRC:.c=.o))

$(OBJS_PATH)%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS)  $(IFLAGS) -c $< -o $@
	@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"	

$(NAME): 	$(OBJ) $(HEADER) libft
	@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) libft.a -o ${NAME}
	@printf "\n${_GREEN}${_BOLD}[Pipex OK]${_END}\n"

bonus : $(OBJ) $(HEADER) libft
	@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) libft.a -o pipex_bonus
	@printf "\n${_GREEN}${_BOLD}[Pipex_bonus OK]${_END}\n"
	
all: $(NAME)

test:		$(OBJ) $(HEADER) libft
	@printf "%-15s ${_PURPLE}${_BOLD}${NAME}${_END}...\n" "Compiling"
	@$(CC) $(CFLAGS) $(FSAN) $(IFLAGS) $(OBJ) -o ${NAME}
	@printf "\n${_GREEN}${_BOLD}[Pipex fsanitize OK]${_END}\n"
libft:
	@make -C libft/
	@mv ./libft/libft.a ./

clean:
	@$(RM) $(OBJS_PATH) 

fclean:		clean
	@$(RM) $(NAME)  libft.a pipex_bonus

re: fclean all

.PHONY: 	clean fclean re all libft