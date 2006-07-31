gds2::gds2(const char *fname)
{
	structurelist=new structures;
	fp=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("Error reading the gdsfile\n");
		exit(4);
	}
	while(get_record_data()!=1)
	{
		if(size==0)
		{
			fclose(fp);
			break;
		}
		data_size=size-4;
		if(DEBUG) printf("rtype=%x\n",rtype);
		switch(rtype)
		{
			case 0x00:
				version=get_unsigned_int();
				break;
			case 0x01:
				year=get_unsigned_int();
				month=get_unsigned_int();
				day=get_unsigned_int();
				hour=get_unsigned_int();
				minute=get_unsigned_int();
				second=get_unsigned_int();
				myear=get_unsigned_int();
				mmonth=get_unsigned_int();
				mday=get_unsigned_int();
				mhour=get_unsigned_int();
				mminute=get_unsigned_int();
				msecond=get_unsigned_int();
				break;
			case 0x02:
				libname=(char *)malloc(data_size+1);
				if(libname==NULL)
				{
					printf("Unable to allocate libname\n");
					exit(9);
				}
				fread(libname,1,data_size,fp);
				libname[data_size]='\0';
				if(DEBUG) printf("Libname is %s\n",libname);
				break;
			case 0x03:
				units=get_real_8();
				unitsinm=get_real_8();
				break;
			case 0x04:
				break;
			case 0x05:
				currentstru=structurelist->newnode();
				currentstru->elems=new elementlist;
				currentstru->year=get_unsigned_int();
				currentstru->month=get_unsigned_int();
				currentstru->day=get_unsigned_int();
				currentstru->hour=get_unsigned_int();
				currentstru->minute=get_unsigned_int();
				currentstru->second=get_unsigned_int();
				currentstru->myear=get_unsigned_int();
				currentstru->mmonth=get_unsigned_int();
				currentstru->mday=get_unsigned_int();
				currentstru->mhour=get_unsigned_int();
				currentstru->mminute=get_unsigned_int();
				currentstru->msecond=get_unsigned_int();
				break;
			case 0x06:
				currentstru->structurename=(char *)malloc(data_size+1);
				if(currentstru->structurename==NULL)
				{
					printf("Unable to allocate libname\n");
					exit(9);
				}
				fread(currentstru->structurename,1,data_size,fp);
				currentstru->structurename[data_size]='\0';
				if(DEBUG) printf("Structure name is %s\n",currentstru->structurename);
				break;
			case 0x07:
				break;
			case 0x08:
				currentelems=currentstru->elems->newnode(BOUNDARY);
				currentelems->plist=new pointlist;
				break;
			case 0x09:
				currentelems=currentstru->elems->newnode(PATH);
				currentelems->plist=new pointlist;
				break;
			case 0x0a:
				currentelems=currentstru->elems->newnode(SREF);
				currentelems->plist=new pointlist;
				break;
			case 0x0b:
				currentelems=currentstru->elems->newnode(AREF);
				currentelems->plist=new pointlist;
				break;
			case 0x0c:
				currentelems=currentstru->elems->newnode(TEXT);
				currentelems->plist=new pointlist;
				break;
			case 0x0d:
				currentelems->elem->set(LAYER,get_unsigned_int());
				break;
			case 0x0e:
				currentelems->elem->set(DATATYPE,get_unsigned_int());
				break;
			case 0x0f:
				currentelems->elem->set(WIDTH,get_unsigned_int());
				break;
			case 0x10:
				for(int i=0;i<data_size/8;i++)
				{
					currentelems->plist->newnode(get_unsigned_4int(),get_unsigned_4int());
				}
				break;
			case 0x11:
				break;
			case 0x12:
				char *tempstr1;
				tempstr1=(char *)malloc(data_size+1);
				if(tempstr1==NULL)
				{
					printf("Unable to allocate text string\n");
					exit(10);
				}
				fread(tempstr1,1,data_size,fp);
				tempstr1[data_size]='\0';
				currentelems->elem->set(STRING,tempstr1);
				free(tempstr1);
				break;
			case 0x13:
				currentelems->elem->set(COL,get_unsigned_int());
				currentelems->elem->set(ROW,get_unsigned_int());
				break;
			case 0x14:
				break;
			case 0x15:
				break;
			case 0x16:
				currentelems->elem->set(TEXTTYPE,get_unsigned_int());
				break;
			case 0x17:
				currentelems->elem->set(PRESENTATION,get_unsigned_int());
				break;
			case 0x18:
				break;
			case 0x19:
				char *tempstr;
				tempstr=(char *)malloc(data_size+1);
				if(tempstr==NULL)
				{
					printf("Unable to allocate text string\n");
					exit(10);
				}
				fread(tempstr,1,data_size,fp);
				tempstr[data_size]='\0';
				currentelems->elem->set(STRING,tempstr);
				free(tempstr);
				break;
			case 0x1a:
				currentelems->elem->set(STRANS,get_unsigned_int());
				break;
			case 0x1b:
				currentelems->elem->set(MAG,get_real_8());
				break;
			case 0x1c:
				currentelems->elem->set(ANGLE,get_real_8());
				break;
			case 0x1d:
				break;
			case 0x1e:
				break;
			case 0x1f:
				printf("Cannot have reflibs. exiting...\n");
				exit(13);
			case 0x20:
				printf("Not handling font tables yet...\n");
				exit(14);
			case 0x21:
				currentelems->elem->set(PATHTYPE,get_unsigned_int());
				break;
			case 0x22:
				generations=get_unsigned_int();
				if(DEBUG) printf("Generations=%d\n",generations);
				break;
			case 0x23:
				printf("Attribute table not supported");
				exit(15);
			case 0x24:
				break;
			case 0x25:
				break;
			case 0x26:
				currentelems->elem->set(ELFLAGS,get_unsigned_int());
				break;
			case 0x27:
				break;
			case 0x28:
				break;
			case 0x29:
				break;
			case 0x2a:
				currentelems->elem->set(NODETYPE,get_unsigned_int());
				break;
			case 0x2b:
				printf("propattr not supported yet.");
				exit(16);
			case 0x2c:
				printf("propvalue not supported yet");
				exit(17);
			case 0x2d:
				currentelems=currentstru->elems->newnode(BOX);
				currentelems->plist=new pointlist;
				break;
			case 0x2e:
				currentelems->elem->set(BOXTYPE,get_unsigned_int());
				break;
			case 0x2f:
				currentelems->elem->set(PLEX,get_unsigned_4int());
				break;
			case 0x30:
				currentelems->elem->set(BGNEXTN,get_unsigned_4int());
				break;
			case 0x31:
				currentelems->elem->set(ENDEXTN,get_unsigned_4int());
				break;
			case 0x32:
				printf("Tapenum unsupported");
				exit(16);
			case 0x33:
				printf("Tapecode unsupported");
				exit(17);
			case 0x34:
				printf("STRCLASS UNsupported");
				exit(18);
			case 0x35:
				printf("RESERVED type found");
				exit(19);
			case 0x36:
				printf("Format unsupported");
				exit(20);
			case 0x37:
				printf("MASK unsupported");
				exit(21);
			case 0x38:
				printf("ENDMASKS Unsupported");
				exit(22);
			case 0x39:
				printf("LIBDIRSIZE Unsupported");
				exit(23);
			case 0x3a:
				printf("SRFNAME unsupported");
				exit(24);
			case 0x3b:
				printf("Libsecure unsupported");
				exit(25);
		}
	}
}

