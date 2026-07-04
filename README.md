# dumbOS
It's an emulator of the dumb 8-64x00 processor.

`8` 8 registers, everyone contains number from 0 to 255.
`64` 64 KB of RAM.
`x00` Version in hexadecimal. The first.

# How to use:
Enter the write bootloader file from the cpu's folder.
In the code you'll see the program's array:
```c
uint8_t program[] = {}
```
There you can write your own code in hexadecimal for the dumb 8-64x00 CPU.
For example:
```
0x02 0x00 0x01
0x01 0x01 0x00
0x06 0x00 0x01
0x07
```
Makes register 0x00 be 0x01, and then makes register 0x01 be 0x01 too.
Then, it sums the number from 0x01 to register 0x00, and now 0x00 contains 0x02.
Finally, we stop the program with 0x07.

# Command instructions:
```
mov reg to reg         = 0x01, r1, r2
mov immediate to reg   = 0x02, r1, num
mov to reg from memory = 0x03, r1, address, offset
jmp address            = 0x04, address, offset
add reg to reg         = 0x06, r1, r2
hlt                    = 0x07 (WARNING, write 0x07 to finish the program)
```
(Note: In dumb 8-64x00 the instruction set is very short, so you can't load anything into RAM. Working with registers is all you can do.)

When the code is written, you can compile the first program named `write bootloader.c` on Linux:

1) Open the terminal in the cpu's directory and run:
```
gcc write\ bootloader.c -o write\ bootloader
```
(Note: You should have GCC installed.)

2) Run the compiled program:
```
./write\ bootloader
```
Then you should see a new file named `disk.bin`.

3) Compile `dumb 8-64x00.c` and run it:
```
gcc dumb\ 8-64x00.c -o dumb\ 8-64x00
./dumb\ 8-64x00
```

Then you'll see your program work. Under the hexadecimal code of your program you'll see the registers.
