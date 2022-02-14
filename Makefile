CC := cc

CFILES := src/pipex.c src/get_next_line.c

OFILES := $(CFILES:.c=.o)

FLAGS := -Wall -Werror -Wextra

INC := src/pipex.h

NAME := pipex

$(NAME) : libft.a $(OFILES) $(INC)
	@$(CC) $(FLAGS) $(CFILES) Libft/libft.a -o $(NAME)
	@cd src && mv *.o ../obj/

libft.a :
	@cd Libft && make

all : $(NAME)

clean :
	@cd obj/ && rm -rf *.o
	@cd Libft/ && make clean

fclean : clean
	@rm -rf $(NAME)
	@cd Libft/ && make fclean

re : fclean all
