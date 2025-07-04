#include <stdio.h>
#include <stdlib.h>

/**
 * A program to control the backlight brightness.
 *
 * @author: Hendrik Werner
 */

#define MIN_BRIGHTNESS 1

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

FILE *open_file(char *name);

void print_usage(char *name) {
	printf(
		"Usage: %1$s [+|-]<value>\n"
		"\n"
		"Examples:\n"
		"\t%1$s +10\n"
		"\t%1$s -10\n"
		"\t%1$s =100\n"
		"\t%1$s 10464\n",
		name
	);
}

void print_brightness_info() {
	int brightness_value = 0;

	FILE *brightness = open_file(BRIGHTNESS_FILE);

	fscanf(brightness, "%d", &brightness_value);
	fclose(brightness);

	printf("\n"
			"Max brightness: %d\n"
			"Min brightness: %d\n"
			"Current brightness: %d\n",
			MAX_BRIGHTNESS,
			MIN_BRIGHTNESS,
			brightness_value);
}

FILE *open_file(char *name) {
	FILE *file;
	if (!(file = fopen(name, "r+"))) {
		fprintf(stderr, "failed to open %s\n", name);
		exit(EXIT_FAILURE);
	}
	return file;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		print_usage(argv[0]);
		print_brightness_info();
		return EXIT_FAILURE;
	}
	int value = strtol(argv[1], NULL, 10);
	FILE *brightness = open_file(BRIGHTNESS_FILE);
	int brightness_value = MIN_BRIGHTNESS;
	switch (argv[1][0]) {
		case '+':
		case '-':
			fscanf(brightness, "%d", &brightness_value);
			brightness_value += MAX_BRIGHTNESS * value / 100;
			break;
		case '=':
			value = strtol(argv[1] + 1, NULL, 10);
			brightness_value = MAX_BRIGHTNESS * value / 100;
			break;
		default:
			brightness_value = value;
	}
	brightness_value = MIN(brightness_value, MAX_BRIGHTNESS);
	brightness_value = MAX(brightness_value, MIN_BRIGHTNESS);
	fprintf(brightness, "%d", brightness_value);
	fclose(brightness);
	return EXIT_SUCCESS;
}
