# Stegtool - Simple steganography tool

## Encode and decode text hidden in bmp files



Afte having fun with the Filter problem in the CS50X I decided to make my own program to manipulate bmp image files.

:warning: **Warning:** This tool is **not** encryption, don't use for sensitive data!

Writing this was good practice writing a parser and learning to read data from a file.

Requires 24-bit uncompressed bmp files

---

## Using the tool

### To encode:

#### Arguments:
1. Program name
1. Input image
1. String to encode

***e.g.*** ./steg test.bmp "test message"

The program will produce output file: **output.bmp** Note that all text is converted to upper case and only very limited punctuation is supported.

### To decode:

#### Arguments:
1. Program name
1. Input image

***e.g.*** ./steg output.bmp

The program will decode any hidden message. If the output is less than 500 characters, the output will be displayed in the terminal. Output larger than 500 chars will be written to output.txt.

---

## Screenshots

![Encoded "hello world."](./images/helloworld.png)

An example of "Hello World." encoded on a tiny 16 x 16 pixel image.

---

## To do

- expanded punctuation set
- improved argument parsing
- selectable encoding density
- txt file message input
