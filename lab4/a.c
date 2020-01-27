#include<stdio.h>

struct Course
{
    char ID[6],name[100],sem,l,t,p,c;
    struct Course *next;
};
typedef struct Course course;

struct Garde
{
    course c;
    char grade[2];
    struct Grade *next;
};
typedef struct Grade grade;

struct Department
{
    char depName[2];
    course cOffered;
    struct Department *next;
};
typedef struct Department department;

struct Semester
{
    //grade grades;
    float credits,spi,cpi;
};
typedef struct Semester semester;

struct Student
{
    char name[100],roll[9];
    semester sem[8];
    struct Student *next;
};
typedef struct Student student;

int charToInt(char c)
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

int hRoll(char* roll)
{
    int hf=0;
    int i;
    for(i=0;i<9;i++)
    {
        hf+=(i+1)*(10-i)*(charToInt(roll[i])+1)*(10-charToInt(roll[i]));
        hf=hf%1039;
    }
    return hf;
}

char* numToRoman(int i)
{
    if(i==0)return "I";
    if(i==1)return "II";
    if(i==2)return "III";
    if(i==3)return "IV";
    if(i==4)return "V";
    if(i==5)return "VI";
    if(i==6)return "VII";
    if(i==7)return "VIII";
}

float grdetocg(char* grd)
{
    if(grd=="AS"||grd=="AA")return 10;
    if(grd=="AB")return 9;
    if(grd=="BB")return 8;
    if(grd=="BC")return 7;
    if(grd=="CC")return 6;
    if(grd=="CD")return 5;
    if(grd=="DD")return 4;
    if(grd=="F")return 0;
}

/*
void spi_calc(Semester *s)
{
    float wght=0,crd=0;
    for(int i=0;i<s->grades.size();i++)
    {
        crd+=(float)charToInt(s->grades[i].first.C[0]);
        wght+=grdetocg(s->grades[i].second)*(float)charToInt(s->grades[i].first.C[0]);
    }
    s->credits=crd;
    s->spi=wght/crd;
}

void cpi_calc(Student *s, int sem)
{
    float wght=0,crd=0;
    for(int i=0;i<=sem;i++)
    {
        wght+=(s->sem[i].credits)*(s->sem[i].spi);
        crd+=(s->sem[i].credits);
    }
    s->sem[sem].cpi=wght/crd;
}
*/


int main()
{
    student stdtable[1039];
    department courseTable;
    char a,b,c,d,e,f,g,h;
    char str1[100]={'\0'},str2[100]={'\0'},str3[100]={'\0'},str4[100]={'\0'};
    FILE *students=fopen("students.csv","r");
    FILE *courses=fopen("courses.csv","r");
    FILE *gardes=fopen("grades.csv","r");

    int i=0;
    while(fscanf(students,"%[^,]%*c%c%[^\n]%*c",str1,&c,str2)==3)
    {
        printf("%d",i++);
    }

    return 0;
}