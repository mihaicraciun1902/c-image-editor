//Craciun Mihai Alexandru 313CA
#include "functii.h"

#define uc unsigned char

// Allocate memory for image data
void aloc_image(image *my_image)
{
	// aloc height
	my_image->data = (rgb **)malloc(my_image->height * sizeof(rgb *));
	// aloc width
	for (int i = 0; i < my_image->height; i++)
		my_image->data[i] = (rgb *)malloc(my_image->width * sizeof(rgb));
}

// Free memory allocated for image data
void free_image(image *my_image)
{
	if (!my_image) {
		for (int i = 0; i < my_image->height; i++)
			free(my_image->data[i]);
		free(my_image->data);
	}
}

// Read metadata from the image file
void read_imagemetadata(image *my_image, FILE **file, char *name)
{
	fscanf(*file, "%s", my_image->tip);
	fscanf(*file, "%d", &my_image->width);
	fscanf(*file, "%d", &my_image->height);
	fscanf(*file, "%d", &my_image->maxim);
	fclose(*file);
	if (my_image->tip[1] - 3 <= 0)
		*file = fopen(name, "r");
	else
		*file = fopen(name, "rb");
	read_image(my_image, file);
}

// Read image data from the file
void read_image(image *my_image, FILE **file)
{
	fscanf(*file, "%s", my_image->tip);
	if (strcmp(my_image->tip, "P3") == 0) {
		fscanf(*file, "%d", &my_image->width);
		fscanf(*file, "%d", &my_image->height);
		fscanf(*file, "%d", &my_image->maxim);
		aloc_image(my_image);
		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++) {
				int r, g, b;
				fscanf(*file, "%d %d %d", &r, &g, &b);
				// Assign values to my_image structure
				my_image->data[i][j].r = r;
				my_image->data[i][j].g = g;
				my_image->data[i][j].b = b;
			}
	} else if (strcmp(my_image->tip, "P6") == 0) {
		fscanf(*file, "%d", &my_image->width);
		fscanf(*file, "%d", &my_image->height);
		fscanf(*file, "%d", &my_image->maxim);
		fgetc(*file);
		aloc_image(my_image);
		uc buf[3];
		for (int i = 0; i < my_image->height; i++) {
			for (int j = 0; j < my_image->width; j++) {
				fread(buf, sizeof(uc), 3, *file);
				my_image->data[i][j].r = (int)buf[0];
				my_image->data[i][j].g = (int)buf[1];
				my_image->data[i][j].b = (int)buf[2];
			}
		}
	} else if (strcmp(my_image->tip, "P5") == 0) {
		fscanf(*file, "%d", &my_image->width);
		fscanf(*file, "%d", &my_image->height);
		fscanf(*file, "%d", &my_image->maxim);
		fgetc(*file);
		aloc_image(my_image);
		uc buf;
		for (int i = 0; i < my_image->height; i++) {
			for (int j = 0; j < my_image->width; j++) {
				fread(&buf, sizeof(uc), 1, *file);
				my_image->data[i][j].r = (int)buf;
			}
		}
	} else if (strcmp(my_image->tip, "P4") == 0) {
		fscanf(*file, "%d", &my_image->width);
		fscanf(*file, "%d", &my_image->height);
		fscanf(*file, "%d", &my_image->maxim);
		fgetc(*file);
		aloc_image(my_image);
		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++)
				fread(&my_image->data[i][j].r, sizeof(uc), 1, *file);
	} else {
		fscanf(*file, "%d", &my_image->width);
		fscanf(*file, "%d", &my_image->height);
		fscanf(*file, "%d", &my_image->maxim);
		aloc_image(my_image);
		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++)
				fscanf(*file, "%d", &my_image->data[i][j].r);
	}
}

