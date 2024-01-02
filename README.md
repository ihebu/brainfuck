# Brainfuck interepreter

This is a simple and minimalist Brainfuck Interpreter written in C.


## What is B****fuck

[Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) is an [esoteric programming language](https://en.wikipedia.org/wiki/Esoteric_programming_languages) created in 1993 by Urban Müller.

Notable for its extreme minimalism, the language consists of only eight simple commands, a data pointer and an instruction pointer. While it is fully Turing complete, it is not intended for practical use, but to challenge and amuse programmers. Brainfuck requires one to break commands into microscopic steps.

The eight language commands each consist of a single character:

| Character | Meaning         |
|-----------|-----------------|
| >         | Increment the data pointer by one (to point to the next cell to the right) |
| <         | Decrement the data pointer by one (to point to the next cell to the left) |
| +         | Increment the byte at the data pointer by one |
| -         | Decrement the byte at the data pointer by one |
| .         | Output the byte at the data pointer |
| ,         | Accept one byte of input, storing its value in the byte at the data pointer |
| [         | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command |
| ]         | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command |


## Implementation conventions

1. The interepreter assumes that the user program is valid, and does not do perform error checks for the moment.
4. Memory consists of exactly 30000 cells
2. The values in each cell range from 0 to 255 inclusive.
3. Each cell wraps on overflows and underflows (e.g adding 1 to 255 will return 0)
5. Any character other than the ones in the table above, is considered a comment, and ignored


## Compilation

```bash
gcc -Wall -o brainfuck brainfuck.c
```

## Usage

1. Save a brainfuck program in a file, for example let's write this program and save it to `hello.bf`:

```brainfuck
+[-->-[>>+>-----<<]<--<---]>-.>>>+.>>..+++[.>]<<<<.+++.------.<<-.>>>>+.
```

2. Then simply run:

```bash
./brainfuck hello.bf
```

3. The output result should be: `Hello, World!`


## Other resources

- [brainfuck.org](https://brainfuck.org/) contains a list of cool brainfuck programs
- [Esolang wiki](https://esolangs.org/wiki/Brainfuck)
- [Brainfuck algorithms](https://esolangs.org/wiki/Brainfuck_algorithms)
