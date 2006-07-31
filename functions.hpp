pointlist::pointlist(void)
{
	head=current=NULL;
}

elementlist::elementlist(void)
{
	head=current=NULL;
}

structures::structures(void)
{
	current=head=NULL;
}

class pointnode * pointlist::newnode(int y,int x)//x & y are interchanged as the calling function is evaluated right to left
{
	if(head==NULL)
	{
		current=head=(class pointnode *)malloc(sizeof(class pointnode));
		if(current==NULL)
		{
			printf("Memory allocation error\n");
			exit(8);
		}
		current->next=NULL;
	}
	else
	{
		current->next=(class pointnode *)malloc(sizeof(class pointnode));
		if(current->next==NULL)
		{
			printf("Memory error\n");
			exit(7);
		}
		current=current->next;
		current->next=NULL;
	}
	current->x=x;
	current->y=y;
	if(DEBUG) printf("X=%d  Y=%d\n",x,y);
	return(current);
}

void pointlist::display(void)
{
	current=head;
	while(current!=NULL)
	{
		printf("\t\tX=%d Y=%d\n",current->x,current->y);
		current=current->next;
	}
}

class elements * elementlist::newnode(int obj)
{
	if(head==NULL)
	{
		current=head=(class elements *)malloc(sizeof(class elements));
		if(current==NULL)
		{
			printf("Element allocation failed\n");
			exit(1);
		}
		current->next=NULL;
	}
	else
	{
		current->next=(class elements *)malloc(sizeof(class elements));
		if(current->next==NULL)
		{
			printf("Element Allocation failed\n");
			exit(2);
		}
		current=current->next;
		current->next=NULL;
	}
	switch(obj)
	{
		case BOUNDARY:
			if(DEBUG) printf("Got into boundary\n");
			current->elem=new boundary;
			break;
		case TEXT:
			if(DEBUG) printf("Got into Text\n");
			current->elem=new text;
			break;
		case PATH:
			if(DEBUG) printf("Got into Path\n");
			current->elem=new path;
			break;
		case SREF:
			if(DEBUG) printf("Got into SREF\n");
			current->elem=new sref;
			break;
		case AREF:
			if(DEBUG) printf("Got into AREF\n");
			current->elem=new aref;
			break;
	}
	return(current);
}

class structure * structures::newnode(void)
{
	if(head==NULL)
	{
		current=head=(class structure *)malloc(sizeof(class structure));
		if(current==NULL)
		{
			printf("Memory Allocation Error.\n");
			exit(6);
		}
		if(MOREDEBUG) printf("Structure node & head allocated = %x\n",current);
		current->next=NULL;
	}
	else
	{
		current->next=(class structure *)malloc(sizeof(class structure));
		if(current->next==NULL)
		{
			printf("Memory allocation error\n");
			exit(7);
		}
		current=current->next;
		if(MOREDEBUG) printf("Structure node allocated = %x\n",current);
		current->next=NULL;
	}
	return(current);
}


void structures::dispname(void)
{
	current=head;
	if(MOREDEBUG) printf("dispname: current=head=%x\n",current);
	if(DEBUG) printf("Reached dispname\n");
	while(current!=NULL)
	{
		printf("Structure Name is %s\n",current->structurename);
		current=current->next;
	}
}

void structures::displayelements(void)
{
	current=head;
	if(MOREDEBUG) printf("dispname: current=head=%x\n",current);
	if(DEBUG) printf("Reached dispname\n");
	while(current!=NULL)
	{
		printf("Structure Name is %s\n",current->structurename);
		current->elems->displayelements();
		current=current->next;
	}
}

void elementlist::displayelements(void)
{
	current=head;
	while(current!=NULL)
	{
		current->elem->display();
		current->plist->display();
		current=current->next;
	}
}

void boundary::set(int prop,unsigned int value)
{
	if(DEBUG) printf("Prop = %d\n",prop);
	switch(prop)
	{
		case LAYER:
			if(DEBUG) printf("Assigning layer through boundary\n");
			layer=value;
			break;
		case PLEX:
			plex=value;
			break;
		case DATATYPE:
			datatype=value;
			break;
		case ELFLAGS:
			elflags=value;
			break;
	}
}

