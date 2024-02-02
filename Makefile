
OBJDIR = obj/

SRCDIR = src/

COLOUR_GREEN=\033[0;32m
COLOUR_PURPLE=\033[0;35m
COLOUR_END=\033[0m
COLOUR_BLUE=\033[0;34
COLOUR_LIGHT_BLUE=\033[1;34
COLOUR_CYAN=\033[0;36
COLOUR_LIGHT_CYAN=\033[1;36

SRC = $(addprefix $(SRCDIR), main.c)

OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))

NAME = a.out

LINKING = -lreadline

FLAGS = $(LINKING) \
		#-Wall -Werror -Wextra 

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJ)
	@cc $(OBJ) $(FLAGS) -o $(NAME)
	@echo "$(COLOUR_PURPLE)cc $(OBJ) $(FLAGS) -o $(NAME)$(COLOUR_END)\n"

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c
		@cc $(FLAGS) -c $< -o $@
		@echo "$(COLOUR_GREEN)cc $(FLAGS) -c $< -o $@$(COLOUR_END)\n"

clean:
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)

re:
	make clean
	make
