#include<fstream.h>
#include<string.h>
#include<process.h>
#include<stdio.h>
#include<conio.h>
#include<iomanip.h>

void main_menu();

class customer
{
	char name[80];
	char prof[80];
	char contact_no[11];
public:
	void insert(char n[80],char pf[80],char no[11])
		{
		strcpy(name,n);
		strcpy(prof,pf);
		strcpy(contact_no,no);
		}
	void display()
		{
		cout<<"\nCustomer Name: "<<name;
		cout<<"\nProfession/Occupation: "<<prof;
		cout<<"\nContact No. "<<contact_no<<endl;
		}
};

class room
	{
	int roomno;
	float base;
	float tax;
	float rent;
	char status[10];
	public:
		customer c;
		room()
			{
			strcpy(status,"VACANT");
			}
		void calc()
			{
			tax=(12.5*base)/100;
			rent=tax+base;
			}
		void occ()
			{
			strcpy(status,"OCCUPIED");
			}
		/*void vac()
			{
			strcpy("VACANT",status);
			}*/

		void init(int x,float p)
		{
			roomno=x;
			base=p;
			calc();
			strcpy(status,"VACANT");
		}
		void details()
		{
		cout<<"\nRoom No.: "<<roomno;
		cout<<"\nRent: "<<rent;
		cout<<"\nAllotment Status: "<<status<<endl;
		if(strcmpi(status,"OCCUPIED")==0)
			c.display();
		}
		int getroomno()
			{
			return roomno;
			}
		int st()
			{
			return(strcmpi(status,"OCCUPIED"));
			}
}temp;

room delux_non_ac,delux_ac,super_delux,suite;

void fileopen()
{  int i;
	fstream fp("Hotel.dat",ios::in|ios::out|ios::binary);

	if(!fp)
		{
		cerr<<"Unable to LINK file!\n";
		exit(-1);
		}
	for(i=101;i<=110;i++)
		{
		delux_non_ac.init(i,1299.49);
		fp.write((char*)&delux_non_ac,sizeof(room));
		}
	for(i=201;i<=208;i++)
		{
		delux_ac.init(i,1599.49);
		fp.write((char*)&delux_ac,sizeof(room));
		}
	for(i=301;i<=305;i++)
		{
		super_delux.init(i,2299.49);
		fp.write((char*)&super_delux,sizeof(room));
		}
	for(i=401;i<=403;i++)
		{
		suite.init(i,2999.49);
		fp.write((char*)&suite,sizeof(room));
		}
	fp.close();
}

void file_retreive()
{
	fstream fin("Hotel.dat",ios::binary|ios::in);
	while(!fin.eof())
		{
		fin.read((char*)&temp,sizeof(temp));
		temp.details();
		cout<<"-*-*-*-*-*-*-*-*-*-"<<endl;
		}
	fin.close();
	cout<<"Input \'M\' to go to Main MENU\n";
	char x;
	cin>>x;
	if(x=='M'||x=='m') main_menu();
}



void checkin()
{  fstream fp("Hotel.dat",ios::out|ios::binary|ios::in);
	clrscr();
	cout<<"Enter ROOM type!\n";
	cout<<"\n1.Delux-NON AC\n2.Delux-AC\n3.Super Delux\n4.Suite\n";
	char ch;
	cin>>ch;
	switch(ch)
		{
		case '1':clrscr();
					long pos;
					rep:cout<<"Input a VACANT room no!\n";
					int n;cin>>n;
					if(n<101||n>110)
						{
							cout<<"Enter a VALID room no!\n";
							goto rep;
						}
					while(!fp.eof())
					{
						fp.read((char*)&temp,sizeof(temp));
						if(n==temp.getroomno())
							{
							if(temp.st()==0)
								{
								fp.seekg(0,ios::beg);
								goto rep;
								}
							pos=fp.tellg();
							char name[80],pf[80],no[11];
							cout<<"Room Type: DELUX-NON-AC\n";
							cout<<"Enter Customer Name:\n";
							gets(name);
							cout<<"Profession/Occupation:\n";
							gets(pf);
							cout<<"Contact No.:\n";
							gets(no);
							temp.c.insert(name,pf,no);
							temp.occ();
							temp.details();
							fp.seekg(pos);
							fp.write((char*)&temp,sizeof(room));
							cout<<"SUCCESS!\n";
							cout<<"Input \'M\' to go to Main MENU\n";
							char x;
							cin>>x;
							if(x=='M'||x=='m') main_menu();
							}
					}
		 }
}




void main_menu()
{
char ch;
clrscr();

repeat://label
cout<<"Welcome to KING AK\'s \'PARADISE\'\n";
cout<<"1.New Customer-Check IN\n2.Existing Customer-Check OUT\n3.Room Details\n4.Exit\n";
cout<<"Enter your choice\n";
cin>>ch;
switch(ch)
	{
	case '1':checkin();
			 break;
	case '2'://checkout();
			 break;
	case '3':clrscr();
				file_retreive();
			 break;
	case '4':clrscr();
				cout<<setw(28)<<"Please close the WINDOW!"<<endl;
				cout<<"#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#"<<endl;
				exit(0);
			 break;
	default:cerr<<"\nPlease Enter a valid Choice!\n\n";
			 goto repeat;
			 break;
	}
}


void main()
{
main_menu();
}

