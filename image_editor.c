//Craciun Mihai Alexandru 313CA
#include "functii.h"

int main(void)
{
	FILE *file = NULL; //pointer file
	char name[100], apply_op[100], op[100];
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0; // coordinates for image operations

	image *my_image = NULL;  // Pointer to image structure

	while (1) { // Infinite loop for reading commands
		scanf("%s", op); // Read the operation from the user
		if (strcmp(op, "LOAD") == 0) {
			scanf("%s", name); // Read the file name from the user
			if (my_image) { // Free memory if an image is already loaded
				free_image(my_image); free(my_image);
			}
			if (load_file(name, &file)) {
				// Allocate memory for the image
				my_image = (image *)malloc(sizeof(image));
				read_imagemetadata(my_image, &file, name); // Read metadata
				// Set default coordinates
				x1 = 0; y1 = 0; x2 = my_image->width; y2 = my_image->height;
			} else {
				my_image = NULL;
			}
		} else if (strcmp(op, "SAVE") == 0) {
			int is_ascii = 0; // Flag to check if "ascii" is provided
			scanf("%s", name); // Read the file name from the user
			int next_char = getchar(); // Read the next character
			if (next_char != '\n') {
				is_ascii = 1;
				if (next_char != EOF)
					ungetc(next_char, stdin);
				clear_input_buffer();
			} else {
				is_ascii = 0;
			}
			if (!my_image) {
				printf("No image loaded\n");
				continue;
			}
			if (save_file(name, &file, is_ascii))
				save_image(my_image, &file, is_ascii);// Save the image
		} else if (strcmp(op, "SELECT") == 0) {
			select_region(my_image, &x1, &y1, &x2, &y2); // select region
		} else if (strcmp(op, "APPLY") == 0) { // apply
			if (!my_image || !file) {
				clear_input_buffer();
				printf("No image loaded\n"); continue;
			} else {
				char next_char = getchar(); // Read the next character
				if (next_char == '\n' || next_char == EOF) {
					printf("Invalid command\n"); continue;
				} else {
					ungetc(next_char, stdin); scanf("%s", apply_op);
					apply(my_image, apply_op, x1, y1, x2, y2);
				}
			}
		} else if (strcmp(op, "CROP") == 0) {
			crop(my_image, &x1, &y1, &x2, &y2);
		} else if (strcmp(op, "HISTOGRAM") == 0) {
			histogram(my_image, x1, y1, x2, y2);
		} else if (strcmp(op, "EQUALIZE") == 0) {
			equalize(my_image);
		} else if (strcmp(op, "ROTATE") == 0) {
			rotate(my_image, &x1, &y1, &x2, &y2);
		} else if (strcmp(op, "EXIT") == 0) {
			if (file)
				fclose(file); // Close the file if open
			if (!my_image) {
				printf("No image loaded\n");
			} else {
				free_image(my_image); free(my_image);
			}
			return 0;

		} else {
			printf("Invalid command\n");
			clear_input_buffer();
		}
	}
}
