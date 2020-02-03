#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

using namespace std;

char *stdBuff;
char *courseBuff;
char *gradeBuff;
int buff=4096;

int main()
{   
    //length of line of students
    int students=open("./students03.csv",O_RDONLY);
    int countStd;
    stdBuff=(char*)malloc(buff*sizeof(char));
    read(students,stdBuff,buff);
    for(int i=0;i<buff;i++)if(stdBuff[i]=='\n')
    {
        countStd=i+1;
        break;
    }
    free(stdBuff);
    stdBuff=(char*)malloc(countStd*sizeof(char));
    close(students);

    //length of line of courses
    int courses=open("./courses03.csv",O_RDONLY);
    int countCou;
    courseBuff=(char*)malloc(buff*sizeof(char));
    read(students,courseBuff,buff);
    for(int i=0;i<buff;i++)if(courseBuff[i]=='\n')
    {
        countCou=i+1;
        break;
    }
    free(courseBuff);
    courseBuff=(char*)malloc(countCou*sizeof(char));
    close(courses);

    //length of line of grades;
    int grades=open("./grades03.csv",O_RDONLY);
    int countGrades;
    gradeBuff=(char*)malloc(buff*sizeof(char));
    read(students,gradeBuff,buff);
    for(int i=0;i<buff;i++)if(gradeBuff[i]=='\n')
    {
        countGrades=i+1;
        break;
    }
    free(gradeBuff);
    gradeBuff=(char*)malloc(countGrades*sizeof(char));
    close(grades);

    students=open("./students03.csv",O_RDONLY);
    cout<<"a"<<endl;
    while(read(students,stdBuff,countStd))
    {
        char roll[14];
        strcpy(roll,stdBuff+countStd-10);
        roll[9]='.';
        roll[10]='t';
        roll[11]='x';
        roll[12]='t';
        roll[13]='\0';
        int tsc=open(roll,O_RDWR|O_CREAT|O_SYNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
        write(tsc,"Name: ",6);
        write(tsc,stdBuff,countStd-11);
        write(tsc,"\n",1);
        write(tsc,"Roll no: ",9);
        write(tsc,roll,9);
        write(tsc,"\n\n",2);
        vector< vector< pair<char*,int> > > gradebook(8);
        courses=open("./courses03.csv",O_RDONLY);
        grades=open("./grades03.csv",O_RDONLY);
    }
    return 0;
}
