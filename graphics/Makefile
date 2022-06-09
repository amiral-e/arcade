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
			$(MAKE) $(MFLAGS) ncurses/
			$(MAKE) $(MFLAGS) sdl2/
			$(MAKE) $(MFLAGS) libcaca/

clean:
			$(MAKE) $(MFLAGS) ncurses/ clean
			$(MAKE) $(MFLAGS) sdl2/ clean
			$(MAKE) $(MFLAGS) libcaca/ clean

fclean:
			$(MAKE) $(MFLAGS) ncurses/ fclean
			$(MAKE) $(MFLAGS) sdl2/ fclean
			$(MAKE) $(MFLAGS) libcaca/ fclean

re:			fclean all

.PHONY:		all clean fclean re