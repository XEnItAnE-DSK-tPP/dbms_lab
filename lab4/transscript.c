#include <stdio.h>
#include <string.h>

struct Course
{
	char ID[5],title[100];
	int credit,sem;
	struct Course *next;
};
typedef struct Course course;

struct Grade
{
	course *c;
	char g[2];
	struct Grade *next;
};

struct Department
{
	char name[2];
	course cOffered;
	struct Department *next;
};
typedef struct Department department;

struct Semester
{
	struct Grade grades;
	float credits,spi,cpi;
};
typedef struct Semester semester;

struct Student
{
	char name[100],roll[9];
	semester sems[8];
	struct Student *next;
};
typedef struct Student student;

int char2int(char c)
{
	if(c=='0')return 0;
	if(c=='1')return 1;
	if(c=='2')return 2;
	if(c=='3')return 3;
	if(c=='4')return 4;
	if(c=='5')return 5;
	if(c=='6')return 6;
	if(c=='7')return 7;
	if(c=='8')return 8;
	if(c=='9')return 9;
}

int hRoll(char roll[])
{
	int hf=0;
	for(int i=0;i<9;i++)
	{
		hf+=(i+1)*(10-i)*(char2int(roll[i])+1)*(10-char2int(roll[i]));
		hf=hf%1039;
	}
	return hf;
}

int main()
{
	student stdTable[1039];
	for(int i=0;i<1039;i++)
	{
		(stdTable[i]).next=NULL;
	}
	department depTable;
	depTable.next=NULL;
	depTable.cOffered.next=NULL;
	char c;
	int a,b;
	char str1[100],str2[100],str3[100];
	
	FILE *students=fopen("students.csv","r");
	while(fscanf(students,"%[^,]%*c%c%[^\n]%*c\n",str1,&c,str2)==3)
	{
		student *tmp=(student*)malloc(sizeof(student));
		int ind=hRoll(str2);
		strcpy(tmp->name,str1);
		strcpy(tmp->roll,str2);
		for(int i=0;i<8;i++)tmp->sems[i].grades.next=NULL;
		tmp->next=stdTable[ind].next;
		stdTable[ind].next=tmp;
	}
	fclose(students);

	FILE *courses=fopen("courses.csv","r");
	while(fscanf(courses,"%d%c%[^,]%*c%c%[^,]%*c%c%c%c%c%c%c%c%d\n",&a,&c,str1,&c,str2,&c,&c,&c,&c,&c,&c,&c,&b)==13)
	{
		course *tmp=(course*)malloc(sizeof(course));
		tmp->sem=a;
		strcpy(tmp->ID,str1);
		strcpy(tmp->title,str2);
		tmp->credit=b;
		char n[2]={str1[0],str1[1]};
		department *dtmp=depTable.next;
		while(dtmp)
		{
			if(strcmp(n,dtmp->name)==0)
			{
				tmp->next=dtmp->cOffered.next;
				dtmp->cOffered.next=tmp;
				break;
			}
			dtmp=dtmp->next;
		}
		if(dtmp==NULL)
		{
			department *dnew=(department*)malloc(sizeof(department));
			strcpy(dnew->name,n);
			dnew->cOffered.next=NULL;
			tmp->next=dnew->cOffered.next;
			dnew->cOffered.next=tmp;
			dnew->next=depTable.next;
			depTable.next=dnew;
		}
	}
	fclose(courses);

	FILE *grades=fopen("grades.csv","r");
	while(fscanf(grades,"%[^,]%*c%c%[^,]%*c%c%[^\n]%*c\n",str1,str2,str3)==5)
	{
		int ind=hRoll(str1);
		char name[2]={str2[0],str2[1]};
		department *dtmp=depTable.next;
		course *ctmp;
		struct Grade *gtemp;
		gtemp=(struct Grade*)malloc(sizeof(struct Grade));
		student *stdtmp=stdTable[ind].next;
		while(stdtmp)
		{
			if(strcmp(stdtmp->roll,str1)==0)
			{
				while(dtmp)
				{
					if(strcmp(dtmp->name,name)==0)
					{
						ctmp=dtmp->cOffered.next;
						while(ctmp)
						{
							if(strcmp(ctmp->ID,str2)==0)
							{
								strcpy(gtemp->g,str3);
								gtemp->c=ctmp;
								gtemp->next=stdtmp->sems[ctmp->sem].grades.next;
								stdtmp->sems[ctmp->sem].grades.next;
								break;
							}
							ctmp=ctmp->next;
						}
						break;
					}
					dtmp=dtmp->next;
				}
				break;
			}
			stdtmp=stdtmp->next;
		}
	}
	fclose(grades);
	return 0;
}