void gds2::printstructurenames(void)
{
	if(DEBUG) printf("Reached printstructures\n");
	structurelist->dispname();
}

void gds2::displayall(void)
{
	if(DEBUG) printf("Reached displayall\n");
	printf("Version is 0x%x\n",version);
	structurelist->displayelements();
}

void gds2::writegds2(char *gds2filename)
{
	wfp=fopen("gds2filename","w");
	if(DEBUG) printf("Opened the file for writing\n");
	writegds2_unsigned_int(version);
}








int gds2::get_record_data(void)
{
   head=(struct header *)malloc(sizeof(struct header));
   if(head==NULL)
   {
	   printf("Memory error\n");
	   exit(2);
   }
   if(sizeof(struct header)!=fread((char *)head,1,sizeof(struct header),fp))
   {
	   printf("Returning 1\n");
       return(1);
   }    
   if(MOREDEBUG)
   {
	   printf("HEADER:\n");
	   printf("0x%x\n",head->record_length[0]);
	   printf("0x%x\n",head->record_length[1]);
	   printf("0x%x\n",head->record_type);
	   printf("0x%x\n",head->data_type);
   }
   size=head->record_length[0]*256+head->record_length[1];
   rtype=head->record_type;
   dtype=head->data_type;
   free(head);
   return(0);
}



double gds2::get_real_8(void)
{
   unsigned char b[8];
   double rvalue;
   unsigned long long real_mantissa=0;
   int sign,i;
   int exponent;
   fread(b,1,8,fp);
   sign=b[0]&0x80;
   exponent=(b[0]&0x7f)-64;
   for(i=0;i<7;i++)
   {
       real_mantissa<<=8;
       real_mantissa+=b[i+1];
   }
   rvalue=(double)((double)real_mantissa)/pow(2,56);
   rvalue=rvalue*pow(16,exponent);
   if(sign)
      rvalue*=-1;
   return(rvalue);
}



unsigned int gds2::get_unsigned_int(void)
{
    unsigned int a=0;
    unsigned char b[2];
    fread(b,1,2,fp);
	if(MOREDEBUG) printf("b[0]=0x%x  b[1]=0x%x\n",b[0],b[1]);
    a=b[0];
    a<<=8;
    a+=b[1];
    if(a&0x8000)
    {
       a&=0x7fff;
       a^=0x7fff;
       a+=1;
       a*=-1;
    }
    return(a);
}


unsigned int gds2::get_unsigned_4int(void)
{
    unsigned int a=0;
    unsigned char b[4];
    fread(b,1,4,fp);
    a=b[0];
    a<<=8;
    a+=b[1];
    a<<=8;
    a+=b[2];
    a<<=8;
    a+=b[3];
    if(a&0x80000000)
    {
       a&=0x7fffffff;
       a^=0x7fffffff;
       a+=1;
       a*=-1;
    }
    return(a);
}