void boundary::display(void)
{
	if(DEBUG) printf("Displaying boundary element\n");
	printf("Boundary\n");
	printf("\tLayer no. %d\n",layer);
	printf("\tDatatype  %d\n",datatype);
}

void text::set(int prop,unsigned int value)
{
	if(DEBUG) printf("Prop = %d\n",prop);
	switch(prop)
	{
		case LAYER:
			if(DEBUG) printf("Assigning layer through text\n");
			layer=value;
			break;
		case PLEX:
			plex=value;
			break;
		case TEXTTYPE:
			texttype=value;
			break;
		case ELFLAGS:
			elflags=value;
			break;
	}
}

void text::set(int prop,char *value)
{
	string=(char *)malloc(strlen(value)+1);
	if(string==NULL)
	{
		printf("Memory Error\n");
		exit(2);
	}
	strcpy(string,value);
}

void text::display(void)
{
	if(DEBUG) printf("Displaying text element\n");
	printf("Text\n");
	printf("\tLayer no. %d\n",layer);
	printf("\tTexttype  %d\n",texttype);
	printf("\tString is %s\n",string);
}

void path::set(int prop,unsigned int value)
{
	if(DEBUG) printf("Prop = %d\n",prop);
	if(DEBUG) printf("inside path\n");
	switch(prop)
	{
		case LAYER:
			if(DEBUG) printf("Assigning layer through path\n");
			layer=value;
			break;
		case PLEX:
			plex=value;
			break;
		case DATATYPE:
			datatype=value;
			break;
		case ELFLAGS:
			elflags=value;
			break;
		case PATHTYPE:
			pathtype=value;
			break;
		case WIDTH:
			width=value;
			break;
		case BGNEXTN:
			bgnextn=value;
			break;
		case ENDEXTN:
			endextn=value;
			break;
	}
}

void path::display(void)
{
	if(DEBUG) printf("Displaying path element\n");
	printf("PATH\n");
	printf("Layer no. %d\n",layer);
	printf("Datatype  %d\n",datatype);
}

void sref::set(int prop,unsigned int value)
{
	if(DEBUG) printf("Prop = %d\n",prop);
	switch(prop)
	{
		case PLEX:
			plex=value;
			break;
		case ELFLAGS:
			elflags=value;
			break;
		case STRANS:
			strans=value;
			break;
		case ROW:
			row=value;
			break;
		case COL:
			col=value;
			break;
	}
}
void sref::set(int prop, double value)
{
	switch(prop)
	{
		case MAG:
			mag=value;
			break;
		case ANGLE:
			angle=value;
			break;
	}
}

void sref::set(int prop, char *value)
{
	sname=(char *)malloc(strlen(value)+1);
	if(sname==NULL)
	{
		printf("Unable to allocate sname\n");
		exit(12);
	}
	strcpy(sname,value);
}

void sref::display(void)
{
	if(DEBUG) printf("Displaying sref element\n");
	printf("SREF\n");
	printf("\t%s\n",sname);
}


void aref::set(int prop,unsigned int value)
{
	if(DEBUG) printf("Prop = %d\n",prop);
	switch(prop)
	{
		case PLEX:
			plex=value;
			break;
		case ELFLAGS:
			elflags=value;
			break;
		case STRANS:
			strans=value;
			break;
	}
}
void aref::set(int prop, double value)
{
	switch(prop)
	{
		case MAG:
			mag=value;
			break;
		case ANGLE:
			angle=value;
			break;
	}
}

void aref::set(int prop, char *value)
{
	sname=(char *)malloc(strlen(value)+1);
	if(sname==NULL)
	{
		printf("Unable to allocate sname\n");
		exit(12);
	}
	strcpy(sname,value);
}

void aref::display(void)
{
	if(DEBUG) printf("Displaying aref element\n");
	printf("AREF\n");
	printf("\t%s\n",sname);
	printf("\tRows=%d Cols=%d\n",row,col);
}
