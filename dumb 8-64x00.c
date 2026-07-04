#include <stdio.h>
#include <stdint.h>

uint8_t RAM[65536]; //64 KB
uint8_t rgster[8]; // 8 registers

void print_exit_status();
int regs_check(uint8_t reg);



int main()
{
    uint16_t PC = 0;

    // Read bootloader form disk and write it to RAM
    FILE *disk = fopen("disk.bin", "rb");
    
    if (!disk) {printf("No disk found!\n"); return 1;}

    size_t bytes_read = fread(&RAM[0x7C00], 1, 512, disk);
    printf("Readed %zu bytes from disk.\n", bytes_read);
    printf("Success writing bootloader to RAM.\n\n");
    PC = 0x7C00;
    fclose(disk);
    ////////////////////////////////////////////////
    
    // Print the content
    uint16_t bootloader_end = PC + bytes_read;
    printf("Bootloader: \n");
    for (int i = PC; i < bootloader_end; i++) {
        printf("0x%02x ", RAM[i]);
    }
    printf("\n");
    ////////////////////

    while (1)
    {
        if (PC >= sizeof(RAM)) 
        {
            printf("\nError, PC is out of RAM.\n");
            return 1;
        }

        uint8_t opcode = RAM[PC];
        switch (opcode)
        {
            //*Command instuctions:
            // mov reg to reg         = 0x01, r1, r2
            // mov immediate to reg   = 0x02, r1, num
            // mov to reg from memory = 0x03, r1, address, offset
            // jmp address            = 0x04, address, offset
            // add reg to reg         = 0x06, r1, r2
            // hlt                    = 0x07 (WARNING, write 0x07 for finish the program)
            // *//
            
            case 0x01:
            {
                PC++;
                uint8_t r1 = RAM[PC];
                if (regs_check(r1)) return 1;
                PC++;
                uint8_t r2 = RAM[PC];
                if (regs_check(r2)) return 1;

                rgster[r1] = rgster[r2];
                break;
            }
            
            case 0x02:
            {
                PC++;
                uint8_t reg = RAM[PC];
                if (regs_check(reg)) return 1;
                PC++;
                uint8_t num = RAM[PC];

                rgster[reg] = num;
                break;
            }

            case 0x03:
            {
                PC ++;
                uint8_t reg = RAM[PC];
                if (regs_check(reg)) return 1;
                PC ++;
                uint8_t address = RAM[PC];
                PC++;
                uint8_t offset = RAM[PC];

                rgster[reg] = RAM[address*256+offset];
                
                break;
            }

            case 0x04:
            {
                PC ++;
                uint8_t address = RAM[PC];
                PC++;
                uint8_t offset = RAM[PC];

                PC = address*256+offset;
                continue;
                break;
            }

            case 0x06:
            {
                PC ++;
                uint8_t r1 = RAM[PC];
                if (regs_check(r1)) return 1;
                PC ++;
                uint8_t r2 = RAM[PC];
                if (regs_check(r2)) return 1;

                rgster[r1] += rgster[r2];
                break;
            }
            
            case 0x07:
            {
                print_exit_status();
                return 0;
            }

            case 0x00: break;

            default:
            {
                printf("\nSorry, the programmer is dumb, he doesnt know how to write code well.\nI DONT KNOW HOW TO READ YOUR CODE.\n\n");
                return 1;
            }
        }
        PC++;
    }
    
}

void print_exit_status()
{
    printf("\n\nRAM:\n");
    for (int i = 0; i < sizeof(rgster); i++)
    {
        printf("%d = 0x%02x\n", i, rgster[i]);
    }
}

int regs_check(uint8_t reg)
{
    if (reg >= sizeof(rgster))
    {
        printf("\nYou want to contact with register %02x but I have only %zu registers\nAre you good?\n\n", reg, sizeof(rgster));
        return 1;
    } else return 0;
}