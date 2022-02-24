CC := cc

CFILES := src/pipex.c src/get_next_line.c src/ft_strjoin_pipex.c src/ft_split.c src/ft_memcpy.c src/ft_strlen.c \
		src/ft_strncmp.c src/ft_strdup.c src/ft_putstr_fd.c src/ft_pipex_utils.c

OFILES := $(CFILES:.c=.o)

FLAGS := -Wall -Werror -Wextra

INC := src/pipex.h

NAME := pipex

$(NAME) : $(OFILES) $(INC)
	@$(CC) $(FLAGS) $(CFILES) -o $(NAME)
	@cd src && mv *.o ../obj/

all : $(NAME)

clean :
	@cd obj/ && rm -rf *.o

fclean : clean
	@rm -rf $(NAME)

re : fclean all
