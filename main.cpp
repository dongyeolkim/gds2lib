#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define LAYER 0x01
#define PLEX 0x02
#define DATATYPE 0x03
#define ELFLAGS 0x04
#define BGNEXTN 0x15
#define ENDEXTN 0x16
#define WIDTH 0x17
#define STRANS 0x18
#define MAG 0x19
#define ANGLE 0x1a
#define PRESENTATION 0x1b
#define NODETYPE 0x1c
#define BOXTYPE 0x1d
#define ROW 0x1e
#define COL 0x1f


#define BOUNDARY 0x05
#define TEXT 0x06
#define TEXTTYPE 0x07
#define PATHTYPE 0x09
#define STRING 0x08
#define PATH 0x10
#define SREF 0x11
#define AREF 0x12
#define NODE 0x13
#define BOX 0x14



#define DEBUG 0x00
#define MOREDEBUG 0x01
#include"global.hpp"
#include"classes.hpp"
#include"functions.hpp"
#include"gdsfunction.hpp"

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Usage: gdsread gdsfilename\n");
		exit(1);
	}
	class gds2 mygds(argv[1]);
	if(DEBUG) printf("Completed building\n");
	//mygds.printstructurenames();
	mygds.displayall();
	mygds.writegds2("newgds.gds2");
	return(0);
}
