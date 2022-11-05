#define _CRT_NO_SECURE_WARNING

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<stdio.h>
#include<string>
#include<cstring>
#include<dirent.h>
#include<vector>
#include<unistd.h>
using namespace std;

int main()
{
	string buffer;
	buffer = getcwd(NULL,0);	
	
	if(access((buffer+"/output").c_str(),0)==-1)
		system(("mkdir "+buffer+"/output").c_str());

	fstream f1,f2;
	f1.open("output/equal.csv",ios::out);
	if(!f1) 
	{
		cout<<"error"<<endl;
		exit(1);
	}
	f1 << "file1,file2\n";
	f1.close();
	f2.open("output/inequal.csv",ios::out);
	if(!f2) 
	{
		cout<<"error"<<endl;
		exit(1);
	}
	f2 << "file1, file2\n";
	f2.close();

	string inipath = buffer + "/input";
	//string inipath = "/home/njucs/SElab4/input";
	DIR *pdir;
	struct dirent *ptr;

	if(!(pdir = opendir(inipath.c_str()))) cout<<"error"<<endl;

	vector<string> dirs;
	while((ptr = readdir(pdir))!= 0 )
	{
		if(strcmp(ptr->d_name, ".")!=0 && strcmp(ptr->d_name,"..")!=0)
		{
			dirs.push_back(inipath + "/" + ptr->d_name);
		}
	}
	closedir(pdir);

	for(int i=0;i<dirs.size();i++)
	{
		DIR *pfile;
		struct dirent *ptr2;
		if(!(pfile = opendir(dirs[i].c_str()))) cout<<"error"<<endl;

		vector<string> files;
		while((ptr2 = readdir(pfile))!= 0 )
		{
			if(strcmp(ptr2->d_name, ".")!=0 && strcmp(ptr2->d_name,"..")!=0 && 
			strcmp(ptr2->d_name, "stdin_format.txt")!=0 && strcmp(ptr2->d_name, "out1.txt")!=0
			&& strcmp(ptr2->d_name, "in.txt")!=0 && strcmp(ptr2->d_name, "out2.txt")!=0
			&& strcmp(ptr2->d_name, "a.out")!=0 && strcmp(ptr2->d_name, "b.out")!=0)
			{
				files.push_back(dirs[i] + "/" + ptr2->d_name);
			}
		}
		closedir(pfile);

		for(int j=0;j<files.size();j++)
			cout<<files[j]<<endl;
	}

	return 0;

}