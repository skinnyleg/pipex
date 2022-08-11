CC = cc

CFLAGS = -Wall -Wextra -Werror

CFILES	=	pipex.c\
			pipex2.c\
			ft_pipex_utils.c\

OBJ = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

HEADER = 	mand/includes/pipex.h

NAME = pipex

OBJ_DIR = ./mand/obj

SRC_DIR = mand/src

BFILES	=	pipex.c\
			init_var.c\
			here_doc.c\
			utils.c\
			ft_pipex_utils.c\

OBJB = $(addprefix $(OBJ_DIRB)/,$(BFILES:.c=.o))

OBJ_DIRB = ./bonus/obj

HEADERB = 	bonus/includes/pipex_bonus.h

BONUS = pipex_bonus

BON_DIR = bonus/src

LIBFT = libft/libft.a

all : bonus


$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(LIBFT) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "Done for pipex"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) -c $< -o $@

$(LIBFT) :
	@make -C libft

bonus : $(BONUS)

$(BONUS) : $(LIBFT) $(OBJB)
	@$(CC) $(LIBFT) $(OBJB) $(CFLAGS) -o $(BONUS)
	@echo "Done for pipex_bonus"

$(OBJ_DIRB):
	@mkdir $(OBJ_DIRB)

$(OBJB): $(OBJ_DIRB)/%.o : $(BON_DIR)/%.c $(HEADERB) | $(OBJ_DIRB)
	@$(CC) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR) $(OBJ_DIRB)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME) $(BONUS)
	@make fclean -C libft

re : fclean all
