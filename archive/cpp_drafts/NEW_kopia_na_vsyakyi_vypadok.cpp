#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <vector>
#include <fstream>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void print_matr_1 (vector <vector <T> > & vArray){   //виведенн€ матриц≥ на екран
for (int i=0; i<vArray.size(); i++) 
{for (int j=0; j<vArray[i].size(); j++)
{if (j==vArray[i].size()-1) {cout<<"|"<<vArray[i][j]<<" ";}
else {cout<<round(vArray[i][j]*1000.00)/1000.00<<"\t";}
}//end of for (j)
cout<<endl;

}//end of for (i)
}//end of print_matr_1
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void print_matr_2 (vector <vector <T> > & vArray){   //виведенн€ матриц≥ на екран
for (int i=0; i<vArray.size(); i++) 
{for (int j=0; j<vArray[i].size(); j++)
{if (j==vArray[i].size()-1) {cout<<"|"<<vArray[i][j]<<" ";}
else {cout<<round(vArray[i][j]*1000.00)/1000.00<<"\t";}
}//end of for (j)
cout<<endl;
if (i==vArray.size()/2-1) {cout<<endl;}
}//end of for (i)
}//end of print_matr_1
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void read_matr (vector <vector <T> > & vArray) {
ifstream fin;
fin.open("matr.txt");
string str="";

if (!fin.is_open()) {cout<<"Cannot read from the file!\n"<<endl;}
int a,b;
fin>>a>>b; //розм≥р матриц≥, без врахуванн€ в≥льних член≥в
vArray.resize(a);
for (int i=0; i<vArray.size(); i++)
{vArray[i].resize(b+1);
for (int j=0; j<vArray[i].size(); j++)
{fin>>str; //зчитали число €к р€док
bool flag=true; 

for (int k=0; k<str.length(); k++) {
if (str[k]=='/') 
		{string ch="";
		 string zn="";
		 string dil="/";
		 ch=str.substr(0,str.find(dil));
		 zn=str.substr(str.find(dil)+1);
		 vArray[i][j]=atof(ch.c_str())/atof(zn.c_str());
		 flag=false;
		}//end of if (a[k]=='/')
}//end of for(k)
if (flag==true) {vArray[i][j]=atof(str.c_str());}
}//end of for(j)
vArray[i][vArray[i].size()-1]=vArray[i][vArray[i].size()-1]*(-1); //зм≥нюЇмо коЇф≥ц≥Їнти в≥льних член≥в системи р≥вн€нь
}
fin.close();
}//end of read_matr
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void identity_matr (vector <vector <T> > & vArray){
for (int i=0; i<vArray.size(); i++) 
{for (int j=0; j<vArray[i].size(); j++)
{if (i==j) {vArray[i][j]=1;}
else {vArray[i][j]=0;}
}//end of for (j)
}//end of for (i)
	
}//end of identity_matr
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void fill_matr(vector <vector <T> > & vArray, vector <vector <T> > & vBrray, vector <vector <T> > & vCrray){
for (int i=0; i<vCrray.size()/2; i++) 
{for (int j=0; j<vCrray[i].size(); j++)
{vCrray[i][j]=vArray[i][j];
}//end of for (j)
}//end of for (i)


for (int i=vCrray.size()/2; i<vCrray.size(); i++) 
{for (int j=0; j<vCrray[i].size(); j++)
{vCrray[i][j]=vBrray[i-vCrray.size()/2][j]; 
}//end of for (j)
}//end of for (i)
	
}//end of fill_matr
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void initialization (vector <vector <T> > & vArray,int rows, int cols) {
vArray.resize(rows);
for (int i=0; i<vArray.size(); i++) 
{vArray[i].resize(cols);
for (int j=0; j<vArray[i].size(); j++)	
{vArray[i][j]=0;
}//end of for (j)
}//end of for (i)
}//end of initialization
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
int main () {
vector <vector <double> >M(0);//матриц€ M, ≥з системи р≥вн€нь + в≥льн≥ члени
read_matr(M);
cout<<"------------------------------------------- MATRIX PSEUDOBASIC ALGORITHMS -------------------------------------------"<<endl;	
cout<<"THE INITIAL MATRIX M:\n";
print_matr_1(M);	
cout<<endl<<endl;
int m=M[0].size()-1;
vector <vector <double> >Od(m, vector <double> (m+1,0)); //одинична матриц€ Od, = матриц≥ M + колонка ≥з нул≥в
identity_matr(Od);
cout<<"IDENTITY MATRIX Od:\n";
print_matr_1(Od);	
cout<<endl<<endl;


vector <vector <vector <double> > >A(1, vector <vector <double> >(m*2, vector <double> (m+1,0))); //масив ус≥х перетворень
int k=0;
fill_matr(M,Od,A[k]);
cout<<"-------------------------------- ITERATION k = "<<k<<" --------------------------------"<<endl;
cout<<"MATRIX A["<<k<<"]:\n";
print_matr_2(A[k]);	
cout<<endl<<endl;



while (k!=m)
{A.resize(A.size()+1);
k=k+1;
initialization(A[k],m*2,(m+1));
cout<<"-------------------------------- ITERATION k = "<<k<<" --------------------------------"<<endl;
cout<<"MATRIX A["<<k<<"]:\n";
for (int r=0; r<m+1;r++)
{if (r==(k-1)) 
	{for (int i=0; i<2*m; i++) {A[k][i][k-1]=A[k-1][i][k-1]/A[k-1][k-1][k-1];}}//end of if(r==(k-1))
	
else if(r==m) 
	{for (int i=0; i<2*m; i++) {A[k][i][m]=A[k-1][i][m]-A[k-1][i][k-1]/A[k-1][k-1][k-1]*A[k-1][k-1][m];  
	                            //A[k][i][m]=round(A[k][i][m]*100000.00)/100000.00;
	                            if (A[k][i][m]==-0){A[k][i][m]=0;}
	                           }}//end of if(r==m)
	
else {for (int i=0; i<2*m; i++) { A[k][i][r]=A[k-1][i][r]-A[k-1][i][k-1]/A[k-1][k-1][k-1]*A[k-1][k-1][r];}}//end of esle (r!=k-1)
}//end of for (r)
print_matr_2(A[k]);
	
} //end of while






return 0;	
}
