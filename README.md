# dumbOS
It's an emulator of dumb 8-64x00 processor. 

# How to use:
Enter the write bootloader file from cpu's folder.
In the code you'll see the program's arrow:
```c
uint8_t program[] = {}
```
There you can write your own code on hexadecimal for dumb 8-64x00 cpu.
For example:
```
0x02 0x00 0x01
0x01 0x01 0x00
0x06 0x00 0x01
0x07
```
Makes register 0x00 be 0x01, and then makes register 0x01 0x01 too. 
Then, he sum to register 0x00 the number from 0x01, and now 0x00 contains 0x02.
Finnaly we stop the program by 0x07.

# Command instuctions:
```
mov reg to reg         = 0x01, r1, r2
mov immediate to reg   = 0x02, r1, num
mov to reg from memory = 0x03, r1, address, offset
jmp address            = 0x04, address, offset
add reg to reg         = 0x06, r1, r2
hlt                    = 0x07 (WARNING, write 0x07 for finish the program)
```