void save_ascii(image *my_image, FILE **file)
{
	if (strcmp(my_image->tip, "P3") == 0) {
		fprintf(*file, "%s\n", my_image->tip);
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);
		for (int i = 0; i < my_image->height; i++) {
			for (int j = 0; j < my_image->width; j++) {
				fprintf(*file, "%d ", my_image->data[i][j].r);
				fprintf(*file, "%d ", my_image->data[i][j].g);
				fprintf(*file, "%d ", my_image->data[i][j].b);
			}
			fprintf(*file, "\n");
		}
	} else if (strcmp(my_image->tip, "P6") == 0) {
		fprintf(*file, "%s\n", "P3");
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);
		for (int i = 0; i < my_image->height; i++) {
			for (int j = 0; j < my_image->width; j++) {
				fprintf(*file, "%d ", my_image->data[i][j].r);
				fprintf(*file, "%d ", my_image->data[i][j].g);
				fprintf(*file, "%d ", my_image->data[i][j].b);
			}
			fprintf(*file, "\n");
		}
	} else if (strcmp(my_image->tip, "P5") == 0) {
		fprintf(*file, "%s\n", "P2");
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);
		for (int i = 0; i < my_image->height; i++) {
			for (int j = 0; j < my_image->width; j++)
				fprintf(*file, "%d ", my_image->data[i][j].r);
			fprintf(*file, "\n");
		}
	} else if (strcmp(my_image->tip, "P4") == 0) {
		fprintf(*file, "%s\n", "P1");
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);
		for (int i = 0; i < my_image->height; i++) {
			for (int j = 0; j < my_image->width; j++)
				fprintf(*file, "%d ", my_image->data[i][j].r);
			fprintf(*file, "\n");
		}
	} else { // P2 P1
		fprintf(*file, "%s\n", my_image->tip);
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);
		for (int i = 0; i < my_image->height; i++) {
			for (int j = 0; j < my_image->width; j++)
				fprintf(*file, "%d ", my_image->data[i][j].r);
			fprintf(*file, "\n");
		}
	}
}

void save_binary(image *my_image, FILE **file)
{
	if (strcmp(my_image->tip, "P3") == 0) {
		fprintf(*file, "%s\n", "P6");
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);

		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++) {
				fwrite(&my_image->data[i][j].r, sizeof(uc), 1, *file);
				fwrite(&my_image->data[i][j].g, sizeof(uc), 1, *file);
				fwrite(&my_image->data[i][j].b, sizeof(uc), 1, *file);
			}
	} else if (strcmp(my_image->tip, "P6") == 0) {
		fprintf(*file, "%s\n", my_image->tip);
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);

		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++) {
				fwrite(&my_image->data[i][j].r, sizeof(uc), 1, *file);
				fwrite(&my_image->data[i][j].g, sizeof(uc), 1, *file);
				fwrite(&my_image->data[i][j].b, sizeof(uc), 1, *file);
			}
	} else if (strcmp(my_image->tip, "P5") == 0) {
		fprintf(*file, "%s\n", my_image->tip);
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);

		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++)
				fwrite(&my_image->data[i][j].r, sizeof(uc), 1, *file);
	} else if (strcmp(my_image->tip, "P4") == 0) {
		fprintf(*file, "%s\n", my_image->tip);
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);
		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++)
				fwrite(&my_image->data[i][j].r, sizeof(uc), 1, *file);
	} else if (strcmp(my_image->tip, "P2") == 0) {
		fprintf(*file, "%s\n", "P5");
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);

		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++)
				fwrite(&my_image->data[i][j].r, sizeof(uc), 1, *file);
	} else {
		fprintf(*file, "%s\n", "P4");
		fprintf(*file, "%d ", my_image->width);
		fprintf(*file, "%d\n", my_image->height);
		fprintf(*file, "%d\n", my_image->maxim);

		for (int i = 0; i < my_image->height; i++)
			for (int j = 0; j < my_image->width; j++)
				fwrite(&my_image->data[i][j].r, sizeof(uc), 1, *file);
	}
}

// Write image data to the file
void save_image(image *my_image, FILE **file, int is_ascii)
{
	if (is_ascii)
		save_ascii(my_image, file);
	else
		save_binary(my_image, file);
}

int load_file(char *name, FILE **file)
{
	if (*file) {
		fclose(*file);
		*file = NULL;
	}

	*file = fopen(name, "r");

	if (!(*file)) {
		printf("Failed to load %s\n", name);
		return 0;

	} else {
		char tipcheck[3];
		fscanf(*file, "%s", tipcheck);
		if ((int)tipcheck[1] - '0' < 1 || (int)tipcheck[1] - '0' > 6) {
			fclose(*file);
			*file = NULL;
			printf("Failed to load %s\n", name);
			return 0;
		}
		printf("Loaded %s\n", name);
		return 1;
	}
}

int save_file(char *name, FILE **file, int is_ascii)
{
	if (*file) {
		fclose(*file);
		*file = NULL;
	}

	if (is_ascii)
		*file = fopen(name, "w");
	else
		*file = fopen(name, "wb");

	if (!(*file)) {
		printf("Failed to save %s\n", name);
		return 0;

	} else {
		printf("Saved %s\n", name);
		return 1;
	}
}

