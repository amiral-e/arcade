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


all:		core games graphicals

core:
			$(MAKE) $(MFLAGS) core/

games:
			$(MAKE) $(MFLAGS) games/

graphicals:
			$(MAKE) $(MFLAGS) graphics/

clean:
			$(MAKE) $(MFLAGS) core/ clean
			$(MAKE) $(MFLAGS) games/ clean
			$(MAKE) $(MFLAGS) graphics/ clean

fclean:
			$(MAKE) $(MFLAGS) core/ fclean
			$(MAKE) $(MFLAGS) games/ fclean
			$(MAKE) $(MFLAGS) graphics/ fclean

re:			fclean all

.PHONY:		all core games graphicals clean fclean re