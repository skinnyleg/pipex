CFILES	=	pipex.c\
			ft_strjoin_pipex.c\
			ft_split.c\
			ft_memcpy.c\
			ft_strlen.c\
			ft_strncmp.c\
			ft_putstr_fd.c\
			ft_pipex_utils.c\
			ft_pid.c\

HEADER = 	includes/pipex.h

OBJ = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

NAME 	= pipex

CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = ./obj

CC = cc

SRC_DIR = ./src

all : $(NAME)


$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "Done for pipex"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -rf $(NAME)

norme:
	@norminette **/*.c
	@norminette **/*.h

re : fclean all