int is_number(char *string)
{
	for (unsigned int i = 0; i < strlen(string); i++)
		if ((string[i] < '0' || string[i] > '9') && (string[i] != '-'))
			return 0;
	return 1;
}

void clear_input_buffer(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

void select_region(image *my_image, int *x1, int *y1, int *x2, int *y2)
{
	if (!my_image) {
		clear_input_buffer();
		printf("No image loaded\n");
		return;
	}

	int temp[4];
	char input[50];

	if (!fgets(input, sizeof(input), stdin) || input[0] != ' ') {
		printf("Invalid command\n");
		return;
	}
	char *token = strtok(input + 1, "\n ");

	if (token && strcmp(token, "ALL") == 0) {
		*x1 = 0;
		*y1 = 0;
		*x2 = my_image->width;
		*y2 = my_image->height;
		printf("Selected ALL\n");
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (!token || !is_number(token)) {
			printf("Invalid command\n");
			return;
		}

		temp[i] = atoi(token);
		token = strtok(NULL, "\n ");
	}

	// Swap the coordonates
	if (temp[0] > temp[2]) {
		int temp_swap = temp[0];
		temp[0] = temp[2];
		temp[2] = temp_swap;
	}

	if (temp[1] > temp[3]) {
		int temp_swap = temp[1];
		temp[1] = temp[3];
		temp[3] = temp_swap;
	}

	int ok1, ok2, ok3, ok4;
	ok1 = temp[0] < 0 || temp[1] < 0;
	ok2 = temp[2] > my_image->width || temp[3] > my_image->height;
	ok3 = temp[0] >= temp[2] || temp[1] >= temp[3];
	ok4 = temp[2] < 0 || temp[3] < 0;
	if (ok1 || ok2 || ok3 || ok4) {
		printf("Invalid set of coordinates\n");
		return;
	}

	//only replace coordonates if valid
	*x1 = temp[0];
	*y1 = temp[1];
	*x2 = temp[2];
	*y2 = temp[3];

	printf("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
}

void crop(image *my_image, int *x1, int *y1, int *x2, int *y2)
{
	if (!my_image) {
		printf("No image loaded\n");
		return;
	}

	int new_height = *y2 - *y1;
	int new_width = *x2 - *x1;

	// Allocate memory for the cropped image
	image *cropped_image = (image *)malloc(sizeof(image));
	cropped_image->width = new_width;
	cropped_image->height = new_height;
	strcpy(cropped_image->tip, my_image->tip);
	aloc_image(cropped_image);

	// Copy pixels from the original image to the cropped image
	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++)
			cropped_image->data[i][j] = my_image->data[*y1 + i][*x1 + j];
	}

	// Free memory of the original image
	free_image(my_image);

	// Update the original image with the cropped image data
	my_image->width = new_width;
	my_image->height = new_height;
	aloc_image(my_image);

	//copy data from cropped image to myimage
	for (int i = 0; i < my_image->height; i++) {
		for (int j = 0; j < my_image->width; j++)
			my_image->data[i][j] = cropped_image->data[i][j];
	}

	strcpy((my_image)->tip, cropped_image->tip);

	// Free memory of the cropped image
	free_image(cropped_image);
	free(cropped_image);

	//update selection
	*x1 = 0;
	*x2 = my_image->width;
	*y1 = 0;
	*y2 = my_image->height;

	printf("Image cropped\n");
}

int clamp(int value, int min, int max)
{
	return (value < min) ? min : ((value > max) ? max : value);
}

