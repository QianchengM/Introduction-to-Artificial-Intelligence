#include<stdio.h>
#include <stdlib.h>  
#include <math.h>


typedef struct array
{
 int s[4][4];	//ʮ�����������
 int x0;
 int y0;	//0���ڵ�λ��
 int f;		//f=d+w
 int d;		//���
 int w;		//�±������֮��ľ���ֵ����������֮��ľ���ֵ 
 struct array *past;		//��չ֮ǰ������
}array,*arrays;

typedef struct table
{		
 arrays a[10000];
 int k;   
}table,*tables;



arrays cs=(arrays)malloc(sizeof(array));			//��ʼʮ������
arrays mb=(arrays)malloc(sizeof(array));			//Ŀ��ʮ������
tables open=(tables)malloc(sizeof(table));			//����open��
tables close=(tables)malloc(sizeof(table));			//����close��


//����w 
int distance_position(arrays s)		//�ڵ㵽Ŀ���ĺ�������֮��ľ���ֵ֮�� 
{
 int w=0;
 int mubiao[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};  //Ŀ��
 for (int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
	{
		for(int k=0;k<4;k++)
		{
			for(int l=0;l<4;l++)
			{
				if (s->s[i][j]==mubiao[k][l]&&s->s[i][j]!=0)
	            {
		            w+=abs(i-k)+abs(j-l);
	            }
			}
		}

	}
 }
 return w;
}

void set_array()  //��ʼ��
{
int s[16] = {5,1,2,4,9,6,3,8,13,15,10,11,14,0,7,12};
//int s[16] = {11,9,4,5,1,3,0,12,7,5,8,6,13,2,10,14};
//int s[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,0,15}; 
int count = 0;

 for (int i=0;i<4;i++)
 {
	 for (int j=0;j<4;j++)
	 {
		cs->s[i][j]=s[count];
		count++;
	 }
 }

// &s0->s[4][4]={5,1,2,4,9,6,3,8,13,15,10,11,14,0,7,12};
}

int Pingjia(arrays s)	//������ۺ���
{
 s->f=s->d+s->w;
 return (s->f);
}


bool left(arrays s)		//0����
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (y==0)		//0������
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x][y-1];
 s->s[x][y-1]=t;
 s->y0--;
 return true;
}

bool right(arrays s)		//0����
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (y==3)		//0������
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x][y+1];
 s->s[x][y+1]=t;
 s->y0++;
 return true;
}

bool up(arrays s)		//0����
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (x==0)		//0������
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x-1][y];
 s->s[x-1][y]=t;
 s->x0--;
 return true;
}

bool down(arrays s)		//0����
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (x==3)		//0������
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x+1][y];
 s->s[x+1][y]=t;
 s->x0++;
 return true;
}

bool isequal(arrays s1,arrays s2)	//�ж����������Ƿ���ȣ���������open���close��
{
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			if (s1->s[i][j]!=s2->s[i][j])
				return false;
		}
	}
	return true;
}

void copy_array(arrays s1,arrays s2)		//�ƶ�֮ǰ�ȴ�������,��s1��ֵ��s2
{
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			s2->s[i][j]=s1->s[i][j];
		}
	}
	s2->x0=s1->x0;
	s2->y0=s1->y0;
	s2->f=s1->f;
	s2->d=s1->d;
	s2->w=s1->w;
	s2->past=s1->past;
}

void output_array(arrays s)		//���ʮ����������
{
 for (int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
	{
		printf("%4d",s->s[i][j]);
	}
	printf("\n");
 }
}

void add_table(tables t,arrays s)		//��������뵽open�����close����
{
 t->a[t->k++]=s;
}

void delete_table(tables t)		//��open��ɾ������
{
 for (int i=0;i<t->k;i++)
	 t->a[i]=t->a[i+1];
 t->k--;
} 

bool search_table(tables t,arrays s)		//��open��close�в����ƶ��������Ƿ���ֹ�
{
 for (int i=0;i<t->k;i++)
 {
	if (isequal(t->a[i],s))
		return true;
 }
 return false;
}

