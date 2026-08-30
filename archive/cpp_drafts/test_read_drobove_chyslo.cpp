#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main () {
vector <double> T(5,0);
ifstream fin;
fin.open("drib.txt");
string a="";

for (int i=0; i<T.size(); i++)
{fin>>a; cout<<"a = "<<a<<endl; 
bool flag=true; 
for (int j=0; j<a.length(); j++)
 	{if (a[j]=='/') 
	 			{string ch="";
				 string zn="";
				 string dil="/";
				 ch=a.substr(0,a.find(dil));
				 zn=a.substr(a.find(dil)+1);
				 T[i]=atof(ch.c_str())/atof(zn.c_str());
				 flag=false;
				} //end of if (a[j]=='/')
	 			
 	 }//end of for (j)
 	 
if (flag==true) {T[i]=atof(a.c_str());}
}//end of for (i)

cout<<endl;
for (int i=0; i<T.size(); i++) {
cout<<"T["<<i<<"] = "<<T[i]<<endl;	
}


fin.close();	
return 0;	
}
