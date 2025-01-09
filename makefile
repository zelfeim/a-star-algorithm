##
# astar
#
# @file
# @version 0.1

astar-cli:
	gcc -g main-cli.c ./grid/grid.c ./astar/astar.c -o astar-cli -Wall -Wextra -lm -lGL -lglfw

astar-gui:
	gcc -g main-gui.c ./grid/grid.c ./astar/astar.c -o astar-gui -Wall -Wextra -lm -lGL -lglfw

# end