void expand(arrays s)	//��չ����
{
 arrays pl=(arrays)malloc(sizeof(array));	//��ʼ�������ƶ�������
 arrays pr=(arrays)malloc(sizeof(array));	//��ʼ�������ƶ�������
 arrays pu=(arrays)malloc(sizeof(array));	//��ʼ�������ƶ�������
 arrays pd=(arrays)malloc(sizeof(array));	//��ʼ�������ƶ�������
 
 copy_array(s,pl);
 copy_array(s,pr);
 copy_array(s,pu);
 copy_array(s,pd);
 
 pl->past=s;
 pr->past=s;
 pu->past=s;
 pd->past=s;
 
 if(left(pl) && !search_table(close,pl) && !search_table(open,pl))	//0���ƣ���open���к�close���в����Ƿ��Ѿ�����
 {
  pl->d++;
  pl->w=distance_position(pl);
  pl->f=Pingjia(pl);
  add_table(open,pl);
 }
 
 if(right(pr) && !search_table(close,pr) && !search_table(open,pr))	//0���ƣ���open���к�close���в����Ƿ��Ѿ�����
 {
  pr->d++;
  pr->w=distance_position(pr);
  pr->f=Pingjia(pr);
  add_table(open,pr);
 }
 
 if(up(pu) && !search_table(close,pu) && !search_table(open,pu))	//0���ƣ���open���к�close���в����Ƿ��Ѿ�����
 {
  pu->d++;
  pu->w=distance_position(pu);
  pu->f=Pingjia(pu);
  add_table(open,pu);
 }
 
  if(down(pd) && !search_table(close,pd) && !search_table(open,pd))	//0���ƣ���open���к�close���в����Ƿ��Ѿ�����
 {
  pd->d++;
  pd->w=distance_position(pd);
  pd->f=Pingjia(pd);
  add_table(open,pd);
 }
 
}

void sort_open(tables t)	//��f�Ĵ�С��С��������
{
 int flag=1;
  arrays temp=(arrays)malloc(sizeof(array));
 for (int i=0;i<t->k && flag;i++)
 {
  flag=0;
  for (int j=t->k-1;j>i;j--)
  {
	if (t->a[j]->f < t->a[j-1]->f)
	{	
	 copy_array(t->a[j],temp);
	 copy_array(t->a[j-1],t->a[j]);
	 copy_array(temp,t->a[j-1]);
	 flag=1;
	}
  }
 }
}

void reverse_array(arrays &s)	//��Ŀ�����鷴�����
{
  arrays si;
  arrays sj;
  si=NULL;
  sj=s->past;
   while(1)
  {
    s->past=si;
    si=s;
    if(sj==NULL)
    {
      break;
    }
    s=sj;
    sj=sj->past;
  }
}

void initial_array()  //��ʼ������
{
 for (int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
	{
		if (cs->s[i][j]==0)
		{
			cs->x0=i;
			cs->y0=j;
		}	
	}
 }
 cs->d=0;
 cs->w=distance_position(cs);
 cs->f=Pingjia(cs);
 cs->past=NULL;
 int mubiao[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};  //Ŀ��
 for ( int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
		mb->s[i][j]=mubiao[i][j];
 }
 open->k=0;
 close->k=0;
 add_table(open,cs);
 printf("��ʼʮ�����룺\n");
 output_array(cs);
 printf("Ŀ��ʮ�����룺\n");
 output_array(mb);
}

int main()
{
 arrays t=(arrays)malloc(sizeof(array));
 set_array();
 initial_array();
 while(open->k!=0 && close->k<=10000) 
 {
    arrays t=open->a[0];
	delete_table(open);
	if(isequal(t,mb))
	{
	  reverse_array(t);
	  while(t)
	  {
		printf("��%d���ƶ� \n",t->d);
		output_array(t);  
		t=t->past;
	  }
	 break;
	}
    add_table(close,t);
    expand(t);
    sort_open(open);
 }
if(open->k==0 || close->k>10000)
 {
  printf("\n�޽�\n");
 }
}
