/*==========================================================================
 * Project: atari cross assembler
 * File: directive.h
 *
 * Contains all assembly directives
 *==========================================================================
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *==========================================================================*/
#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#define NUM_DIR 31+8

/* Give names to the 'directives' entries */
#define DOT_BYTE 0
#define DOT_CBYTE 1
#define DOT_SBYTE 2
#define DOT_DBYTE 3
#define DOT_ELSE 4
#define DOT_END 5
#define DOT_ENDIF 6
#define DOT_ERROR 7
#define DOT_FLOAT 8
#define DOT_IF 9
#define DOT_INCLUDE 10
#define DOT_LOCAL 11
#define DOT_OPT 12
#define DOT_PAGE 13
#define DOT_SET 14
#define DOT_TAB 15
#define DOT_TITLE 16
#define DOT_WORD 17
#define DOT_STAR 18
#define DOT_ENDM 19
#define DOT_MACRO 20
#define DOT_DS 21
#define DOT_INCBIN 22
#define DOT_REPT 23
#define DOT_ENDR 24
#define DOT_WARN 25
#define DOT_DC 26
#define DOT_BANK 27
#define DOT_ALIGN 28
#define DOT_REGION_NAME 29
#define DOT_ELSEIF 30

// Extended the directives with some long jump hard coded macros
// JEQ, JNE, JPL, JMI, JCC, JCS, JVC, JVS
#define EX_JEQ 31
#define EX_JNE 32
#define EX_JPL 33
#define EX_JMI 34
#define EX_JCC 35
#define EX_JCS 36
#define EX_JVC 37
#define EX_JVS 38

char *direct[NUM_DIR]={".BYTE",".CBYTE",".SBYTE",".DBYTE",".ELSE",".END",".ENDIF",
		".ERROR",".FLOAT",".IF",".INCLUDE",".LOCAL",".OPT",".PAGE",
		".SET",".TAB",".TITLE",".WORD","*",".ENDM",".MACRO",".DS",
		".INCBIN",".REPT",".ENDR",".WARN",".DC",".BANK",".ALIGN", ".NAME",
        ".ELSEIF",
        // Long jumps
        "JEQ","JNE","JPL","JMI","JCC","JCS","JVC","JVS"
};

unsigned longJump2ShortOpcode[NUM_DIR] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0xF0,       // JEQ -> BEQ 
    0xD0,       // JNE -> BNE
    0x10,       // JPL -> BPL
    0x30,       // JMI -> BMI
    0x90,       // JCC -> BCC
    0xB0,       // JCS -> BCS
    0x50,       // JVC -> BVC
    0x70,       // JVS -> BVS
};

char* longJump2ShortOpcodeName[NUM_DIR] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    "BEQ",
    "BNE",
    "BPL",
    "BMI",
    "BCC",
    "BCS",
    "BVC",
    "BVS",
};

unsigned longJump2InverseOpcode[NUM_DIR] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0xD0,       // JEQ -> BNE 
    0xF0,       // JNE -> BEQ
    0x30,       // JPL -> BMI
    0x10,       // JMI -> BPL
    0xB0,       // JCC -> BCS
    0x90,       // JCS -> BCC
    0x70,       // JVC -> BVS
    0x50,       // JVS -> BVC
};

char* longJump2InverseOpcodeName[NUM_DIR] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    "BNE",
    "BEQ",
    "BMI",
    "BPL",
    "BCS",
    "BCC",
    "BVS",
    "BVC",
};

unsigned char ascii_to_screen[128] =
{
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
        0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
        0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
        0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
        0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
        0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
        0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f
};

#endif
