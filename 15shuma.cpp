#include<stdio.h>
#include <stdlib.h>  
#include <math.h>


typedef struct array
{
 int s[4][4];	//十五数码的数组
 int x0;
 int y0;	//0所在的位置
 int f;		//f=d+w
 int d;		//深度
 int w;		//下表横坐标之差的绝对值加上纵坐标之差的绝对值 
 struct array *past;		//扩展之前的数组
}array,*arrays;

typedef struct table
{		
 arrays a[10000];
 int k;   
}table,*tables;



arrays cs=(arrays)malloc(sizeof(array));			//初始十五数码
arrays mb=(arrays)malloc(sizeof(array));			//目标十五数码
tables open=(tables)malloc(sizeof(table));			//创建open表
tables close=(tables)malloc(sizeof(table));			//创建close表


//计算w 
int distance_position(arrays s)		//节点到目标点的横纵坐标之差的绝对值之和 
{
 int w=0;
 int mubiao[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};  //目标
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

void set_array()  //初始化
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

int Pingjia(arrays s)	//计算估价函数
{
 s->f=s->d+s->w;
 return (s->f);
}


bool left(arrays s)		//0左移
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (y==0)		//0在最左
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x][y-1];
 s->s[x][y-1]=t;
 s->y0--;
 return true;
}

bool right(arrays s)		//0右移
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (y==3)		//0在最右
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x][y+1];
 s->s[x][y+1]=t;
 s->y0++;
 return true;
}

bool up(arrays s)		//0上移
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (x==0)		//0在最上
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x-1][y];
 s->s[x-1][y]=t;
 s->x0--;
 return true;
}

bool down(arrays s)		//0下移
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (x==3)		//0在最下
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x+1][y];
 s->s[x+1][y]=t;
 s->x0++;
 return true;
}

bool isequal(arrays s1,arrays s2)	//判断两个数组是否相等，用于搜索open表和close表
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

void copy_array(arrays s1,arrays s2)		//移动之前先创建数组,将s1赋值给s2
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

void output_array(arrays s)		//输出十五数码数组
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

void add_table(tables t,arrays s)		//把数组加入到open表或者close表中
{
 t->a[t->k++]=s;
}

void delete_table(tables t)		//从open中删除数组
{
 for (int i=0;i<t->k;i++)
	 t->a[i]=t->a[i+1];
 t->k--;
} 

bool search_table(tables t,arrays s)		//在open和close中查找移动的数组是否出现过
{
 for (int i=0;i<t->k;i++)
 {
	if (isequal(t->a[i],s))
		return true;
 }
 return false;
}

void expand(arrays s)	//扩展数组
{
 arrays pl=(arrays)malloc(sizeof(array));	//初始化向左移动的数组
 arrays pr=(arrays)malloc(sizeof(array));	//初始化向右移动的数组
 arrays pu=(arrays)malloc(sizeof(array));	//初始化向上移动的数组
 arrays pd=(arrays)malloc(sizeof(array));	//初始化向下移动的数组
 
 copy_array(s,pl);
 copy_array(s,pr);
 copy_array(s,pu);
 copy_array(s,pd);
 
 pl->past=s;
 pr->past=s;
 pu->past=s;
 pd->past=s;
 
 if(left(pl) && !search_table(close,pl) && !search_table(open,pl))	//0左移，在open表中和close表中查找是否已经存在
 {
  pl->d++;
  pl->w=distance_position(pl);
  pl->f=Pingjia(pl);
  add_table(open,pl);
 }
 
 if(right(pr) && !search_table(close,pr) && !search_table(open,pr))	//0右移，在open表中和close表中查找是否已经存在
 {
  pr->d++;
  pr->w=distance_position(pr);
  pr->f=Pingjia(pr);
  add_table(open,pr);
 }
 
 if(up(pu) && !search_table(close,pu) && !search_table(open,pu))	//0上移，在open表中和close表中查找是否已经存在
 {
  pu->d++;
  pu->w=distance_position(pu);
  pu->f=Pingjia(pu);
  add_table(open,pu);
 }
 
  if(down(pd) && !search_table(close,pd) && !search_table(open,pd))	//0下移，在open表中和close表中查找是否已经存在
 {
  pd->d++;
  pd->w=distance_position(pd);
  pd->f=Pingjia(pd);
  add_table(open,pd);
 }
 
}

void sort_open(tables t)	//按f的大小从小到大排序
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

void reverse_array(arrays &s)	//把目标数组反序输出
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

void initial_array()  //初始化矩阵
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
 int mubiao[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};  //目标
 for ( int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
		mb->s[i][j]=mubiao[i][j];
 }
 open->k=0;
 close->k=0;
 add_table(open,cs);
 printf("初始十五数码：\n");
 output_array(cs);
 printf("目标十五数码：\n");
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
		printf("第%d次移动 \n",t->d);
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
  printf("\n无解\n");
 }
}
