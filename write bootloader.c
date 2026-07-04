#include <stdio.h>
#include <stdint.h>

// You can change the program to write your code on dumb 8-64x00
uint8_t program[] = 
    {
        0x00
    };

int main()
{
    
    size_t size = sizeof(program); 
    
    // Open the disk and write to it the code
    FILE *disk_file = fopen("disk.bin", "wb");

    if (disk_file == NULL) {
        perror("File cant be open");
        return 1;
    }
    
    size_t written;
    
    if (size < 512)
    {
        uint8_t disk[512];
        for (int i = 0; i < 512; i++)
        {
            if (i < size) disk[i] = program[i];
            else disk[i] = 0x00;
            printf("0x%02x ", disk[i]);
        }
        printf("\n\n");
        written = fwrite(disk, 1, 512, disk_file);
    }
    else written = fwrite(program, 1, size, disk_file);
    
    if (written != size) {
        perror("Written error.");
        fclose(disk_file);
        return 1;
    }
    
    fclose(disk_file);

    printf("Writed %zu bytes to disk.bin\n", written);

    return 0;
}