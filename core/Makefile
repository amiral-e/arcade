##
## EPITECH PROJECT, 2022
## Untitled (Workspace)
## File description:
## Makefile
##


### SOURCES ###
#----c_sources----#
SRC		:= main.cpp
SRC		+= Core.cpp
#------other------#
OBJ		:= $(SRC:.cpp=.o)
INC		:= -I ./
### SOURCES ###


### COMPILE_USEFULL ###
#----general_usefull----#
CC			= g++
#----project_usefull----#
NAME		= arcade
#MAKEFLAGS 	+= --no-print-directory
#MFLAGS		+=	-sC
CPPFLAGS	:= $(INC) -fno-gnu-unique -fPIE
CFLAGS		:= -std=c++20 -Wall -Wextra
#CFLAGS		+= -Werror
#CFLAGS		+= -g3
LDFLAGS		:= -ldl
### COMPILE_USEFULL ###


all:		$(OBJ)
			$(CC) -o ../$(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
			$(RM) -rf $(OBJ) *.gc* *.o vgcore.*

fclean:		clean
			$(RM) -rf ../$(NAME) a.out

re:			fclean all

.PHONY:		all clean fclean re