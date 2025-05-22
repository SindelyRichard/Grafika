all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/collision.c src/enemy.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o metro.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/collision.c src/enemy.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o metro -Wall -Wextra -Wpedantic
