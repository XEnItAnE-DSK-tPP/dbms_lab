#include<bits/stdc++.h>
#include<fstream>

using namespace std;

class Course
{
    public:
        string sem,L,T,P,C,ID,title;
};
typedef pair<Course,string> grade;

class Department
{
    public:
        string name;
        vector<Course> cOffered;
};

class Semester
{
    public:
        vector<grade> grades;
        float credits,spi,cpi;
};

class Student
{
    public:
        string name,roll;
        Semester sem[8];
};
typedef vector<Student> stdTable;

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

int hRoll(string roll)
{
    int hf=0;
    for(int i=0;i<roll.length();i++)
    {
        hf+=(i+1)*(10-i)*(charToInt(roll[i])+1)*(10-charToInt(roll[i]));
        hf=hf%1039;
    }
    return hf;
}

string numToRoman(int i)
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

float grdetocg(string grd)
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

int main()
{
    stdTable stdtable[1039];
    vector<Department> courseTable;
    string str1,str2,str3,str4;
    fstream studs("students.csv",ios::in);
    fstream courses("courses.csv",ios::in);
    fstream grades("grades.csv",ios::in);
    
    while(getline(studs,str1,'\n'))
    {
        istringstream ss(str1);
        Student tmp;
        getline(ss,str2,',');
        tmp.name=str2;
        getline(ss,str2,',');
        tmp.roll=str2;
        stdtable[hRoll(str2)].push_back(tmp);
    }

    while(getline(courses,str1,'\n'))
    {
        istringstream ss(str1);
        Course tmp;
        string depname="";
        int i;
        getline(ss,str2,',');
        tmp.sem=str2;
        getline(ss,str2,',');
        tmp.ID=str2;
        depname.push_back(str2[0]);
        depname.push_back(str2[1]);
        getline(ss,str2,',');
        tmp.title=str2;
        getline(ss,str2,',');
        tmp.L=str2;
        getline(ss,str2,',');
        tmp.T=str2;
        getline(ss,str2,',');
        tmp.P=str2;
        getline(ss,str2,',');
        tmp.C=str2;
        for(i=0;i<courseTable.size();i++)
        {
            if(courseTable[i].name==depname)
            {
                courseTable[i].cOffered.push_back(tmp);
                break;
            }
        }
        if(i==courseTable.size())
        {
            Department dtemp;
            dtemp.name=depname;
            dtemp.cOffered.push_back(tmp);
            courseTable.push_back(dtemp);
        }
    }

    while(getline(grades,str1,'\n'))
    {
        istringstream ss(str1);
        string depname="";
        int i,j,k;
        Course c;
        getline(ss,str2,',');
        getline(ss,str3,',');
        getline(ss,str4,',');
        int ind=hRoll(str2);
        depname.push_back(str3[0]);
        depname.push_back(str3[1]);
        for(int i=0;i<stdtable[ind].size();i++)
        {
            if((stdtable[ind])[i].roll==str2)
            {
                for(int j=0;j<courseTable.size();j++)
                {
                    if(courseTable[j].name==depname)
                    {
                        for(int k=0;k<courseTable[j].cOffered.size();k++)
                        {
                            if((courseTable[j]).cOffered[k].ID==str3)
                            {
                                c=(courseTable[j]).cOffered[k];
                                break;
                            }
                        }
                        break;
                    }
                }
                grade grd;
                grd.second=str4;
                grd.first=c;
                int semno=charToInt(c.sem[0])-1;
                (((stdtable[ind])[i]).sem[semno]).grades.push_back(grd);
                break;
            }
        }
    }

    for(int i=0;i<1039;i++)
    {
        for(int j=0;j<stdtable[i].size();j++)
        {
            Semester s;
            string fileName=(stdtable[i])[j].roll+".txt";
            fstream file(fileName,ios::out);
            file<<"Name:\t"<<(stdtable[i])[j].name<<endl;
            file<<"Roll Number:\t"<<(stdtable[i])[j].roll<<endl<<endl;
            for(int k=0;k<8;k++)
            {
                
                spi_calc(&((stdtable[i])[j].sem[k]));
                cpi_calc(&((stdtable[i])[j]),k);
                s=(stdtable[i])[j].sem[k];
                file<<"Semester "<<numToRoman(k)<<endl;
                file<<"Course Title\t|\tCourse ID\t|\tC\t|\tGrade"<<endl;
                for(int l=0;l<s.grades.size();l++)
                {
                    Course c=s.grades[l].first;
                    file<<c.title<<"\t\t"<<c.ID<<"\t\t"<<c.C<<"\t\t"<<s.grades[l].second<<endl;
                }
                file<<endl;
            }
            file<<"\t";
            for(int k=0;k<8;k++)file<<numToRoman(k)<<"\t";
            file<<endl;
            file<<"SPI";
            for(int k=0;k<8;k++)file<<"\t"<<(stdtable[i])[j].sem[k].spi;
            file<<endl;
            file<<"CPI";
            for(int k=0;k<8;k++)file<<"\t"<<(stdtable[i])[j].sem[k].cpi;
        }
    }

    return 0;
}