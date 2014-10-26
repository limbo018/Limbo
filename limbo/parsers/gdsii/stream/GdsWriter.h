
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <vector>

// Setting BYTESWAP to 1 is appropriate for big-endian Intel processors. 
// GDS format was originally used on little-endian, older computers.
#define BYTESWAP 1
#define BYTE unsigned char

#define BOOL  int
#define TRUE  1
#define FALSE 0

//extern BYTE  gdsswap;
//extern short gdsword;

#define SKIPOVER( fd, count )  { for ( i=0; i < ((count)-4); i+=2 ) read( (fd), &gdsword, 2 ); }
#define BAILOUT( message )     { printf( "\n\nERROR: %s\n\n", (message) ); fflush(stdout); exit(-1); }
#define WARNING( message )     { printf( "\n                            WARNING: %s\n\n", (message) ); fflush(stdout); }


#define MAX_FORWARD_REFS 1000

namespace GdsParser
{

struct gds_itemtype
{                                /* an item might be a polygon, path, aref, sref or text                      */
	int   type;                      /* 0 = polygon, 1 = path, 2 = aref, 3 = sref, 4 = text, 5 = box              */
	int   n;                         /* in the case of polygons or paths, this is the number of verticies         */
	/*     for text this is the number of characters in the string               */
	int   layer;                     /* layer                                                                     */
	int   dt;                        /* datatype                                                                  */ 
	int   cell_number;               /* index into the table of cells- relevant for sref and aref                 */
	double mag;                       /* magnification- relevant to sref, aref and text                            */
	double angle;                     /* the angle - relevant to sref and aref                                     */
	BOOL  abs_angle;                 /* from strans - normally false                                              */
	BOOL  abs_mag;                   /* from strans - normally false                                              */
	BOOL  reflect;                   /* from strans (reflect over x axis before rotating)                         */
	int   cols;			     /* Yes, many of these items are relevant to only one type of item, so        */
	int   rows;			     /* perhaps we should invent a different item type for each item, then        */
	int   col_pitch;		     /* string them together in a linked list of items.  Why not?                 */
	int   row_pitch;		     /* Because the "library" has to be a linked list of one "thing". What we     */
	int   col_pitchy;                /* An array's column pitch in y, which would create a diagonal array.        */
	int   row_pitchx;                /* An array's row pitch in x. Diagonal arrays are strange and useless.       */
	int   path_end;		     /* 0 = flush, 1 = round, 2 = extended. Default 0.                            */
	int   hor_present;		     /* The horizontal presentation for text.                                     */
	int   ver_present;		     /* The vertical presentation for text.                                       */
	int   font;			     /* Also relevant only for text.                                              */
	int   width;                     /* Relevant only to paths.                                                   */
	int  *x;                         /* array of x coordinates or possibly just the reference point X             */
	int  *y;                         /* array of y coordinates or possibly just the reference point Y             */
	char *text;                      /* Used only for strings. Such a waste.                                      */
	struct gds_itemtype *nextitem;       
};                               


struct gds_celltype                  /* A GDS library is a linked list of cells.                                  */
{                                /* A cell is a linked list of items.                                         */
	char *name;                      /* name of the cell                                                          */
	struct gds_itemtype *item;       /* one element of the cell                                                   */
	struct gds_celltype *nextcell;   /* pointer to the next cell, forming a linked list                           */  
};


struct GdsWriter
{
	int out; // output gds file descriptor
	BYTE  gdsswap;
	short gdsword;

	GdsWriter(const char* filename);
	~GdsWriter();

	/**************** high level interfaces *****************/
	// if has_last == true, it means the last point is the same as the first point 
	// otherwise, we need to add one point to the end 
	// default value is true 
	void write_boundary(int layer, int datatype, std::vector<int> const& vx, std::vector<int> const& vy, bool has_last = true);
	void write_box(int layer, int datatype, int xl, int yl, int xh, int yh);
	/**************** low level interfaces *****************/
	void gds_make_next_item( struct gds_itemtype **ci );
	void gds_bindump( BYTE x );            // dump one byte in binary format
	void gds_write_float( double x );
	void gds_swap4bytes( BYTE *four  );
	void gds_swap2bytes( BYTE *two );
	void gds_write_header(  );
	void gds_write_bgnlib(  );
	void gds_write_bgnstr(  );
	void gds_write_endlib(  );
	void gds_write_endstr(  );
	void gds_write_libname( const char *name );
	void gds_write_strname( const char *name );
	void gds_write_string( const char *s );
	void gds_write_sname( const char *s );
	void gds_write_boundary(  );
	void gds_write_box(  );
	void gds_write_boxtype( short int dt );
	void gds_write_path(  );
	void gds_write_sref(  );
	void gds_write_aref(  );
	void gds_write_text(  );
	void gds_write_endel(  );
	void gds_write_layer( short int layer );
	void gds_write_width( int width );
	void gds_write_datatype( short int dt );
	void gds_write_texttype( short int dt );
	void gds_write_generations( short int gens );
	void gds_write_pathtype( short int pt );
	void gds_write_presentation( int font, int vp, int hp );
	void gds_write_strans( BOOL reflect, BOOL abs_angle, BOOL abs_mag  );
	void gds_write_xy( const int *x, const int *y, int n, bool has_last = true);
	void gds_write_colrow( int ncols, int nrows );
	void gds_write_units( double dbu_uu, double dbu_m );
	void gds_write_mag( double mag );
	void gds_write_angle( double angle );
	void gds_create_lib( const char *libname, double dbu_um );    
	void gds_create_text( const char *str, int x, int y, int layer, int size );

	// add by Yibo Lin 
	// handle string with odd length 
	// generate new string output and return its length 
	char* gds_adjust_string(const char* input, int *output_length);
};

} // namespace GdsParser
