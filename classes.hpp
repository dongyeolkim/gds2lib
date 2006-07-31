class structure
{
	public:
		signed int version,year,month,day,hour,minute,second;
		signed int myear,mmonth,mday,mhour,mminute,msecond;
		char *structurename;
		class elementlist *elems;
		class structure *next;
};

class structures
{
	private:
		class structure *head;
		class structure *current;
	public:
		structures(void);
		class structure *newnode(void);
		void dispname(void);
		void displayelements(void);
};

struct header{
       unsigned char record_length[2];
       unsigned char record_type;
       unsigned char data_type;
};

class gds2
{
	private:
		unsigned int version,year,month,day,hour,minute,second;
		unsigned int myear,mmonth,mday,mhour,mminute,msecond;
		int data_size,generations;
		char *libname;
		double units,unitsinm;

		class structures *structurelist;
		class structure *currentstru;
		class elements *currentelems;

		int size,rtype,dtype;
        struct header *head;
		FILE *fp;

		int get_record_data(void);
		unsigned int get_unsigned_int(void);
		unsigned int get_unsigned_4int(void);
		double get_real_8(void);

	public:
		gds2(const char *fname);
		void printstructurenames(void);
		void displayall(void);
		void writegds2(char *gds2filename);
};

class pointnode
{
	public:
		int x,y;
		class pointnode *next;
};

class pointlist
{
	private:
		class pointnode *current;
		class pointnode *head;
	public:
		pointlist(void);
		class pointnode *newnode(int x,int y);
		void display(void);
};

class element
{
	public:
		virtual void set(int prop,unsigned int value)=0;
		virtual void set(int prop,signed int value)=0;
		virtual void set(int prop,double value)=0;
		virtual void set(int prop,char *value)=0;
		virtual void display(void)=0;
};

class elements
{
	public:
		class pointlist *plist;
		class element *elem;
		class elements *next;
};

class elementlist
{
	private:
		class elements *head;
		class elements *current;
	public:
		elementlist(void);
		class elements *newnode(int obj);
		void displayelements(void);
};

class boundary:public element
{
	private:
		unsigned int elflags;
		unsigned int plex;
		unsigned int layer;
		unsigned int datatype;
	public:
		void set(int prop,unsigned int value);
		void set(int prop,signed int value){};
		void set(int prop,double value){};
		void set(int prop,char *value){};
		void display(void);
};

class text:public element
{
	private:
		unsigned int elflags;
		unsigned int plex;
		unsigned int layer;
		unsigned int texttype;
		unsigned int presentation;
		unsigned int pathtype;
		int width;
		int strance;
		double mag,angle;
		char *string;
	public:
		void set(int prop,unsigned int value);
		void set(int prop,signed int value){};
		void set(int prop,double value){};
		void set(int prop,char *value);
		void display(void);
};

class path:public element
{
	private:
		unsigned int layer;
		unsigned int plex;
		unsigned int datatype;
		unsigned int elflags;
		unsigned int pathtype;
		int width;
		int bgnextn;
		int endextn;
	public:
		void set(int prop,unsigned int value);
		void set(int prop,signed int value){};
		void set(int prop,double value){};
		void set(int prop,char *value){};
		void display(void);
};

class sref:public element
{
	private:
		unsigned int elflags;
		unsigned int plex;
		char *sname;
		int strans;
		double mag,angle;
		int row,col;
	public:
		void set(int prop,unsigned int value);
		void set(int prop,signed int value){};
		void set(int prop,double value);
		void set(int prop,char *value);
		void display(void);
};

class aref:public element
{
	private:
		unsigned int elflags;
		unsigned int plex;
		char *sname;
		int strans;
		double mag,angle;
		int row,col;
	public:
		void set(int prop,unsigned int value);
		void set(int prop,signed int value){};
		void set(int prop,double value);
		void set(int prop,char *value);
		void display(void);
};

class node:public element
{
	private:
		unsigned int elflags;
		unsigned int plex;
		unsigned int layer;
		unsigned int nodetype;
	public:
		void set(int prop,unsigned int value);
		void set(int prop,signed int value){};
		void set(int prop,double value){};
		void set(int prop,char *value);
		void display(void);
};

class box:public element
{
	private:
		unsigned int elflags;
		unsigned int plex;
		unsigned int layer;
		unsigned int nodetype;
	public:
		void set(int prop,unsigned int value);
		void set(int prop,signed int value){};
		void set(int prop,double value){};
		void set(int prop,char *value);
		void display(void);
};
