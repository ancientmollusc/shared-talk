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
class shands//senders hand shake;sent=s,recieved=r,readytorecieve=q
{
void ihi()//initial handshake initiate
{
char hconst='?';//initial sender const
fstream hsfile;
hsfile.open(hsfname,ios::out|ios::binary);
hsfile.write((char*)&hconst,sizeof(char));
hsfile.close();	
}
bool iht()//initial handshake terminate
{
char hconst;
fstream hsfile;
hsfile.open(hsfname,ios::in|ios::binary);
hsfile.read((char*)&hconst,sizeof(char));
hsfile.close();	
if(hconst=='!')//initial reciever const
return 1;
return 0;
}
void ihcs()//initial handshake check s
{
char hconst='~';//sender2 const
fstream hsfile;
hsfile.open(hsfname,ios::out|ios::binary);
hsfile.write((char*)&hconst,sizeof(char));
hsfile.close();
}
public:	
void tds()//tell data sent
{
char hconst='s';//data sent const in file
fstream hsfile;
hsfile.open(hsfname,ios::out|ios::binary);
hsfile.write((char*)&hconst,sizeof(char));
hsfile.close();	
}
bool cidr()//check if data recieved
{
char hconst;
fstream hsfile;
hsfile.open(hsfname,ios::in|ios::binary);
hsfile.read((char*)&hconst,sizeof(char));
hsfile.close();	
if(hconst=='r')//recieved
return 1;
return 0;
}
bool cidrtr()//check if data ready to be recieved
{
char hconst;
fstream hsfile;
hsfile.open(hsfname,ios::in|ios::binary);
hsfile.read((char*)&hconst,sizeof(char));
hsfile.close();	
if(hconst=='q')//ready to recieve
return 1;
return 0;
}
bool initialhandshake()
{
cout<<'\n';	
ihi();	
while(!iht())
{
cout<<'\r'<<'/';
cout<<'\r'<<'|';
cout<<'\r'<<'\\';
cout<<'\r'<<'|';	
}
cout<<'\r'<<' '<<'\r';	
ihcs();
return true;
}
char hsfname[15];
};
class sendpc
{
public:	
void sp(char data)//sendpacket
{
fstream dfile,lfile;
dfile.open(dfname,ios::out|ios::binary);
lfile.open(lfname,ios::out|ios::binary|ios::app);
dfile.write((char*)&data,sizeof(char));
lfile.write((char*)&data,sizeof(char));
dfile.close();
lfile.close();
}
char dfname[15],lfname[15];	
};
bool senddata(char hsfname[15],char dfname[15],char lfname[15],int mode,string password)
{
char data;
int EOFcheck=0;
string input;
input="";
shands h1;
strcpy(h1.hsfname,hsfname);
sendpc s1;
strcpy(s1.dfname,dfname);
strcpy(s1.lfname,lfname);
if(h1.initialhandshake())
cout<<"success\n";
if(mode==0)
{
int c;	
while ( (c = getchar()) != '\n' && c != EOF ){ }
data=getchar();
while(!h1.cidrtr());
s1.sp(data);
h1.tds();
while(!h1.cidr());
return true;	
}
if(mode==1)
{
getchar();	
while(input!=password)
{	
if((data=getchar())!='\n')
EOFcheck=1;
else
input="";
while(!h1.cidrtr());
s1.sp(data);
h1.tds();
while(!h1.cidr());	
if(EOFcheck==1)
{
input.push_back(data);
EOFcheck=0;
}
}
return true;	
}
return false;
}
int main()
{
bool scv;
char hsfname[15],dfname[15],lfname[15];
int mode;
string password;
cout<<"enter hfilename: ";
gets(hsfname);
cout<<"\nenter dfilename: ";	
gets(dfname);	
cout<<"\nenter lfilename: ";
gets(lfname);
cout<<"\nenter password: ";
cin>>password;
cout<<"\nenter mode: ";
cin>>mode;
remove(hsfname);
remove(dfname);
scv=senddata(hsfname,dfname,lfname,mode,password);
remove(hsfname);
remove(dfname);
return scv;
}
