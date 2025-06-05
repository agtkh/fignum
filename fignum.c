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

// Function to print a string of numbers as ASCII art with colors and right-alignment
void print_number_ascii(const char *num_str, int desired_width) {
    int original_digit_count = strlen(num_str); // 元の数字の桁数を取得（小数点も1桁としてカウント）
    int char_display_width = 6; // 各ASCII文字の表示上の幅
    int space_between_chars = 1; // 各ASCII文字間のスペース

    // ASCIIアート全体が占める実際の画面上の文字数
    // 各数字の幅 (6) + 各数字間のスペース (1) * (数字の数 - 1)
    int actual_display_width = original_digit_count * char_display_width + (original_digit_count - 1) * space_between_chars;
    if (original_digit_count == 0) {
        actual_display_width = 0;
    } else if (original_digit_count == 1) { // 1桁の場合、スペースは含まれない
        actual_display_width = char_display_width;
    }


    // パディングの計算（元の数字の桁数を基準にする）
    int padding_spaces_count = 0;
    if (desired_width > 0 && original_digit_count < desired_width) {
        // desired_widthは「元の数字の桁数」なので、
        // ASCIIアートの表示上の幅に変換してパディングを計算
        int target_ascii_display_width = desired_width * char_display_width + (desired_width - 1) * space_between_chars;
        if (desired_width == 1) {
            target_ascii_display_width = char_display_width;
        }

        if (target_ascii_display_width > actual_display_width) {
            padding_spaces_count = target_ascii_display_width - actual_display_width;
        }
    }


    // Iterate through each line of the ASCII art (0 to 4)
    for (int line = 0; line < 5; line++) {
        // Print leading spaces for right alignment
        for (int p = 0; p < padding_spaces_count; p++) {
            printf(" ");
        }

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
            for (int j = 0; j < char_display_width; j++) { // Each segment is 6 characters wide
                if (ASCII_DIGITS[index][line][j] != ' ') {
                    printf("%s%c", BG_WHITE, ASCII_DIGITS[index][line][j]); // White background
                } else {
                    printf("%s ", BG_TRANSPARENT); // Transparent background for ' '
                }
            }
            printf("%s", RESET_COLOR); // Reset color after each character segment
            if (num_str[i+1] != '\0') { // Don't add space after the last character
                printf(" "); // Small space between numbers for clarity
            }
        }
        printf("\n"); // Move to the next line of ASCII art
    }
    printf("%s", RESET_COLOR); // Ensure color is reset at the end of the entire number
}

int main(int argc, char *argv[]) {
    char input_buffer[256]; // Buffer for standard input
    int desired_width = 0;          // Default width (no right alignment)
    char *number_to_print = NULL; // Stores the number string from argument

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
            if (i + 1 < argc) {
                desired_width = atoi(argv[i+1]);
                if (desired_width <= 0) {
                    fprintf(stderr, "Error: Width must be a positive integer.\n");
                    return EXIT_FAILURE;
                }
                i++; // Skip the next argument as it's the width value
            } else {
                fprintf(stderr, "Error: -w or --width option requires a width value.\n");
                return EXIT_FAILURE;
            }
        } else if (number_to_print == NULL) { // First non-option argument is the number
            number_to_print = argv[i];
        } else {
            fprintf(stderr, "Error: Too many arguments or unrecognized option '%s'.\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (number_to_print != NULL) {
        // Input from command-line argument
        // Basic validation: ensure it's only digits and one decimal point
        int decimal_count = 0;
        for (int j = 0; number_to_print[j] != '\0'; j++) {
            if (isdigit(number_to_print[j])) {
                // Valid digit
            } else if (number_to_print[j] == '.') {
                decimal_count++;
                if (decimal_count > 1) {
                    fprintf(stderr, "Error: Multiple decimal points in '%s'. Only numbers and one decimal allowed.\n", number_to_print);
                    return EXIT_FAILURE;
                }
            } else {
                fprintf(stderr, "Error: Invalid character '%c' in '%s'. Only numbers and decimal points allowed.\n", number_to_print[j], number_to_print);
                return EXIT_FAILURE;
            }
        }
        print_number_ascii(number_to_print, desired_width);
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
                print_number_ascii(input_buffer, desired_width);
            }
        }
    }

    return EXIT_SUCCESS;
}