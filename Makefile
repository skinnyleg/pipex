CFILES	=	pipex.c\
			ft_strjoin_pipex.c\
			ft_split.c\
			ft_memcpy.c\
			ft_strlen.c\
			ft_strncmp.c\
			ft_putstr_fd.c\
			ft_pipex_utils.c\
			ft_pid.c\
			ft_execve_error.c\

BFILES	=	pipex.c\
			ft_strjoin_pipex.c\
			ft_split.c\
			ft_memcpy.c\
			ft_strlen.c\
			ft_strncmp.c\
			ft_putstr_fd.c\
			ft_pipex_utils.c\
			ft_pid.c\
			ft_execve_error.c\
			ft_child_rep.c\

HEADER = 	mand/includes/pipex.h

HEADERB = 	bonus/includes/pipex.h

OBJ = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_B = $(addprefix $(OBJ_DIRB)/,$(BFILES:.c=.o))

NAME = pipex

bonus = pipex_bonus

CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = ./mand/obj

OBJ_DIRB = ./bonus/obj

CC = cc

SRC_DIR = ./mand/src

SRC_DIRB = ./bonus/src

all : $(NAME)


$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "Done for pipex"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) -c $< -o $@

bonus : $(bonus)

$(bonus) : $(OBJ_B)
	@$(CC) $(OBJ_B) $(CFLAGS) -o $(bonus)
	@echo "Done for pipex_bonus"

$(OBJ_B): $(OBJ_DIRB)/%.o : $(SRC_DIRB)/%.c $(HEADER_B) | $(OBJ_DIRB)
	@$(CC) -c $< -o $@

$(OBJ_DIRB):
	@mkdir $(OBJ_DIRB)

clean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIRB)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(bonus)

norme:
	@norminette **/*.c
	@norminette **/*.h

re : fclean all
