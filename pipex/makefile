M_SRCSDIR = pipex_src/

M_SRCS= $(M_SRCSDIR)pipex.c	\
		$(M_SRCSDIR)cmds.c \
		$(M_SRCSDIR)read_file.c \
		$(M_SRCSDIR)helper_functions1.c \
		$(M_SRCSDIR)helper_functions2.c \
		$(M_SRCSDIR)pipe_actions.c \
		$(M_SRCSDIR)parsing.c \
		$(M_SRCSDIR)read_timeout.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c

M_OBJS = $(M_SRCS:.c=.o)

M_A = pipex.a

BUF_SIZE = 5

M_EXE = pipex

LIBFTLIB = ../libft

LIBFTA = $(LIBFTLIB)/libft.a

FLAGS = #-Wall -Werror -Wextra

all: $(M_EXE)

$(M_EXE): $(M_OBJS) $(LIBFTA)
	cp $(LIBFTA) $(M_A)
	ar rcs $(M_A) $(M_OBJS)

#cc $(FLAGS) -lreadline -g $(M_A) -o $(M_EXE)

$(LIBFTA):
	make -C $(LIBFTLIB)

$(M_OBJS): %.o: %.c
		cc $(FLAGS) -DBUFFER_SIZE=$(BUF_SIZE) -g -c $< -o $@

clean:
	rm $(M_EXE)
	rm $(M_A)
	rm $(M_OBJS)

fclean:
	make fclean -C $(LIBFTLIB)
	make clean

re: fclean all
