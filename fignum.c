#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isdigit and ispunct

// ANSI escape codes for colors
#define BG_WHITE    "\033[47;m" // Background white
#define BG_TRANSPARENT "\033[49m"           // Background transparent (default)
#define RESET_COLOR "\033[0m"               // Reset all attributes

// ASCII art definitions for digits 0-9 and decimal point
// Each character is 5 lines high and 6 characters wide.
// '#' represents the "filled" part (white background)
// ' ' represents the "empty" part (transparent background)
const char *ASCII_DIGITS[11][5] = {
    // 0
    {"######",
     "##  ##",
     "##  ##",
     "##  ##",
     "######"},
    // 1
    {"    ##",
     "    ##",
     "    ##",
     "    ##",
     "    ##"},
    // 2
    {"######",
     "    ##",
     "######",
     "##    ",
     "######"},
    // 3
    {"######",
     "    ##",
     "######",
     "    ##",
     "######"},
    // 4
    {"##  ##",
     "##  ##",
     "######",
     "    ##",
     "    ##"},
    // 5
    {"######",
     "##    ",
     "######",
     "    ##",
     "######"},
    // 6
    {"######",
     "##    ",
     "######",
     "##  ##",
     "######"},
    // 7
    {"######",
     "    ##",
     "    ##",
     "    ##",
     "    ##"},
    // 8
    {"######",
     "##  ##",
     "######",
     "##  ##",
     "######"},
    // 9
    {"######",
     "##  ##",
     "######",
     "    ##",
     "######"},
    // . (decimal point)
    {"      ",
     "      ",
     "      ",
     "      ",
     "##    "}
};

// Function to print a string of numbers as ASCII art with colors
void print_number_ascii(const char *num_str) {
    // Iterate through each line of the ASCII art (0 to 4)
    for (int line = 0; line < 5; line++) {
        // Iterate through each character in the input string
        for (int i = 0; num_str[i] != '\0'; i++) {
            char c = num_str[i];
            int index = -1;

            if (c >= '0' && c <= '9') {
                index = c - '0';
            } else if (c == '.') {
                index = 10;
            } else {
                // If invalid character, skip it or print a space
                continue;
            }

            // Print each character segment with appropriate background color
            for (int j = 0; j < 6; j++) { // Each segment is 6 characters wide
                if (ASCII_DIGITS[index][line][j] != ' ') {
                    printf("%s%c", BG_WHITE, ASCII_DIGITS[index][line][j]); // White background
                } else {
                    printf("%s ", BG_TRANSPARENT); // Transparent background for ' '
                }
            }
            printf("%s", RESET_COLOR); // Reset color after each character segment
            printf(" "); // Small space between numbers for clarity
        }
        printf("\n"); // Move to the next line of ASCII art
    }
    printf("%s", RESET_COLOR); // Ensure color is reset at the end of the entire number
}

int main(int argc, char *argv[]) {
    char input_buffer[256]; // Buffer for standard input

    if (argc > 1) {
        // Input from command-line arguments
        for (int i = 1; i < argc; i++) {
            // Basic validation: ensure it's only digits and one decimal point
            int decimal_count = 0;
            for (int j = 0; argv[i][j] != '\0'; j++) {
                if (isdigit(argv[i][j])) {
                    // Valid digit
                } else if (argv[i][j] == '.') {
                    decimal_count++;
                    if (decimal_count > 1) {
                        fprintf(stderr, "Error: Multiple decimal points in '%s'. Only numbers and one decimal allowed.\n", argv[i]);
                        return EXIT_FAILURE;
                    }
                } else {
                    fprintf(stderr, "Error: Invalid character '%c' in '%s'. Only numbers and decimal points allowed.\n", argv[i][j], argv[i]);
                    return EXIT_FAILURE;
                }
            }
            print_number_ascii(argv[i]);
            if (i < argc - 1) {
                printf("\n"); // Add a blank line between multiple numbers
            }
        }
    } else {
        // Input from standard input
        while (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            // Remove trailing newline character if present
            input_buffer[strcspn(input_buffer, "\n")] = 0;

            // Basic validation: ensure it's only digits and one decimal point
            int decimal_count = 0;
            for (int j = 0; input_buffer[j] != '\0'; j++) {
                if (isdigit(input_buffer[j])) {
                    // Valid digit
                } else if (input_buffer[j] == '.') {
                    decimal_count++;
                    if (decimal_count > 1) {
                        fprintf(stderr, "Error: Multiple decimal points in '%s'. Only numbers and one decimal allowed.\n", input_buffer);
                        return EXIT_FAILURE;
                    }
                } else {
                    fprintf(stderr, "Error: Invalid character '%c' in '%s'. Only numbers and decimal points allowed.\n", input_buffer[j], input_buffer);
                    return EXIT_FAILURE;
                }
            }
            if (strlen(input_buffer) > 0) { // Only print if there's actual input
                print_number_ascii(input_buffer);
            }
        }
    }

    return EXIT_SUCCESS;
}