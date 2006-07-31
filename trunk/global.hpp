void writegds2_unsigned_4int(unsigned int a);
void writegds2_unsigned_int(unsigned int a);
int find_float_parts (double in_num, double *mantissa);
int writegds2_double(double x);
FILE *wfp;
void writegds2_unsigned_int(unsigned int a)
{
	unsigned char b[2];
	b[1]=a&0x00ff;
	b[0]=a>>8;
	printf("a=0x%x  b[0]=0x%x  b[1]=0x%x\n",a,b[0],b[1]);
}
void writegds2_unsigned_4int(unsigned int a)
{
	unsigned char b[4];
	b[3]=a&0x00ff;
	a=a>>8;
	b[2]=a&0x00ff;
	a>>=8;
	b[1]=a&0x00ff;
	a>>=8;
	b[0]=a&0x00ff;
	printf("b[0]=0x%x  b[1]=0x%x  b[2]=0x%x  b[3]=0x%x\n",b[0],b[1],b[2],b[3]);
}
int find_float_parts (double in_num, double *mantissa)
{
    int exponent;

    in_num = fabs (in_num);

/*    if (fabs (in_num) < 1e-18)
        {
		printf("abcd");
        exponent = 0;
        *mantissa = 0;
        }
    else
        {*/
        for (exponent = -64; exponent < 64; exponent++)
            {
            *mantissa = in_num / pow (16, exponent);
            if (*mantissa <= 1)
                {
                break;
                }
            }
        //}

    return (exponent);
}
int writegds2_double(double x)
{
	unsigned int exp;
	double mantissa;
	unsigned long long int_mantissa,part_mantissa;
	unsigned int part_mantissa_int;
	exp=find_float_parts(x,&mantissa);
	exp+=64;
	if(x<0)
	{
		printf("Hello");
		exp&=0x000000ff;
		exp|=0x80;
	}
        mantissa *= pow (2, 56);
        int_mantissa = (unsigned long long)mantissa;
        printf("exponent=0x%x",(char)exp);
        for (int mantissa_ktr = 6; mantissa_ktr >= 0; mantissa_ktr--)
        {
             part_mantissa = int_mantissa;
             for (int sm_ktr = 0; sm_ktr < mantissa_ktr; sm_ktr++)
             {
                   part_mantissa >>= 8;
             }
             part_mantissa &= 0xff;
             part_mantissa_int = part_mantissa;
             printf(" 0x%x",part_mantissa_int);
        }
	return(0);
}
