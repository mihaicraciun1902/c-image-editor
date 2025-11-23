#Craciun Mihai Alexandru 313CA
build:
	gcc image_editor.c functii.c functii.h -o image_editor -lm -Wall -Wextra
clean:
	rm image_editor
