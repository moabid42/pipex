# # MAKEFLAGS += --no-builtin-rules
# # MAKEFLAGS += --no-builtin-variables
# CC 		= gcc
# CFLAGS 	= -Wall -Wextra -Werror -g
# PROG  	= pipex
# PROG_B 	= pipex_bonus

# INCLUDES	= -I./includes
# LIBFT		= 	./libft/libft.a

# SRCS 	= pipex.c
# SRCS_B 	= pipex_bonus.c
# OBJS 	= ${SRCS:.c=.o}
# OBJS_B  = ${SRCS_B:.c=.o}

# %.o : %.c
# 	@gcc ${CFLAGS} ${INCLUDES} -c $< -o $@

# all: 		${PROG}

# ${PROG}:	${OBJS}
# 	@echo "\033[33m----Compiling lib----"
# 	@make re -C ./libft
# 	@$(CC) -o $(PROG) $(INCLUDES) $(OBJS) $(LIBFT)
# 	@echo "\033[32mPipex Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

# bonus:		${PROG_B}

# ${PROG_B}:	${OBJS_B}
# 	@echo "\033[33m----Compiling lib----"
# 	@make -C ./libft
# 	@$(CC) -o $(PROG_B) $(INCLUDES) $(OBJS_B) $(LIBFT)
# 	@echo "\033[32mBonus Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"
# clean:
# 	@make clean -C ./libft
# 	@rm -rf ${OBJS} ${OBJS_B}
# 	@rm -rf pipex.o pipex_bonus.o

# fclean: 	clean
# 	@make fclean -C ./libft
# 	@rm -rf $(NAME)
# 	@rm -rf ${PROG}
# 	@rm -rf ${PROG_B}

PIPEX		=	pipex
PIPEX_BONUS	=	pipex_bonus

FLAGS		=	-Wall -Wextra -Werror -g
CC			=	gcc
INCLUDES	= 	-I./include
LIBFT		= 	./libft/libft.a

CHECKER_DIR		=	./src/
CHECKER_FILES	=	pipex.c error.c parser.c utils.c
CHECKERS		= 	$(addprefix $(CHECKER_DIR), $(CHECKER_FILES))

SRCS_DIR	=	./src/
SRCS_FILES	=	pipex_bonus.c error_bonus.c parser_bonus.c utils_bonus.c
SRCS		= 	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJ_DIR		=	./mnd/
OBJS1	 	= $(OBJS_FILES:.c=.o)
OBJS_FILES	=	$(addprefix $(OBJ_DIR), $(SRCS_FILES))

OBJ_DIR_2		=	./bonus/
OBJS2		= $(OBJS_CH_FILES:.c=.o)
OBJS_CH_FILES	=	$(addprefix $(OBJ_DIR_2), $(CHECKER_FILES))

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) ${FLAGS} ${INCLUDES} -c $< -o $@

$(OBJ_DIR_2)%.o : $(CHECKER_DIR)%.c
	@$(CC) ${FLAGS} ${INCLUDES} -c $< -o $@

all: $(PIPEX)

bonus : $(PIPEX_BONUS)

$(PIPEX): $(OBJS2) 
	@echo "\033[33m----Compiling PIPEX...----"
	@make -C ./libft --silent
	@$(CC) -o $(PIPEX) $(INCLUDES) $(OBJS2) $(LIBFT)
	@echo "\033[32mPIPEX Compiled! ༺ (\033[31m♥\033[32m_\033[31m♥\033[32m)༻\n"

$(PIPEX_BONUS): $(OBJS1)
	@echo "\033[33m----Compiling BONUS...----"
	@make -C ./libft --silent
	@$(CC) -o $(PIPEX_BONUS) $(INCLUDES) $(OBJS1) $(LIBFT)
	@echo "\033[32mBONUS Compiled! ༺ (\033[31m♥\033[32m_\033[31m♥\033[32m)༻\n"

clean:
	@echo "\033[33m     Cleaning the garbage ..."
	@make clean -C ./libft --silent
	@rm -f $(OBJS1)
	@rm -f $(OBJS2)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(PIPEX_BONUS) $(PIPEX)
	@echo "\033[32mEverything is fcleaned! ✓ (\033[31m>_<\033[32m)\n"

re: fclean all

.PHONY: all clean fclean re