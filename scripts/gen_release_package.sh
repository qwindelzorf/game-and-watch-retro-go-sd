#!/bin/bash

# Input files
FIRMWARE="release/firmware_update.bin"
GW_UPDATE="release/gw_update.tar"

# Output file
COMBINED="release/retro-go_update.bin"

# Target size for firmware_update.bin (1024 KB = 1 MB)
TARGET_SIZE=$((1024 * 1024))

# Check if both input files exist
if [[ ! -f "$FIRMWARE" || ! -f "$GW_UPDATE" ]]; then
    echo "Error: One or both input files are missing!"
    exit 1
fi

# Get the current size of firmware_update.bin
if [[ "$OSTYPE" == "darwin"* ]]; then
    CURRENT_SIZE=$(stat -f%z "$FIRMWARE")
else
    CURRENT_SIZE=$(stat -c%s "$FIRMWARE")
fi

# Check if firmware_update.bin exceeds the target size
if [[ "$CURRENT_SIZE" -gt "$TARGET_SIZE" ]]; then
    echo "Error: $FIRMWARE exceeds 1024 KB!"
    exit 1
fi

# Create a temporary file filled with zeros to pad firmware_update.bin
PADDING_FILE=$(mktemp)
dd if=/dev/zero bs=1 count=$((TARGET_SIZE - CURRENT_SIZE)) of="$PADDING_FILE" 2>/dev/null

# Write the size of firmware_update.bin as a 4-byte little-endian value
SIZE_FILE=$(mktemp)
printf "%08x" "$CURRENT_SIZE" | sed 's/../& /g' | awk '{print $4 $3 $2 $1}' | xxd -r -p > "$SIZE_FILE"

# Concatenate firmware_update.bin (with padding) and gw_update.tar into the output file
cat "$FIRMWARE" "$PADDING_FILE" "$SIZE_FILE" "$GW_UPDATE" > "$COMBINED"

# Clean up the temporary padding file
rm "$PADDING_FILE" "$SIZE_FILE"