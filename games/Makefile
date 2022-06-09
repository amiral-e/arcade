##
## EPITECH PROJECT, 2022
## Untitled (Workspace)
## File description:
## Makefile
##


### COMPILE_USEFULL ###
#----project_usefull----#
MAKEFLAGS 	+= --no-print-directory
MFLAGS		+=	-sC
### COMPILE_USEFULL ###


all:
			$(MAKE) $(MFLAGS) nibbler/
			$(MAKE) $(MFLAGS) pacman/

clean:
			$(MAKE) $(MFLAGS) nibbler/ clean
			$(MAKE) $(MFLAGS) pacman/ clean

fclean:
			$(MAKE) $(MFLAGS) nibbler/ fclean
			$(MAKE) $(MFLAGS) pacman/ fclean

re:			fclean all

.PHONY:		all clean fclean re