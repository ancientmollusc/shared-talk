#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define ESC 27
using namespace std;
class rhands//recievers hand shake;sent=s,recieved=r,readytorecieve=q
{
void iht()//initial handshake terminate
{
char hconst='!';//initial reciever const
fstream hsfile;
hsfile.open(hsfname,ios::out|ios::binary);
hsfile.write((char*)&hconst,sizeof(char));
hsfile.close();	
}
bool ihi()//initial handshake initiate
{
char hconst;
fstream hsfile;
hsfile.open(hsfname,ios::in|ios::binary);
hsfile.read((char*)&hconst,sizeof(char));
hsfile.close();	
if(hconst=='?')//initial sender const
return 1;
return 0;
}
bool ihcr()//initial handshake check r
{
char hconst;
fstream hsfile;
hsfile.open(hsfname,ios::in|ios::binary);
hsfile.read((char*)&hconst,sizeof(char));
hsfile.close();	
if(hconst=='~')//reciever2 const
return 1;
return 0;
}
public:	
bool cids()//check if data sent
{
char hconst;
fstream hsfile;
hsfile.open(hsfname,ios::in|ios::binary);
hsfile.read((char*)&hconst,sizeof(char));
hsfile.close();
if(hconst=='s')
return 1;
return 0;	
}
void tdr()//tell data recieved
{
char hconst='r';
fstream hsfile;
hsfile.open(hsfname,ios::out|ios::binary);
hsfile.write((char*)&hconst,sizeof(char));
hsfile.close();	
}
void tdrtr()//tell data ready to be recieved
{
char hconst='q';
fstream hsfile;
hsfile.open(hsfname,ios::out|ios::binary);
hsfile.write((char*)&hconst,sizeof(char));
hsfile.close();	
}
bool initialhandshake()
{
cout<<'\n';	
while(!ihi())
{
cout<<'\r'<<'/';
cout<<'\r'<<'|';
cout<<'\r'<<'\\';
cout<<'\r'<<'|';	
}
cout<<'\r'<<' '<<'\r';
iht();
while(!ihcr());	
return true;
}
char hsfname[15];
};
class recievepc
{
public:	
void rp(char &data)//recievepacket
{
fstream dfile;
dfile.open(dfname,ios::in|ios::binary);
dfile.read((char*)&data,sizeof(char));
dfile.close();
}
char dfname[15];	
};
bool senddata(char hsfname[15],char dfname[15],int mode,string password)
{
char data;
string output;
output="";
rhands h1;
strcpy(h1.hsfname,hsfname);
recievepc r1;
strcpy(r1.dfname,dfname);
if(h1.initialhandshake())
cout<<"success\n";
if(mode==0)
{
h1.tdrtr();	
while(!h1.cids());
r1.rp(data);
h1.tdr();
cout<<data;
return true;	
}
if(mode==1)
{
while(output!=password)
{
h1.tdrtr();	
while(!h1.cids());
r1.rp(data);
h1.tdr();
cout<<data;
if(data=='\n')
output="";
else
output.push_back(data);
}
return true;	
}
return false;
}
int main()
{
bool scv;
char hsfname[15],dfname[15];
int mode;
string password;	
cout<<"enter hfilename: ";
gets(hsfname);
cout<<"\nenter dfilename: ";	
gets(dfname);
cout<<"\nenter password: ";
cin>>password;
cout<<"\nenter mode: ";
cin>>mode;
scv=senddata(hsfname,dfname,mode,password);	
remove(hsfname);
remove(dfname);
cout<<'\n';
return scv;
}
