#!/usr/bin/env python3

import argparse
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

def reverse_bits(byte):
    return int('{:08b}'.format(byte)[::-1], 2)

def paint_glyph(img, draw, font, character, xoffset, yoffset, half=False) -> str:
    """
    Draws a character on an image and returns its representation in a pixel array.
    """
    ret = ""
    draw.rectangle((0,0,16,16), fill='#000000')  # Clears the image
    draw.fontmode = "1"
    draw.text((xoffset, yoffset), character, font=font, fill=(255,255,255))
    pixels = img.load()
    
    for y in range(12):
        b1 = 0
        b2 = 0
        s1 = ''
        s2 = ''
        for x in range(8):
            pt = pixels[x, y]
            pt1 = pixels[x + 8, y]
            if ((pt[0] + pt[1] + pt[2]) >= 100):
                b1 = b1 | (0x80 >> x)
                s1 += 'O'
            else:
                s1 += '.' 
            if (x < 4):
                if ((pt1[0] + pt1[1] + pt1[2]) >= 100):
                    b2 = b2 | (0x80 >> x)
                    s2 += 'O'
                else:
                    s2 += '.'
        b1 = reverse_bits(b1)
        b2 = reverse_bits(b2)
        if half:
            ret += '  0x%02x'%(b1)  + ', //  ' + s1[:6] +'\n'
        else:
            ret += '  0x%02x'%(b1) + ',0x%02x'%(b2) + ', //  ' + s1 + s2 +'\n'
    return ret

def generate_font_header(font_name, font_size, unicode_range, xoffset, yoffset, index, half=False):
    """
    Generates a header file containing a font table for the specified Unicode codepoints.
    """
    print("Processing:", font_name)
    
    img = Image.new('RGB', (16, 16), 0)
    font = ImageFont.truetype(font_name, font_size, index)
    draw = ImageDraw.Draw(img)
    
    output_path = Path(font_name).parent / (Path(font_name).stem + "_unicode.h")
    
    with open(output_path, "w", encoding="utf-8") as f:
        f.write("#pragma once\n\n")
        f.write("// Unicode font data\n")
        f.write("const char font_data[] = {\n")

        # Stores the mapping between codepoints and table index
        unicode_map = []
        glyph_count = 0

        for codepoint in unicode_range:
            char = chr(codepoint)
            try:
                font.getmask(char)  # Checks if the character is supported by the font
                unicode_map.append((codepoint, glyph_count))
                f.write(f"  // U+{codepoint:04X} '{char}'\n")
                f.write(paint_glyph(img, draw, font, char, xoffset, yoffset, half))
                glyph_count += 1
            except:
                pass  # Ignores unsupported characters

        f.write("};\n")

    print(f"Font header generated: {output_path}")

def main():
    parser = argparse.ArgumentParser(description="Convert a TTF font to a C header file using Unicode codepoints.")
    parser.add_argument("fontfile", type=str, help="Path to the TTF font file")
    parser.add_argument("--size", type=int, default=12, help="Font size (default: 12)")
    parser.add_argument("--range", type=str, default="32-127", help="Unicode range (default: ASCII 32-127)")
    parser.add_argument("--xoffset", type=int, default=0, help="X offset for character rendering")
    parser.add_argument("--yoffset", type=int, default=0, help="Y offset for character rendering")
    parser.add_argument("--index", type=int, default=0, help="Font face index")
    parser.add_argument("--half", type=bool, default=False, help="Use half-width characters")

    args = parser.parse_args()

    # Convert the Unicode range
    unicode_range = []
    for part in args.range.split(","):
        if "-" in part:
            start, end = map(lambda x: int(x, 0), part.split("-"))
            unicode_range.extend(range(start, end + 1))
        else:
            unicode_range.append(int(part))

    generate_font_header(args.fontfile, args.size, unicode_range, args.xoffset, args.yoffset, args.index, args.half)

if __name__ == "__main__":
    main()