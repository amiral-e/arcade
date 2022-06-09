##
## EPITECH PROJECT, 2022
## Untitled (Workspace)
## File description:
## Makefile
##


### SOURCES ###
#----c_sources----#
SRC		:= Sdl2.cpp
#------other------#
OBJ		:= $(SRC:.cpp=.o)
INC		:= -I ./
### SOURCES ###


### COMPILE_USEFULL ###
#----general_usefull----#
CC			= g++
#----project_usefull----#
NAME		= arcade_sdl2.so
#MAKEFLAGS 	+= --no-print-directory
#MFLAGS		+=	-sC
CPPFLAGS	:= $(INC) -fPIC
CFLAGS		:= -std=c++20 -Wall -Wextra
#CFLAGS		+= -Werror
#CFLAGS		+= -g3
LDFLAGS		:= -shared -lSDL2 -lSDL2_ttf -lSDL2_image
### COMPILE_USEFULL ###


all:		$(OBJ)
			$(CC) -o ../../lib/$(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
			$(RM) -rf $(OBJ) *.gc* *.o vgcore.*

fclean:		clean
			$(RM) -rf ../../lib/$(NAME) a.out

re:			fclean all

.PHONY:		all clean fclean re