# Stegtool - Simple steganography tool

## Encode and decode text hidden in bmp files

----

Afte having fun with the Filter problem in the CS50X I decided to make my own program to manipulate bmp image files.

:warning: **Warning:** This tool is **not** encryption, don't use for sensitive data!

Writing this was good practice writing a parser and learning to read data from a file.

Requires 24-bit uncompressed bmp files

---

### To encode:

#### Arguments:
1. Program name
1. Input image
1. String to encode

***e.g.*** ./steg test.bmp "test message"

The program will produce output file: **output.bmp**

### To decode:

#### Arguments:
1. Program name
1. Input image

***e.g.*** ./steg output.bmp

The program will decode any hidden message. If the output is less than 500 characters, the output will be displayed in the terminal. Output larger than 500 chars will be written to output.txt.
