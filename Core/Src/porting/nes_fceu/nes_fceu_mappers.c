#include <stdlib.h>
#include <string.h>
#include "nes_fceu_mappers.h"

#define MAPPER_ENTRY_SIZE 28
#define MAPPER_TABLE_FILE "/cores/mappers/mappers_table.bin"
#define MAPPER_PATH_PREFIX "/cores/mappers/mapper_"
#define MAPPER_PATH_SUFFIX ".bin"

int fceumm_get_mapper_name(uint16_t mapper_number, char *output, size_t output_size) {
    FILE *file = fopen(MAPPER_TABLE_FILE, "rb");
    if (!file) {
        return -1;
    }

    size_t offset = mapper_number * MAPPER_ENTRY_SIZE;

    if (fseek(file, offset, SEEK_SET) != 0) {
        fclose(file);
        return -1;
    }

    char buffer[MAPPER_ENTRY_SIZE] = {0};
    if (fread(buffer, 1, MAPPER_ENTRY_SIZE, file) != MAPPER_ENTRY_SIZE) {
        fclose(file);
        return -1;
    }

    fclose(file);

    buffer[strcspn(buffer, "\0")] = '\0'; // Truncate at first null byte
    if (snprintf(output, output_size, "/cores/mappers/mapper_%s.bin", buffer) >= (int)output_size) {
        return -1;
    }

    return 0;
}
