# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/02 21:54:50 by moabid            #+#    #+#              #
#    Updated: 2022/08/03 23:25:51 by moabid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= ./philo

SOURCES 	= $(shell find . -name "*.c")
HEADERS 	= $(shell find . -name "*.h")

OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))
DEPENDS 	= $(patsubst %.c, %.d, $(SOURCES))

CFLAGS 		=  -g

#####################
#	  Reci			#
#	     pes		#
#####################

.PHONY	: re run fclean clean all philo_echo

all		: $(NAME)

philo_echo	:
	@echo "  "
	@echo "$(G)			    	██████╗░██╗░░██╗██╗██╗░░░░░░█████╗░                                  "
	@echo "				██╔══██╗██║░░██║██║██║░░░░░██╔══██╗                                          "
	@echo "				██████╔╝███████║██║██║░░░░░██║░░██║                                          "
	@echo "				██╔═══╝░██╔══██║██║██║░░░░░██║░░██║                                          "
	@echo "				██║░░░░░██║░░██║██║███████╗╚█████╔╝ $(W)   █▀▄▀█ █▀█ ▄▀█ █▄▄ █ █▀▄ $(G)      "
	@echo "				╚═╝░░░░░╚═╝░░╚═╝╚═╝╚══════╝░╚════╝░ $(W)   █░▀░█ █▄█ █▀█ █▄█ █ █▄▀  $(END)   "
	@echo "  $(END)"

%.o		: %.c
	@$(CC) -Iinclude $(CFLAGS) -MMD -MP -c $< -o $@
	@echo "$(G)created $(END)$@"

$(NAME)	: philo_echo $(OBJECTS)
	@$(CC) -Iinclude $(OBJECTS) -fsanitize=thread -o $(NAME)
	@echo "$(G)created $(END)$(NAME)\n"
	@echo "$(W)Executable is ready !$(END)"

norm	:
	@norminette -R CheckForbiddenSourceHeader $(HEADERS) $(SOURCES)

clean	:
	-@$(RM) $(OBJECTS) $(DEPENDS)
	@echo "$(W)Everything is Cleaned !$(END)"

fclean	: clean
	-@$(RM) $(NAME)

re		: clean all

#####################
#	  Col			#
#	     ors		#
#####################

R		= $(shell tput setaf 1)
G		= $(shell tput setaf 2)
Y		= $(shell tput setaf 3)
B		= $(shell tput setaf 4)
M		= $(shell tput setaf 5)
C		= $(shell tput setaf 6)
W		= $(shell tput setaf 7)
K		= $(shell tput setaf 8)
END		= $(shell tput sgr0)
ECHO	= echo -n "\r\033[K$(NAME): "

-include $(DEPENDS)