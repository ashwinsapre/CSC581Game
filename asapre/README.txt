Before you compile:

	The following files are required for the game to execute properly:
		a1.cpp
		Circle.h
		Rectangle.h
		Time.h
		ball.png
		brick_wall.png

Compilation instructions:
	
	Navigate to the folder containing the files listed above. Run the following commands:
		g++ -c a1.cpp
		g++ a1.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
		./sfml-app

Game controls:
	
	Move left: Left arrow key
	Move right: Right arrow key
	Jump: Up arrow key
	Change window mode (proportional/constant): LShift