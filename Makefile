CC = cc

CFLAGS = -Wall -Wextra -Werror

CFILES	=	pipex.c\
			pipex2.c\
			libft_utils.c\
			ft_split.c\
			ft_pipex_utils.c\

OBJ = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

HEADER = 	mand/includes/pipex.h

NAME = pipex

OBJ_DIR = ./mand/obj

SRC_DIR = mand/src

BFILES	=	pipex.c\
			pipex2.c\
			libft_utils.c\
			ft_split.c\
			ft_pipex_utils.c\

OBJB = $(addprefix $(OBJ_DIRB)/,$(BFILES:.c=.o))

OBJ_DIRB = ./bonus/obj

HEADERB = 	bonus/includes/pipex_bonus.h

BONUS = pipex_bonus

BON_DIR = bonus/src

all : $(NAME)


$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "Done for pipex"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) -c $< -o $@

bonus : $(BONUS)

$(BONUS) : $(OBJB)
	@$(CC) $(OBJB) $(CFLAGS) -o $(BONUS)
	@echo "Done for pipex_bonus"

$(OBJ_DIRB):
	@mkdir $(OBJ_DIRB)

$(OBJB): $(OBJ_DIRB)/%.o : $(BON_DIR)/%.c $(HEADERB) | $(OBJ_DIRB)
	@$(CC) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR) $(OBJ_DIRB)

fclean : clean
	@rm -rf $(NAME) $(BONUS)

re : fclean all
