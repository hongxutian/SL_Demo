#ifndef _CODINGTABLE_H
#define _CODINGTABLE_H

const unsigned char CODE16X8[128][16]={
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",32*/
{0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCC,0x00,0x00,0x00,0x00},/*"!",33*/
{0x00,0x08,0x30,0x40,0x08,0x30,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",34*/
{0x00,0x02,0x03,0x1E,0x02,0x03,0x1E,0x00,0x00,0x20,0xFC,0x20,0x20,0xFC,0x20,0x00},/*"#",35*/
{0x00,0x0E,0x11,0x11,0x3F,0x10,0x0C,0x00,0x00,0x18,0x04,0x04,0xFF,0x84,0x78,0x00},/*"$",36*/
{0x0F,0x10,0x0F,0x01,0x06,0x18,0x00,0x00,0x00,0x8C,0x30,0xC0,0x78,0x84,0x78,0x00},/*"%",37*/
{0x00,0x0F,0x10,0x11,0x0E,0x00,0x00,0x00,0x78,0x84,0xC4,0x34,0x98,0xE4,0x84,0x08},/*"&",38*/
{0x00,0x48,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",39*/
{0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00},/*"(",40*/
{0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00},/*")",41*/
{0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00},/*"*",42*/
{0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xF0,0x80,0x80,0x80},/*"+",43*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x0E,0x00,0x00,0x00,0x00,0x00},/*",",44*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00},/*"-",45*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,0x00,0x00},/*".",46*/
{0x00,0x00,0x00,0x00,0x03,0x1C,0x20,0x00,0x00,0x06,0x18,0xE0,0x00,0x00,0x00,0x00},/*"/",47*/
{0x00,0x07,0x08,0x10,0x10,0x08,0x07,0x00,0x00,0xF0,0x08,0x04,0x04,0x08,0xF0,0x00},/*"0",48*/
{0x00,0x00,0x08,0x08,0x1F,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00},/*"1",49*/
{0x00,0x0E,0x10,0x10,0x10,0x10,0x0F,0x00,0x00,0x0C,0x14,0x24,0x44,0x84,0x0C,0x00},/*"2",50*/
{0x00,0x0C,0x10,0x10,0x10,0x11,0x0E,0x00,0x00,0x18,0x04,0x84,0x84,0x44,0x38,0x00},/*"3",51*/
{0x00,0x00,0x01,0x02,0x0C,0x1F,0x00,0x00,0x00,0x60,0xA0,0x24,0x24,0xFC,0x24,0x24},/*"4",52*/
{0x00,0x1F,0x11,0x11,0x11,0x10,0x10,0x00,0x00,0x98,0x04,0x04,0x04,0x88,0x70,0x00},/*"5",53*/
{0x00,0x07,0x08,0x11,0x11,0x09,0x00,0x00,0x00,0xF0,0x88,0x04,0x04,0x04,0xF8,0x00},/*"6",54*/
{0x00,0x18,0x10,0x10,0x11,0x16,0x18,0x00,0x00,0x00,0x00,0x7C,0x80,0x00,0x00,0x00},/*"7",55*/
{0x00,0x0E,0x11,0x10,0x10,0x11,0x0E,0x00,0x00,0x38,0x44,0x84,0x84,0x44,0x38,0x00},/*"8",56*/
{0x00,0x0F,0x10,0x10,0x10,0x08,0x07,0x00,0x00,0x80,0x48,0x44,0x44,0x88,0xF0,0x00},/*"9",57*/
{0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00},/*":",58*/
{0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00},/*";",59*/
{0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x00},/*"<",60*/
{0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00},/*"=",61*/
{0x00,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x80,0x00},/*">",62*/
{0x00,0x0E,0x12,0x10,0x10,0x11,0x0E,0x00,0x00,0x00,0x00,0x0C,0xEC,0x00,0x00,0x00},/*"?",63*/
{0x03,0x0C,0x13,0x14,0x17,0x08,0x07,0x00,0xE0,0x18,0xE4,0x14,0xF4,0x14,0xE8,0x00},/*"@",64*/
{0x00,0x00,0x03,0x1C,0x07,0x00,0x00,0x00,0x04,0x3C,0xC4,0x40,0x40,0xE4,0x1C,0x04},/*"A",65*/
{0x10,0x1F,0x11,0x11,0x11,0x0E,0x00,0x00,0x04,0xFC,0x04,0x04,0x04,0x88,0x70,0x00},/*"B",66*/
{0x03,0x0C,0x10,0x10,0x10,0x10,0x1C,0x00,0xE0,0x18,0x04,0x04,0x04,0x08,0x10,0x00},/*"C",67*/
{0x10,0x1F,0x10,0x10,0x10,0x08,0x07,0x00,0x04,0xFC,0x04,0x04,0x04,0x08,0xF0,0x00},/*"D",68*/
{0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x04,0xFC,0x04,0x04,0xC4,0x04,0x18,0x00},/*"E",69*/
{0x10,0x1F,0x11,0x11,0x17,0x10,0x08,0x00,0x04,0xFC,0x04,0x00,0xC0,0x00,0x00,0x00},/*"F",70*/
{0x03,0x0C,0x10,0x10,0x10,0x1C,0x00,0x00,0xE0,0x18,0x04,0x04,0x44,0x78,0x40,0x00},/*"G",71*/
{0x10,0x1F,0x10,0x00,0x00,0x10,0x1F,0x10,0x04,0xFC,0x84,0x80,0x80,0x84,0xFC,0x04},/*"H",72*/
{0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"I",73*/
{0x00,0x00,0x10,0x10,0x1F,0x10,0x10,0x00,0x03,0x01,0x01,0x01,0xFE,0x00,0x00,0x00},/*"J",74*/
{0x10,0x1F,0x11,0x03,0x14,0x18,0x10,0x00,0x04,0xFC,0x04,0x80,0x64,0x1C,0x04,0x00},/*"K",75*/
{0x10,0x1F,0x10,0x00,0x00,0x00,0x00,0x00,0x04,0xFC,0x04,0x04,0x04,0x04,0x0C,0x00},/*"L",76*/
{0x10,0x1F,0x1F,0x00,0x1F,0x1F,0x10,0x00,0x04,0xFC,0x80,0x7C,0x80,0xFC,0x04,0x00},/*"M",77*/
{0x10,0x1F,0x0C,0x03,0x00,0x10,0x1F,0x10,0x04,0xFC,0x04,0x00,0xE0,0x18,0xFC,0x00},/*"N",78*/
{0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0xF0,0x00},/*"O",79*/
{0x10,0x1F,0x10,0x10,0x10,0x10,0x0F,0x00,0x04,0xFC,0x84,0x80,0x80,0x80,0x00,0x00},/*"P",80*/
{0x07,0x08,0x10,0x10,0x10,0x08,0x07,0x00,0xF0,0x08,0x14,0x14,0x0C,0x0A,0xF2,0x00},/*"Q",81*/
{0x10,0x1F,0x11,0x11,0x11,0x11,0x0E,0x00,0x04,0xFC,0x04,0x00,0xC0,0x30,0x0C,0x04},/*"R",82*/
{0x00,0x0E,0x11,0x10,0x10,0x10,0x1C,0x00,0x00,0x1C,0x04,0x84,0x84,0x44,0x38,0x00},/*"S",83*/
{0x18,0x10,0x10,0x1F,0x10,0x10,0x18,0x00,0x00,0x00,0x04,0xFC,0x04,0x00,0x00,0x00},/*"T",84*/
{0x10,0x1F,0x10,0x00,0x00,0x10,0x1F,0x10,0x00,0xF8,0x04,0x04,0x04,0x04,0xF8,0x00},/*"U",85*/
{0x10,0x1E,0x11,0x00,0x00,0x13,0x1C,0x10,0x00,0x00,0xE0,0x1C,0x70,0x80,0x00,0x00},/*"V",86*/
{0x10,0x1F,0x00,0x1F,0x00,0x1F,0x10,0x00,0x00,0xC0,0x7C,0x80,0x7C,0xC0,0x00,0x00},/*"W",87*/
{0x10,0x18,0x16,0x01,0x01,0x16,0x18,0x10,0x04,0x0C,0x34,0xC0,0xC0,0x34,0x0C,0x04},/*"X",88*/
{0x10,0x1C,0x13,0x00,0x13,0x1C,0x10,0x00,0x00,0x00,0x04,0xFC,0x04,0x00,0x00,0x00},/*"Y",89*/
{0x08,0x10,0x10,0x10,0x13,0x1C,0x10,0x00,0x04,0x1C,0x64,0x84,0x04,0x04,0x18,0x00},/*"Z",90*/
{0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00},/*"[",91*/
{0x00,0x20,0x1C,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x1C,0x03,0x00},/*"\",92*/
{0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00},/*"]",93*/
{0x00,0x00,0x20,0x40,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",94*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},/*"_",95*/
{0x00,0x40,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",96*/
{0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x98,0x24,0x24,0x48,0xFC,0x04,0x00},/*"a",97*/
{0x08,0x0F,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0xFC,0x88,0x04,0x04,0x88,0x70,0x00},/*"b",98*/
{0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x70,0x88,0x04,0x04,0x04,0x88,0x00},/*"c",99*/
{0x00,0x00,0x01,0x01,0x01,0x09,0x0F,0x00,0x00,0xF8,0x04,0x04,0x04,0x08,0xFC,0x04},/*"d",100*/
{0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0xF8,0x24,0x24,0x24,0x24,0xE8,0x00},/*"e",101*/
{0x00,0x01,0x01,0x07,0x09,0x09,0x04,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"f",102*/
{0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0xD6,0x29,0x29,0x29,0xC9,0x06,0x00},/*"g",103*/
{0x08,0x0F,0x00,0x01,0x01,0x01,0x00,0x00,0x04,0xFC,0x84,0x00,0x00,0x04,0xFC,0x04},/*"h",104*/
{0x00,0x01,0x19,0x19,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"i",105*/
{0x00,0x00,0x00,0x01,0x19,0x19,0x00,0x00,0x00,0x03,0x01,0x01,0x01,0xFE,0x00,0x00},/*"j",106*/
{0x08,0x0F,0x00,0x00,0x01,0x01,0x01,0x00,0x04,0xFC,0x24,0x60,0x94,0x0C,0x04,0x00},/*"k",107*/
{0x00,0x08,0x08,0x1F,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00},/*"l",108*/
{0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x04,0xFC,0x04,0x00,0xFC,0x04,0x00,0xFC},/*"m",109*/
{0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x00,0x04,0xFC,0x84,0x00,0x00,0x04,0xFC,0x04},/*"n",110*/
{0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0xF8,0x04,0x04,0x04,0x04,0xF8,0x00},/*"o",111*/
{0x01,0x01,0x00,0x01,0x01,0x00,0x00,0x00,0x01,0xFF,0x89,0x04,0x04,0x88,0x70,0x00},/*"p",112*/
{0x00,0x00,0x00,0x01,0x01,0x00,0x01,0x00,0x00,0x70,0x88,0x04,0x04,0x89,0xFF,0x01},/*"q",113*/
{0x01,0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x04,0x04,0xFC,0x84,0x04,0x00,0x80,0x00},/*"r",114*/
{0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0xCC,0x24,0x24,0x24,0x24,0x98,0x00},/*"s",115*/
{0x00,0x01,0x01,0x07,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0xF8,0x04,0x04,0x08,0x00},/*"t",116*/
{0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0xF8,0x04,0x04,0x04,0x08,0xFC,0x04},/*"u",117*/
{0x01,0x01,0x01,0x00,0x01,0x01,0x01,0x00,0x00,0xC0,0x30,0x0C,0x30,0xC0,0x00,0x00},/*"v",118*/
{0x01,0x01,0x00,0x01,0x01,0x00,0x01,0x01,0x80,0x70,0x0C,0x30,0xE0,0x1C,0x60,0x80},/*"w",119*/
{0x00,0x01,0x01,0x01,0x00,0x01,0x01,0x00,0x00,0x04,0x8C,0x70,0x74,0x8C,0x04,0x00},/*"x",120*/
{0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x00,0x81,0x61,0x1E,0x18,0x60,0x80,0x00},/*"y",121*/
{0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x84,0x0C,0x34,0x44,0x84,0x0C,0x00},/*"z",122*/
{0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02},/*"{",123*/
{0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00},/*"|",124*/
{0x40,0x40,0x3F,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00},/*"}",125*/
{0x00,0x40,0x80,0x40,0x40,0x20,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",126*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"",127*/
};

const unsigned char TRANTAB[]=
{
	0x00,0x80,0x40,0xc0,0x20,0xa0,0x60,0xe0,0x10,0x90,0x50,0xd0,0x30,0xb0,0x70,0xf0,
	0x08,0x88,0x48,0xc8,0x28,0xa8,0x68,0xe8,0x18,0x98,0x58,0xd8,0x38,0xb8,0x78,0xf8,
	0x04,0x84,0x44,0xc4,0x24,0xa4,0x64,0xe4,0x14,0x94,0x54,0xd4,0x34,0xb4,0x74,0xf4,
	0x0c,0x8c,0x4c,0xcc,0x2c,0xac,0x6c,0xec,0x1c,0x9c,0x5c,0xdc,0x3c,0xbc,0x7c,0xfc,
	0x02,0x82,0x42,0xc2,0x22,0xa2,0x62,0xe2,0x12,0x92,0x52,0xd2,0x32,0xb2,0x72,0xf2,
	0x0a,0x8a,0x4a,0xca,0x2a,0xaa,0x6a,0xea,0x1a,0x9a,0x5a,0xda,0x3a,0xba,0x7a,0xfa,
	0x06,0x86,0x46,0xc6,0x26,0xa6,0x66,0xe6,0x16,0x96,0x56,0xd6,0x36,0xb6,0x76,0xf6,
	0x0e,0x8e,0x4e,0xce,0x2e,0xae,0x6e,0xee,0x1e,0x9e,0x5e,0xde,0x3e,0xbe,0x7e,0xfe,
	0x01,0x81,0x41,0xc1,0x21,0xa1,0x61,0xe1,0x11,0x91,0x51,0xd1,0x31,0xb1,0x71,0xf1,
	0x09,0x89,0x49,0xc9,0x29,0xa9,0x69,0xe9,0x19,0x99,0x59,0xd9,0x39,0xb9,0x79,0xf9,
	0x05,0x85,0x45,0xc5,0x25,0xa5,0x65,0xe5,0x15,0x95,0x55,0xd5,0x35,0xb5,0x75,0xf5,
	0x0d,0x8d,0x4d,0xcd,0x2d,0xad,0x6d,0xed,0x1d,0x9d,0x5d,0xdd,0x3d,0xbd,0x7d,0xfd,
	0x03,0x83,0x43,0xc3,0x23,0xa3,0x63,0xe3,0x13,0x93,0x53,0xd3,0x33,0xb3,0x73,0xf3,
	0x0b,0x8b,0x4b,0xcb,0x2b,0xab,0x6b,0xeb,0x1b,0x9b,0x5b,0xdb,0x3b,0xbb,0x7b,0xfb,
	0x07,0x87,0x47,0xc7,0x27,0xa7,0x67,0xe7,0x17,0x97,0x57,0xd7,0x37,0xb7,0x77,0xf7,
	0x0f,0x8f,0x4f,0xcf,0x2f,0xaf,0x6f,0xef,0x1f,0x9f,0x5f,0xdf,0x3f,0xbf,0x7f,0xff
};

const unsigned char PIKAQIU[]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x10,0x67,0x7C,0x2F,0x31,0x54,0x1B,0x6A,0x15,0x16,0x0B,0x03,0x02,0x01,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x90,0x38,0xCE,0x72,0x1D,0x66,0x0B,0xCD,0x62,
0xB1,0xC1,0xB6,0x5A,0x6D,0x36,0x1B,0x01,0x03,0x02,0x02,0x0A,0x1E,0x16,0x06,0x16,0x06,0x06,0x06,0x0A,0x1A,0x03,0x09,0x03,
0x1A,0x16,0x04,0x3D,0x0E,0x0A,0x1A,0x55,0xD4,0xB5,0x38,0x2A,0xAA,0x25,0x2D,0x2B,0x2A,0xA6,0x25,0x2A,0x3A,0x34,0x68,0x50,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xC0,0x70,0xB0,0xD0,0x6F,0xB0,0x7F,0xDC,0x65,0x5B,0x17,0x17,0x1B,0x8F,0x0E,0x07,0x00,0x81,0x00,0x00,
0x00,0x80,0x02,0x84,0x8B,0x47,0x47,0x96,0xD3,0x64,0x38,0xBE,0xA3,0xAB,0x26,0x75,0x4D,0x4A,0xDA,0xB4,0xA4,0xEC,0x50,0xD0,
0x98,0xEC,0x32,0x5C,0x66,0x1B,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x31,0x8E,0x7F,0xEF,0x11,0x94,0xD1,0xEF,0xE0,
0xEE,0xCC,0x2C,0xAF,0xEB,0x68,0x4A,0xE9,0x68,0x0F,0x0E,0x29,0xD4,0xCC,0xEF,0xC0,0xDF,0x11,0x32,0x11,0xEF,0x7F,0x81,0x8F,
0x8D,0x01,0x05,0x06,0x00,0x01,0x01,0x01,0x00,0x02,0x02,0xC0,0x61,0x91,0xED,0x33,0x1F,0x26,0x09,0x07,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x71,0x6E,0xDB,0xB5,0xA8,
0x2B,0xE8,0xC0,0xE0,0xB4,0x98,0x58,0xC6,0x80,0x00,0xE0,0x20,0xD8,0x68,0xA0,0xA0,0x60,0xD0,0x30,0xC0,0x00,0x00,0x00,0x80,
0x40,0xA0,0xA0,0x40,0xE2,0xB3,0x62,0x45,0x9B,0x96,0xED,0xDB,0x76,0x6E,0x40,0x50,0xC0,0xF0,0xB0,0x80,0x80,0x00,0x00,0x40,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x80,0x60,0xB0,0xD0,0x60,0xA0,0x3F,0x5F,0x20,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0xE0,0xFF,0xED,0xBB,0x86,0xCC,0x7B,0x1C,0x14,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0xFF,0xFF,0x00,0x09,0x01,0x01,
0x01,0x01,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x10,0xC0,0x7F,0xFC,0x80,0x40,
0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xE0,0x50,0x80,0xE8,0x28,0xA8,0x30,0xB0,0xB0,0xB0,0xB0,0xA8,0x28,0x68,0x60,0x68,0x68,0x68,0x68,0x68,0x68,0xE8,0x70,0x70,
0xB0,0xB8,0x28,0x68,0xC0,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00/*"C:\Users\hongxu\Desktop\pkq.bmp",0*/
};

#endif