// Function to apply a generic filter to the image
void a(image *my_image, int x1, int y1, int x2, int y2, int ker[3][3], int div)
{
	int sum_r, sum_g, sum_b;
	//temp image
	image *t_i = (image *)malloc(sizeof(image));
	strcpy(t_i->tip, my_image->tip);
	t_i->width = my_image->width;
	t_i->height = my_image->height;
	t_i->maxim = my_image->maxim;
	aloc_image(t_i);

	for (int i = y1; i < y2 && i < my_image->height; i++) {
		for (int j = x1; j < x2 && j < my_image->width; j++) {
			int ok1, ok2;
			ok1 = (i == 0 || j == 0);
			ok2 = (i == my_image->height - 1 || j == my_image->width - 1);
			if (ok1 || ok2) {
				// If on the edge of the image, copy the pixel value
				t_i->data[i][j].r = my_image->data[i][j].r;
				t_i->data[i][j].g = my_image->data[i][j].g;
				t_i->data[i][j].b = my_image->data[i][j].b;
			} else {
				sum_r = 0, sum_g = 0, sum_b = 0;

				for (int k = -1; k <= 1; k++) {
					for (int l = -1; l <= 1; l++) {
						int ni = i + k;
						int nj = j + l;

						sum_r += ker[k + 1][l + 1] * my_image->data[ni][nj].r;
						sum_g += ker[k + 1][l + 1] * my_image->data[ni][nj].g;
						sum_b += ker[k + 1][l + 1] * my_image->data[ni][nj].b;
					}
				}

				t_i->data[i][j].r = clamp(sum_r / div, 0, my_image->maxim);
				t_i->data[i][j].g = clamp(sum_g / div, 0, my_image->maxim);
				t_i->data[i][j].b = clamp(sum_b / div, 0, my_image->maxim);
			}
		}
	}

	// copy the temporary image back to the original image
	for (int i = y1; i < y2 && i < my_image->height; i++) {
		for (int j = x1; j < x2 && j < my_image->width; j++) {
			my_image->data[i][j].r = t_i->data[i][j].r;
			my_image->data[i][j].g = t_i->data[i][j].g;
			my_image->data[i][j].b = t_i->data[i][j].b;
		}
	}

	//free the tempimage
	free_image(t_i);
	free(t_i);
}

