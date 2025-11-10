// png_to_cub3.c
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Usage: %s input.png output.cub3 threshold\n", argv[0]);
        printf("  threshold: 0 = no correction, 5 = normal, 10 = aggressive\n");
        return 1;
    }
    
    // Threshold değerini al
    int threshold = atoi(argv[3]);
    if (threshold < 0)
    {
        printf("Error: threshold must be >= 0\n");
        return 1;
    }
    
    int width, height, channels;
    unsigned char *data = stbi_load(argv[1], &width, &height, &channels, 4);
    
    if (!data)
    {
        printf("Error loading image!\n");
        return 1;
    }
    
    FILE *out = fopen(argv[2], "w");
    
    if (!out)
    {
        printf("Error opening output file!\n");
        stbi_image_free(data);
        return 1;
    }
    
    // .cub3 header yaz
    fprintf(out, ".cub3:%d:%d\n", width, height);
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int i = y * width + x;
            int idx = i * 4;
            
            // RGBA değerlerini al
            uint8_t r = data[idx + 0];
            uint8_t g = data[idx + 1];
            uint8_t b = data[idx + 2];
            uint8_t a = data[idx + 3];

            // Threshold uygula (0 ise atla)
            if (threshold > 0)
            {
                // Siyah threshold - çok koyu renkleri tam siyah yap
                if (r < threshold && g < threshold && b < threshold)
                {
                    r = 0;
                    g = 0;
                    b = 0;
                }
                // Beyaz threshold - çok açık renkleri tam beyaz yap
                else if (r >= (255 - threshold) && g >= (255 - threshold) && b >= (255 - threshold))
                {
                    r = 255;
                    g = 255;
                    b = 255;
                    a = 255;
                }
            }
            
            // 32-bit ARGB formatında birleştir
            unsigned int color = (a << 24) | (r << 16) | (g << 8) | b;
            
            fprintf(out, "0x%08x", color);
            
            // Satır sonu kontrolü
            if (x < width - 1)
                fprintf(out, ".");
            else
                fprintf(out, " \n");
        }
    }
    
    
    stbi_image_free(data);
    fclose(out);
    
    printf("✓ Converted %dx%d image to %s\n", width, height, argv[2]);
    printf("  Total pixels: %d\n", width * height);
    printf("  Threshold applied: %d\n", threshold);
    
    return 0;
}