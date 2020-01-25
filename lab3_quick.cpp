#include<bits/stdc++.h>
#include<fstream>

using namespace std;

struct Course
{
    string ID,title;
    bool operator>(Course c)
    {
        int a=title.compare(c.title);
        return a>0;
    }
};

struct Grade
{
    string grade;
    Course c;
    bool operator<(Grade g)
    {
        int a=grade.compare(g.grade);
        return a<0;
    }
};

struct Department
{
    string name;
    vector<Course> cOffered;
};

struct Student
{
    string name,roll;
    vector<Grade> grdaes;

    bool operator<(Student s)
    {
        int a=roll.compare(s.roll);
        return a<0;
    }
};
typedef vector<Student> stdvector;

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

int coursePart(vector<Grade> *grades,int l, int u)
{
    Grade pivot=(*grades)[u];
    int i=l-1;
    for(int j=l;j<u;j++)
    {
        if((*grades)[j].c>pivot.c)
        {
            i++;
            swap((*grades)[i],(*grades)[j]);
        }
    }
    swap((*grades)[i+1],(*grades)[u]);
    return i+1;
}

int coursePart2(vector<Grade> *grades,int l, int u)
{
    Grade pivot=(*grades)[u];
    int i=l-1;
    for(int j=l;j<u;j++)
    {
        if((*grades)[j]<pivot)
        {
            i++;
            swap((*grades)[i],(*grades)[j]);
        }
    }
    i++;
    swap((*grades)[i],(*grades)[u]);
    return i;
}

int quickSortCourses(vector<Grade> *grades, int l, int u,bool gORc)
{
    if(l<u)
    {
        int m;
        if(gORc)m=coursePart(grades,l,u);
        else m=coursePart2(grades,l,u);
        quickSortCourses(grades,l,m-1,gORc);
        quickSortCourses(grades,m+1,u,gORc);
        
    }
}

void gradeSort(vector<Grade> *grades)
{
    for(int i=0;i<(*grades).size();i++)
    {
        for(int j=i+1;j<(*grades).size();j++)
        {
            if((*grades)[j].c.ID!=(*grades)[i].c.ID)
            {
                j--;
                quickSortCourses(grades,i,j,false);
                break;           
            }
        }
    }
}

int quickStds(stdvector *stds,int l, int u)
{
    Student pivot=(*stds)[u];
    int i=l-1;
    for(int j=l;j<u;j++)
    {
        if((*stds)[j]<pivot)
        {
            i++;
            swap((*stds)[i],(*stds)[j]);
        }
    }
    i++;
    swap((*stds)[i],(*stds)[u]);
    return i;
}

void quickSortStds(stdvector *stds, int l, int u)
{
    if(l<u)
    {
        int m=quickStds(stds,l,u);
        quickSortStds(stds,l,m-1);
        quickSortStds(stds,m+1,u);
    }
}

int main()
{
    stdvector stdTable[1039];
    stdvector final_stds;
    vector<Department> course_table;
    string str1,str2,str3,str4;
    fstream studs("students01.csv",ios::in);
    fstream courses("courses01.csv",ios::in);
    fstream grades("grades01.csv",ios::in);
    fstream outFile("output_q.csv",ios::out);

    while(getline(studs,str1,'\n'))
    {
        istringstream ss(str1);
        Student tmp;
        getline(ss,str2,',');
        tmp.name=str2;
        getline(ss,str2,',');
        tmp.roll=str2;
        stdTable[hRoll(tmp.roll)].push_back(tmp);
    }

    while(getline(courses,str1,'\n'))
    {
        istringstream ss(str1);
        Course tmp;
        string depName="";
        int i=0;
        getline(ss,str2,',');
        getline(ss,str2,',');
        tmp.ID=str2;
        depName.push_back(str2[0]);
        depName.push_back(str2[1]);
        getline(ss,str2,',');
        tmp.title=str2;
        for(i=0;i<course_table.size();i++)
        {
            if(course_table[i].name==depName)
            {
                course_table[i].cOffered.push_back(tmp);
                break;
            }
        }
        if(i==course_table.size())
        {
            Department dTmp;
            dTmp.name=depName;
            dTmp.cOffered.push_back(tmp);
            course_table.push_back(dTmp);
        }
    }

    while(getline(grades,str1,'\n'))
    {
        istringstream ss(str1);
        string depname="";
        int i=0,j=0,k=0;
        Course c;
        getline(ss,str2,',');
        getline(ss,str3,',');
        getline(ss,str4,',');
        depname.push_back(str3[0]);
        depname.push_back(str3[1]);
        int ind=hRoll(str2);
        for(i=0;i<stdTable[ind].size();i++)
        {
            if(stdTable[ind][i].roll==str2)
            {
                for(j=0;j<course_table.size();j++)
                {
                    if(course_table[j].name==depname)
                    {
                        for(k=0;k<course_table[j].cOffered.size();k++)
                        {
                            if(course_table[j].cOffered[k].ID==str3)
                            {
                                c=course_table[j].cOffered[k];
                                break;
                            }
                        }
                        break;
                    }
                }
                Grade gtmp;
                gtmp.c=c;
                gtmp.grade=str4;
                stdTable[ind][i].grdaes.push_back(gtmp);
                break;
            }
        }
    }

    for(int i=0;i<1039;i++)for(int j=0;j<stdTable[i].size();j++)
    {
        quickSortCourses(&(stdTable[i][j].grdaes),0,stdTable[i][j].grdaes.size()-1,true);
        gradeSort(&(stdTable[i][j].grdaes));
        final_stds.push_back(stdTable[i][j]);
    }
    quickSortStds(&final_stds,0,final_stds.size()-1);

    for(int i=0;i<final_stds.size();i++)
    {
        for(int j=0;j<final_stds[i].grdaes.size();j++)
        {
            outFile<<final_stds[i].name<<","<<final_stds[i].grdaes[j].c.title<<","<<final_stds[i].grdaes[j].grade<<endl;
        }
    }

    return 0;
}