// Function to apply blur filter to the image
void apply_blur(image *my_image, int x1, int y1, int x2, int y2)
{
	int ker[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	int div = 9;

	a(my_image, x1, y1, x2, y2, ker, div);
}

// Function to apply a guussian blur filter to the image
void apply_gaussian_blur(image *my_image, int x1, int y1, int x2, int y2)
{
	int ker[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
	int div = 16;

	a(my_image, x1, y1, x2, y2, ker, div);
}

// Function to apply an edge detection filter to the image
void apply_edge_detection(image *my_image, int x1, int y1, int x2, int y2)
{
	int ker[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
	int div = 1;

	a(my_image, x1, y1, x2, y2, ker, div);
}

void apply_sharpen(image *my_image, int x1, int y1, int x2, int y2)
{
	int ker[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

	int div = 1;

	a(my_image, x1, y1, x2, y2, ker, div);
}

void apply(image *my_image, char *apply_op, int x1, int y1, int x2, int y2)
{
	if (strcmp(my_image->tip, "P2") == 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	if (strcmp(my_image->tip, "P5") == 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	if (strlen(apply_op) == 0) {
		printf("APPLY parameter invalid\n");
		return;
	}

	if (strcmp(apply_op, "EDGE") == 0) {
		apply_edge_detection(my_image, x1, y1, x2, y2);
	} else if (strcmp(apply_op, "SHARPEN") == 0) {
		apply_sharpen(my_image, x1, y1, x2, y2);
	} else if (strcmp(apply_op, "BLUR") == 0) {
		apply_blur(my_image, x1, y1, x2, y2);
	} else if (strcmp(apply_op, "GAUSSIAN_BLUR") == 0) {
		apply_gaussian_blur(my_image, x1, y1, x2, y2);
	} else {
		printf("APPLY parameter invalid\n");
		return;
	}

	printf("APPLY %s done\n", apply_op);
}

void histogram(image *my_image, int x1, int y1, int x2, int y2)
{
	// Check if the image is loaded
	if (!my_image) {
		clear_input_buffer();
		printf("No image loaded\n");
		return;
	}

	// if no parameter exist
	if ((char)getchar() != ' ') {
		printf("Invalid command\n");
		return;
	}

	char xt[100];
	char yt[100];
	int max_stars, bins;
	char clear[100];

	scanf("%s", xt);
	if ((char)getchar() == '\n') {
		printf("Invalid command\n");
		return;
	}
	scanf("%s", yt);

	if (is_number(xt) && is_number(yt)) {
		max_stars = atoi(xt);
		bins = atoi(yt);
	} else {
		scanf("%255[^\n]", clear);
		printf("Invalid command\n");
	}

	// if space after the two numbers invalid command
	if ((char)getchar() == ' ') {
		printf("Invalid command\n");
		scanf("%255[^\n]", clear);
		return;
	}

	// Check if the image is color
	if (strcmp(my_image->tip, "P3") == 0 || strcmp(my_image->tip, "P6") == 0) {
		printf("Black and white image needed\n");
		return;
	}

	int h[256] = {0};
	int f = 0;
	for (int i = x1; i < y2; i++) {
		for (int j = y1; j < x2; j++) {
			int bin_size = (my_image->maxim + 1) / bins;
			int bin_index = my_image->data[i][j].r / bin_size;
			h[bin_index]++;
			if (h[bin_index] > f)
				f = h[bin_index];
		}
	}

	// Print the histogram
	for (int i = 0; i < bins; i++) {
		int num_stars = h[i] * max_stars / f;
		printf("%d\t|\t", num_stars);
		for (int j = 0; j < num_stars; j++)
			printf("*");
		printf("\n");
	}
}

void equalize(image *my_image)
{
	if (!my_image) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(my_image->tip, "P2") != 0 && strcmp(my_image->tip, "P5") != 0) {
		printf("Black and white image needed\n");
		return;
	}

	int h[256] = {0};
	for (int i = 0; i < my_image->height; i++) {
		for (int j = 0; j < my_image->width; j++) {
			int pixel_value = my_image->data[i][j].r;
			h[pixel_value]++;
		}
	}

	double d[256];
	d[0] = (double)h[0] / (my_image->width * my_image->height);
	for (int i = 1; i < 256; i++)
		d[i] = d[i - 1] + (double)h[i] / (my_image->width * my_image->height);

	// equalize the channel
	for (int i = 0; i < my_image->height; i++) {
		for (int j = 0; j < my_image->width; j++) {
			int pixel_value = my_image->data[i][j].r;
			int new_pixel_value = (int)round(d[pixel_value] * 255.0);

			// Ensure the new pixel value is in the range [0, 255]
			new_pixel_value = fmin(255, fmax(0, new_pixel_value));

			// Apply the new pixel value
			my_image->data[i][j].r = new_pixel_value;
		}
	}

	printf("Equalize done\n");
}

void rotate(image *my_image, int *x1, int *y1, int *x2, int *y2)
{
	// Check if the image is loaded
	if (!my_image) {
		clear_input_buffer();
		printf("No image loaded\n");
		return;
	}

	//read the angle
	int angle;
	scanf("%d", &angle);

	// Check if the angle is valid
	if (angle % 90 != 0 || abs(angle) > 360) {
		printf("Unsupported rotation angle\n");
		return;
	}

	//nr of counterclockwise rotations
	int rotation = ((360 + angle) % 360) / 90;

	for (int z = 0; z < rotation; z++) {
		int ok1, ok2;
		ok1 = *x1 == 0 && *y1 == 0;
		ok2 = *y2 == my_image->height && *x2 == my_image->width;
		int is_entire_image = (ok1 && ok2);

		if (is_entire_image) {
			image *t_i = (image *)malloc(sizeof(image));
			strcpy(t_i->tip, my_image->tip);
			//swap the image size
			t_i->width = my_image->height;
			t_i->height = my_image->width;
			t_i->maxim = my_image->maxim;
			aloc_image(t_i);

			for (int i = 0; i <  t_i->height; i++)
				for (int j = 0; j <  t_i->width; j++)
					t_i->data[i][j] = my_image->data[t_i->width - j - 1][i];

			free_image(my_image);
			strcpy(my_image->tip, t_i->tip);
			my_image->width = t_i->width;
			my_image->height = t_i->height;
			aloc_image(my_image);

			for (int i = 0; i <  t_i->height; i++)
				for (int j = 0; j <  t_i->width; j++)
					my_image->data[i][j] = t_i->data[i][j];

			//update selection
			*x1 = 0;
			*x2 = t_i->width;
			*y1 = 0;
			*y2 = t_i->height;
			free_image(t_i);
			free(t_i);
		} else {
			image *t_i = (image *)malloc(sizeof(image));
			strcpy(t_i->tip, my_image->tip);
			t_i->width = *x2 - *x1;
			t_i->height = *y2 - *y1;
			t_i->maxim = my_image->maxim;
			aloc_image(t_i);

			for (int i = 0; i < t_i->height; i++)
				for (int j = 0; j < t_i->width; j++)
					t_i->data[i][j] = my_image->data[*y2 - j - 1][i + *x1];

			for (int i = 0; i < t_i->height; i++)
				for (int j = 0; j < t_i->width; j++)
					my_image->data[i + *y1][j + *x1] = t_i->data[i][j];

			free_image(t_i);
			free(t_i);
		}
	}
	printf("Rotated %d\n", angle);
}
