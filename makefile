
OBJDIR = obj/

SRCDIR = src/

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

SRC = $(addprefix $(SRCDIR), main.c \
			get_path.c \
			excecution.c \
			parsing.c)

OBJ = $(addprefix $(OBJDIR), $(notdir $(SRC:.c=.o)))

NAME = minishell

LINKING = -lreadline

FLAGS = $(LINKING) \
	#-Wall -Werror -Wextra

all: $(OBJDIR) $(NAME)

LIBFTLIB = libft/
LIBFTA = $(LIBFTLIB)libft.a

PIPEXLIB = pipex/
PIPEXA = $(PIPEXLIB)pipex.a

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJ)
	make -C $(PIPEXLIB)
	make -C $(LIBFTLIB)
	cc $(OBJ) $(PIPEXA) $(LIBFTA) $(FLAGS) -o $(NAME)

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c
		cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(PIPEXLIB)
	make fclean -C $(LIBFTLIB)
	rm $(NAME)

re:
	make clean
	make
