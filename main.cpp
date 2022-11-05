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
#include<ctime>
#include<cstdlib>
using namespace std;

int main()
{
	srand((unsigned)time(0));
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
			&& strcmp(ptr2->d_name, "in1.txt")!=0 && strcmp(ptr2->d_name, "in2.txt")!=0
			&& strcmp(ptr2->d_name, "out2.txt")!=0
			&& strcmp(ptr2->d_name, "a.out")!=0 && strcmp(ptr2->d_name, "b.out")!=0)
			{
				files.push_back(dirs[i] + "/" + ptr2->d_name);
			}
		}
		closedir(pfile);

		//for(int j=0;j<files.size();j++)
			//cout<<files[j]<<endl;

		string sourcestr = "qwertyuioplkjhgfdsazxcvbnm";

		string informpath = dirs[i] + "/stdin_format.txt";
		fstream formf;
		formf.open(informpath, ios::in);
		if(!formf) cout<<"error"<<endl;
		
		vector<string> formstr;
		while(!formf.eof())
		{
			string tmpstr;
			formf >> tmpstr;
			formstr.push_back(tmpstr);
		}
		formf.close();

		fstream inf1;
		string inpath1 = dirs[i] + "/in1.txt";
		inf1.open(inpath1,ios::out);
		if(!inf1) cout<<"error"<<endl;

		for(int j=0;j<formstr.size();j++)
		{
			//cout<<formstr[j]<<endl;
			if(formstr[j]=="char")
			{	
				char ch = rand()%26+'a';
				inf1 << ch << " ";
			}
			else
			{
				string::size_type posit1, posit2, posit3;
				posit1 = formstr[j].find_first_of("(");
				posit2 = formstr[j].find_first_of(",");
				posit3 = formstr[j].find_first_of(")");

				string type = formstr[j].substr(0,posit1);
				
				if(type=="int")
				{
					int range1 = stoi(formstr[j].substr(posit1+1, posit2));
					int range2 = stoi(formstr[j].substr(posit2+1, posit3));

					inf1 << range1 + rand()%(range2-range1+1) << " ";
				}
				else if(type == "string")
				{
					int range1 = stoi(formstr[j].substr(posit1+1, posit2));
					int range2 = stoi(formstr[j].substr(posit2+1, posit3));

					int len = range1 + rand()%(range2-range1 + 1);
					inf1 << sourcestr.substr(0,len) << " ";
				}	
			}
		}
		inf1.close();

		fstream inf2;
		string inpath2 = dirs[i] + "/in2.txt";
		inf2.open(inpath2,ios::out);
		if(!inf2) cout<<"error"<<endl;

		for(int j=0;j<formstr.size();j++)
		{
			//cout<<formstr[j]<<endl;
			if(formstr[j]=="char")
			{	
				char ch = rand()%26+'a';
				inf2 << ch << " ";
			}
			else
			{
				string::size_type posit1, posit2, posit3;
				posit1 = formstr[j].find_first_of("(");
				posit2 = formstr[j].find_first_of(",");
				posit3 = formstr[j].find_first_of(")");

				string type = formstr[j].substr(0,posit1);
				
				if(type=="int")
				{
					int range1 = stoi(formstr[j].substr(posit1+1, posit2));
					int range2 = stoi(formstr[j].substr(posit2+1, posit3));

					inf2 << range1 + rand()%(range2-range1+1) << " ";
				}
				else if(type == "string")
				{
					int range1 = stoi(formstr[j].substr(posit1+1, posit2));
					int range2 = stoi(formstr[j].substr(posit2+1, posit3));

					int len = range1 + rand()%(range2-range1 + 1);
					inf2 << sourcestr.substr(0,len) << " ";
				}	
			}
		}
		inf2.close();

		
		for(int j=0;j<files.size();j++)
		{
			for(int k=j+1;k<files.size();k++)
			{
				bool judgeE = 1;
				string cmd1;
				string cmd2;

				string outpath1 = dirs[i] + "/out1.txt";
				string outpath2 = dirs[i] + "/out2.txt";

				cmd1 = "g++ " + files[j] + " -o "+ dirs[i]+"/a.out";
				//cout<<cmd1<<endl;	
				cmd2 = dirs[i] + "/a.out <"+inpath1 +" >"+outpath1;
				//cout<<cmd2<<endl;
				system(cmd1.c_str());
				system(cmd2.c_str());		
				
				cmd1 = "g++ " + files[k]+ " -o "+ dirs[i]+"/b.out";
				cmd2 = dirs[i]+ "/b.out <"+inpath1 +" >"+outpath2;
				system(cmd1.c_str());
				system(cmd2.c_str());

				//cout<<"Debug22"<<endl;a

				fstream outf1, outf2;
				string ans1, ans2;
				outf1.open(outpath1,ios::in);
				if(!outf1) cout<<"error"<<endl;
				char c;
				while(!outf1.eof()) 
				{
					outf1 >> c;
					ans1+=c;
				}
				outf1.close();
				//cout<<ans1<<endl;

				outf2.open(outpath2,ios::in);
				if(!outf2) cout<<"error"<<endl;
				while(!outf2.eof()) 
				{
					outf2 >> c;					
					ans2+=c;
				}
				outf2.close();
				//cout<<ans2<<endl;

				if(ans1.size()!=ans2.size()) 
					judgeE = 0;
				for(int m=0;m<ans1.size();m++)
				{
					if(ans1[m]!=ans2[m])
						judgeE = 0;
				}
	
				cmd2 = dirs[i] + "/a.out <"+inpath2 +" >"+outpath1;
				system(cmd2.c_str());		
				
				cmd2 = dirs[i]+ "/b.out <"+inpath2 +" >"+outpath2;
				system(cmd2.c_str());
				string ans3, ans4;

				outf1.open(outpath1,ios::in);
				if(!outf1) cout<<"error"<<endl;
				while(!outf1.eof()) 
				{
					outf1 >> c;
					ans3+=c;
				}
				outf1.close();
				//cout<<ans1<<endl;

				outf2.open(outpath2,ios::in);
				if(!outf2) cout<<"error"<<endl;
				while(!outf2.eof()) 
				{
					outf2 >> c;					
					ans4+=c;
				}
				outf2.close();
				//cout<<ans2<<endl;

				if(ans3.size()!=ans4.size()) 
					judgeE = 0;
				for(int m=0;m<ans3.size();m++)
				{
					if(ans3[m]!=ans4[m])
						judgeE = 0;
				}

				if(judgeE==1)
				{
					f1.open("output/equal.csv",ios::app);
					if(!f1) cout<<"error"<<endl;
					string::size_type posit1, posit2;
					posit1 = files[j].find_first_of("i");
					posit2 = files[k].find_first_of("i");
					f1 <<files[j].substr(posit1,1000)<<","<<files[k].substr(posit2,1000)<<"\n";
					f1.close();	
				}
				else
				{					
					f2.open("output/inequal.csv",ios::app);
					if(!f2) cout<<"error"<<endl;
					string::size_type posit1, posit2;
					posit1 = files[j].find_first_of("i");
					posit2 = files[k].find_first_of("i");
					f2 <<files[j].substr(posit1,1000)<<","<<files[k].substr(posit2,1000)<<"\n";
					
					f2.close();
				}

			}
		}

		files.clear();
		formstr.clear();

	}

	return 0;

}