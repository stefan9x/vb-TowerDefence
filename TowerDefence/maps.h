#pragma once

#define SIZEROW 15
#define SIZECOLUMN 20

char map1[SIZEROW][SIZECOLUMN] = {
	{ 'G','G','D','G','G','G','G','G','G','G','G','G','B','B','G','G','G','G','G','O' },
	{ 'G','G','D','G','G','G','G','G','G','G','G','G','B','B','1','2','3','G','G','t' },
	{ 'G','G','D','G','G','G','D','D','D','G','G','G','G','G','4','5','6','G','G','G' },
	{ 'G','G','D','G','G','G','D','S','D','G','G','G','G','G','G','G','G','G','G','G' },
	{ 'G','G','D','G','G','G','D','G','D','G','G','G','G','G','G','G','G','G','G','G' },
	{ 'G','G','D','X','G','S','D','G','D','G','G','G','G','G','G','G','G','S','G','7' },
	{ 'G','G','D','D','D','D','D','G','D','G','G','G','G','D','D','D','D','D','D','D' },
	{ 'G','G','G','G','G','G','G','G','D','G','G','G','G','D','S','G','G','G','G','7' },
	{ 'G','G','G','G','G','G','G','G','D','G','G','G','G','D','G','G','G','G','G','G' },
	{ 'G','G','G','G','G','G','G','G','D','G','G','G','G','D','G','G','G','G','G','G' },
	{ 'B','G','G','G','G','G','G','G','D','S','G','G','S','D','G','G','G','G','G','G' },
	{ 'B','B','B','G','G','G','G','G','D','D','D','D','D','D','G','G','G','G','G','B' },
	{ 'B','B','B','G','G','G','G','G','G','G','G','G','G','G','G','G','B','G','B','B' },
	{ 'B','B','B','B','B','G','G','G','G','G','G','G','G','G','G','G','B','B','B','B' },
	{ 'B','B','B','B','B','G','G','G','G','G','G','G','G','G','G','G','B','B','B','B' },
};

unsigned char gameOver[SIZEROW][SIZECOLUMN] = {
	{ 'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D' },
	{ 'D',0,0,0,0,'D',0,0,0,'D',0,'D','D','D',0,'D',0,0,0,'D' },
	{ 'D',0,'D','D',0,'D',0,'D',0,'D',0,0,'D',0,0,'D',0,'D','D','D' },
	{ 'D',0,'D','D','D','D',0,'D',0,'D',0,'D',0,'D',0,'D',0,'D','D','D' },
	{ 'D',0,'D',0,0,'D',0,0,0,'D',0,'D',0,'D',0,'D',0,0,'D','D' },
	{ 'D',0,'D','D',0,'D',0,'D',0,'D',0,'D','D','D',0,'D',0,'D','D','D' },
	{ 'D',0,0,0,0,'D',0,'D',0,'D',0,'D','D','D',0,'D',0,0,0,'D' },
	{ 'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D' },
	{ 'D','D',0,0,0,0,'D',0,'D',0,'D',0,0,0,'D',0,0,0,'D','D' },
	{ 'D','D',0,'D','D',0,'D',0,'D',0,'D',0,'D','D','D',0,'D',0,'D','D' },
	{ 'D','D',0,'D','D',0,'D',0,'D',0,'D',0,'D','D','D',0,'D',0,'D','D' },
	{ 'D','D',0,'D','D',0,'D',0,'D',0,'D',0,0,'D','D',0,0,0,'D','D' },
	{ 'D','D',0,'D','D',0,'D',0,'D',0,'D',0,'D','D','D',0,0,'D','D','D' },
	{ 'D','D',0,0,0,0,'D','D',0,'D','D',0,0,0,'D',0,'D',0,'D','D' },
	{ 'D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D','D' },
};

bool mapChanges[SIZEROW][SIZECOLUMN] = {
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },
	{ true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true },

};