##
## EPITECH PROJECT, 2022
## Untitled (Workspace)
## File description:
## Makefile
##


### SOURCES ###
#----c_sources----#
SRC		:= Nibbler.cpp
SRC		+= Player.cpp
SRC		+= Apple.cpp
#------other------#
OBJ		:= $(SRC:.cpp=.o)
INC		:= -I ./
### SOURCES ###


### COMPILE_USEFULL ###
#----general_usefull----#
CC			= g++
#----project_usefull----#
NAME		= arcade_nibbler.so
#MAKEFLAGS 	+= --no-print-directory
#MFLAGS		+=	-sC
CPPFLAGS	:= $(INC) -fPIC -g
CFLAGS		:= -std=c++20 -Wall -Wextra
#CFLAGS		+= -Werror
#CFLAGS		+= -g3
LDFLAGS		:= -shared -lncurses
### COMPILE_USEFULL ###


all:		$(OBJ)
			$(CC) -o ../../lib/$(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
			$(RM) -rf $(OBJ) *.gc* *.o vgcore.*

fclean:		clean
			$(RM) -rf ../../lib/$(NAME) a.out

re:			fclean all

.PHONY:		all clean fclean re