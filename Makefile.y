
OBJDIR = obj/

SRCDIR = src/

COLOUR_GREEN=\033[0;32m
COLOUR_PURPLE=\033[0;35m
COLOUR_END=\033[0m
COLOUR_BLUE=\033[0;34
COLOUR_LIGHT_BLUE=\033[1;34
COLOUR_CYAN=\033[0;36
COLOUR_LIGHT_CYAN=\033[1;36

SRC = $(addprefix $(SRCDIR), main.c, get_path.c, test.c)

OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))

NAME = a.out

LIBFTLIB = libft/
LIBFTA = $(LIBFTLIB)libft.a

PIPEXLIB = pipex/
PIPEXA = $(PIPEXLIB)pipex.a

LINKING = -lreadline

FLAGS = $(LINKING) \
		#-Wall -Werror -Wextra 

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJ)
	echo $(SRC)
	echo $(OBJ)
	make -C $(LIBFTLIB)
	make -C $(PIPEXLIB)
	@gcc $(OBJ) $(LIBFTA) $(PIPEXA) $(FLAGS) -o $(NAME)
	@echo "$(COLOUR_PURPLE)cc $(OBJ) $(LIBFTA) $(PIPEXA) $(FLAGS) -o $(NAME)$(COLOUR_END)\n"

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c
		@gcc $(FLAGS) -c $< -o $@
		@echo "$(COLOUR_GREEN)cc $(FLAGS) -c $< -o $@$(COLOUR_END)\n"

clean:
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFTLIB)
	make fclean -C $(PIPEXLIB)
	rm $(NAME)

re:
	make clean
	make