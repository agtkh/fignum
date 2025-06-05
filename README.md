# fignum

fignum is a command-line utility written in C that displays sequences of numbers as large, easy-to-read ASCII art, similar to `figlet` but specialized for numerical output. It supports integers and decimal numbers, but not text or other characters.

![screenshot01](ss01.png)

## Features

  * **Numerical Focus:** Designed specifically for rendering numbers as ASCII art.
  * **Decimal Support:** Handles numbers with decimal points.
  * **Flexible Input:** Accepts input via command-line arguments or standard input.
  * **`figlet`-like Output:** Provides large, clear ASCII art representations of numbers.
  * **Right Alignment:** Align numbers to the right within a specified **digit width**.

-----

## Installation

To compile `fignum`, you will need a C compiler (like GCC) and `make`.

1.  **Clone the repository (or download the source code):**
    ```bash
    git clone https://github.com/agtkh/fignum.git
    cd fignum
    ```
2.  **Compile using `make`:**
    ```bash
    make
    ```
    This will create an executable named `fignum` in the current directory.

-----

## Usage

You can use `fignum` by providing numbers as command-line arguments or by piping them through standard input.

### Basic Usage

To display numbers directly, pass them as arguments to the `fignum` command:

```bash
./fignum 12345
./fignum 3.14159
```

### Using Standard Input

You can also pipe numbers to `fignum`:

```bash
echo "98765" | ./fignum
cat numbers.txt | ./fignum # Assuming numbers.txt contains numbers, one per line
```

### Right Alignment with `--width` or `-w`

Use the `--width` or `-w` option followed by a positive integer to specify the desired **total number of digits** for right alignment. The number will be padded with spaces on the left if its actual digit count is less than the specified width.

```bash
# Display "123" right-aligned within a 10-digit width
./fignum -w 10 123

# Display "3.14" right-aligned within an 8-digit width (3.14 is 4 digits)
./fignum --width 8 3.14

# With standard input
echo "456.7" | ./fignum -w 12
```

-----

## Author

K. Agata

## License

This program is licensed under the MIT License. See the `LICENSE` file for more details.
