#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <vector>
#include <fstream>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void print_matr_1 (vector <vector <T> > & vArray){   //виведення матриці на екран
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
void print_matr_2 (vector <vector <T> > & vArray){   //виведення матриці на екран
for (int i=0; i<vArray.size(); i++) 
{for (int j=0; j<vArray[i].size(); j++)
{if (j==vArray[i].size()-1) {cout<<"|"<<vArray[i][j]<<" ";}
else { if (vArray[i][j]==-0) {vArray[i][j]=0;} cout<<round(vArray[i][j]*1000.00)/1000.00<<"\t";}
}//end of for (j)
cout<<endl;
if (i==vArray.size()/2-1) {cout<<endl;}
}//end of for (i)
}//end of print_matr_2
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void read_matr (vector <vector <T> > & vArray) {
ifstream fin;
fin.open("matr.txt");
string str="";

if (!fin.is_open()) {cout<<"Cannot read from the file!\n"<<endl;}
int a,b;
fin>>a>>b; //розмір матриці, без врахування вільних членів
vArray.resize(a);
for (int i=0; i<vArray.size(); i++)
{vArray[i].resize(b+1);
for (int j=0; j<vArray[i].size(); j++)
{fin>>str; //зчитали число як рядок
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
vArray[i][vArray[i].size()-1]=vArray[i][vArray[i].size()-1]*(-1); //змінюємо коєфіцієнти вільних членів системи рівнянь
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
template <typename T>
void print_matr_2_new (vector <vector <T> > & vArray){   //виведення матриці на екран із певним декором
cout<<"\t";                           //трішки декору для виведення номерів стовпців
for (int j=0; j<vArray[0].size(); j++) 
{cout<<"["<<j<<"]\t";}
cout<<endl;

for (int i=0; i<vArray.size(); i++) 
{cout<<"["<<i<<"]\t"; //виведення номерів рядків
for (int j=0; j<vArray[i].size(); j++)
{if (j==vArray[i].size()-1) {cout<<"|"<<vArray[i][j]<<" ";}
else { if (vArray[i][j]==-0) {vArray[i][j]=0;} cout<<round(vArray[i][j]*1000.00)/1000.00<<"\t";}
}//end of for (j)
cout<<endl;
if (i==vArray.size()/2-1) {cout<<endl;}
}//end of for (i)
}//end of print_matr_2_new
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void fill_Ob_matr (vector <vector <T> > & vArray, vector <vector <T> > & vBrray) { //заповнення оберненої матриці
for (int i=vBrray.size()/2; i<vBrray.size(); i++) {
for (int j=0; j<vBrray[i].size()-1; j++){
vArray[i-vBrray.size()/2][j]=vBrray[i][j];
}//end of for (j)	
}//end of for (i)
}//end of fill_Ob_matr_plus_sol 
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void fill_Ob_matr_plus_sol (vector <vector <T> > & vArray, vector <vector <T> > & vBrray) { //заповнення оберненої матриці
for (int i=vBrray.size()/2; i<vBrray.size(); i++) {
for (int j=0; j<vBrray[i].size(); j++){
vArray[i-vBrray.size()/2][j]=vBrray[i][j];
}//end of for (j)	
}//end of for (i)
}//end of fill_Ob_matr 
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void print_matr_3 (vector <vector <T> > & vArray){ // для виведення оберененої матриці на екран 
for (int i=0; i<vArray.size(); i++) 
{for (int j=0; j<vArray[i].size(); j++)
{
cout<<round(vArray[i][j]*1000.00)/1000.00<<"\t";
}//end of for (j)
cout<<endl;

}//end of for (i)	
}
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void fill_Vec_Sol (vector <vector <T> > & vArray, vector <vector <T> > & vBrray){ //заповнення вектору рішень
for (int i=vBrray.size()/2; i<vBrray.size(); i++) {
for (int j=vBrray[i].size()-1; j<vBrray[i].size(); j++){
vArray[i-vBrray.size()/2][0]=vBrray[i][j];
}//end of for (j)	
}//end of for (i)	
}//end of fill_Vec_Sol
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void print_vect (vector <vector <T> > & vArray){ //виведення вектору рішень
for (int i=0; i<vArray.size(); i++) 
{for (int j=0; j<vArray[i].size(); j++)
{
cout<<vArray[i][j]<<"\t";
}//end of for (j)
cout<<endl;

}//end of for (i)
	
}//end of print_vect
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void print_line(vector <T> & vArray){
for (int i=0;i<vArray.size(); i++)
{cout<<vArray[i]<<"\t";
}//end of for (i)	
	
}//end of print_line
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void multiply_line_matr(vector <T>  & vArray, vector <vector <T> > & vBrray, vector <T> & vCrray){ //мн. вект. a(k) * Обер. матр. = alpha(k)
for (int i=0; i<vCrray.size(); i++) //ініціалізація вектору результату
{vCrray[i]=0;}


for (int i=0; i<vBrray[0].size(); i++){
for (int j=0; j<vArray.size(); j++)	
{
vCrray[i]=vCrray[i]+vArray[j]*vBrray[j][i];	
}//end of for (j)
}//end of for (i)
	
}//end of multiply_line_matr 
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void multiply_line_vect (vector <T>  & vArray, vector <vector <T> >  & vBrray, vector <T> &c, vector <T> &delta){ //множення a(k) * u(0) - c(k) = delta (k)
delta[0]=0;

for (int i=0; i<1; i++){
for (int j=0; j<vArray.size(); j++)	
{
delta[0]=delta[0]+vArray[j]*vBrray[j][i];	
//cout<<"delta[0] = "<<delta[0]<<endl;
}//end of for (j)
}//end of for (i)

delta[0]=delta[0]+c[0]; // бо у нас у матриці воно (c[0]) зберігається уже як від'ємне число, тому тут додаємо 
//delta[0]=-1*delta[0];  //?????????????????
}//end of multiply_line_vect
//////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void recalculation (vector <vector <T> > & vArray, int k, vector <vector <T> > & vBrray, vector <vector <T> >  & vUrray){ //перерахунок k-го рядка
vector <T> temp1(vArray[k].size()-1,0); //масив для коєфіцієнтів рядка a(k)
vector <T> temp11(temp1.size()); //його порожня копія, сюди запишеться результат множення вектору temp1 на обернену матрицю
vector <T> temp2(1,0); //масив, що складається із вільного члена с(k)
vector <T> temp22(temp2.size()); //його порожня копія, сюди запишеться результат після певних дій над вектором temp2

for (int i=0; i<vArray[k].size();i++){ //копіюємо значення вибраного рядка у два масиви
if (i==vArray[k].size()-1) {temp2[0]=vArray[k][i];}	
else {temp1[i]=vArray[k][i];}	
}//end of for (i)

cout<<"STEP 2.1. Import of the chosen line:"<<endl;
cout<<"["<<k<<"]\t";
print_line(temp1);
cout<<"|";
print_line(temp2);
cout<<endl;

cout<<"STEP 2.2. Changing the chosen line:"<<endl;
cout<<"["<<k<<"]\t";
multiply_line_matr(temp1,vBrray,temp11); //виконуємо множення вектору a(k) * Обернену матрицю = alpha(k)
multiply_line_vect(temp1, vUrray, temp2, temp22);
print_line(temp11);
cout<<"|";
print_line(temp22);
cout<<endl;

cout<<"STEP 2.3. New matrix for the future steps:"<<endl;
for (int i=0; i<vArray[k].size();i++){ //змінюємо нашу матрицю новим рядком
if (i==vArray[k].size()-1) {vArray[k][i]=temp22[0];}	
else {vArray[k][i]=temp11[i];}	
}//end of for (i)
print_matr_2_new(vArray);
cout<<endl<<endl;

}
//////////////////////////////////////////////////////////////////////////////////////////
int main () {
vector <vector <double> >M(0);//матриця M, із системи рівнянь + вільні члени
read_matr(M);
cout<<"------------------------------------------- MATRIX PSEUDOBASIC ALGORITHMS -------------------------------------------"<<endl;	
cout<<"THE INITIAL MATRIX M:\n";
print_matr_1(M);	
cout<<endl<<endl;
int m=M[0].size()-1;
vector <vector <double> >Od(m, vector <double> (m+1,0)); //одинична матриця Od, = розміру M + колонка із нулів
identity_matr(Od);
cout<<"IDENTITY MATRIX Od:\n";
print_matr_1(Od);	
cout<<endl<<endl;


vector <vector <vector <double> > >A(1, vector <vector <double> >(m*2, vector <double> (m+1,0))); //масив усіх перетворень
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


cout<<endl<<endl;
cout<<"------------------------------------------- CHANGING THE ROWS OF THE MATRIX -------------------------------------------"<<endl;
cout<<"\tTHE SOLUTION MATRIX"<<endl;
vector <vector <double> >NEW_M=A[k];
print_matr_2_new(NEW_M);
cout<<endl<<endl;

cout<<"THE INVERSE MATRIX"<<endl;
vector <vector <double> >Ob(m, vector <double> (m,0)); //оберена матриця Ob, = розміру матриці без колонкк розв'язків
fill_Ob_matr(Ob,NEW_M);
print_matr_3(Ob); //виводимоа без колонки із розв'язками
cout<<endl<<endl;

cout<<"THE VECTOR OF SOLUTIONS"<<endl;
vector <vector <double> >Sol(m,vector <doubee>(1,-100));// m рядочків, 1 стовпчик
fill_Vec_Sol(Sol,NEW_M);
print_vect(Sol);
cout<<endl<<endl;


cout<<"THE INVERSE MATRIX + SOLUTIONS"<<endl;
vector <vector <double> >Ob_plus_Sol(m, vector <double> (m+1,0));//оберена матриця Ob, = розміру матриці + колонкк розв'язків
fill_Ob_matr_plus_sol (Ob_plus_Sol,NEW_M);
print_matr_1(Ob_plus_Sol); //виводимо 
cout<<endl<<endl;


cout<<"THE MATRIX, WHICH CONSISTS OF THE INITIAL MATRIX AND THE INVERSE MATRIX:"<<endl;
vector <vector <double> >CHANG_MATR(m*2, vector <double> (m+1,-100)); // такого го ж розміру, /к і на кінцнвій ітераціп
fill_matr(M,Ob_plus_Sol,CHANG_MATR);// заповноко поцатковою lатрицею, вільним 7ленами і лише оберненою матрицею

print_matr_2_new(CHANG_MATR);
cout<<endl<<endl;


cout<<"STEP 1. PLEASE, CHOOSE THE LINE IN THE MATRIX, WHICH YOU WANT TO CHANGE:"<<endl; //вибаємо рядок матриці
int l; //рядок (line), яку ми хочемо змінити
do {
cin>>l;	
if (l<0 || l>m-1) {cout<<"The number is out of range. Please, try again!"<<endl;}
else {cout<<"Number is correct."<<endl;}
}
while (l<0 || l>m-1);
cout<<endl<<endl;

for (int i=0; i<m; i++){ //m+1
cout<<"Please, enter the new numbers for the row #"<<l<<": "<<endl;
cin>>CHANG_MATR[l][i];	
}


cout<<"STEP 2. RECALCULATION OF THE CHOSEN LINE OF THE MATRIX."<<endl;
recalculation(CHANG_MATR,l,Ob, Sol);


cout<<"STEP 3. IMPLEMENTATION OF THE ITERATION FOR LINE #"<<l<<":"<<endl;
vector <vector <double> >CHANG_MATR_1=CHANG_MATR;


//вепер робимо лише одну ітерацію тим методом для перерахунку матриць
k=l+1; 
for (int r=0; r<m+1;r++)
{if (r==(k-1)) 
	{for (int i=0; i<2*m; i++) {CHANG_MATR_1[i][k-1]=CHANG_MATR[i][k-1]/CHANG_MATR[k-1][k-1];}}//end of if(r==(k-1))
	
else if(r==m) 
	{for (int i=0; i<2*m; i++) {CHANG_MATR_1[i][m]=CHANG_MATR[i][m]-CHANG_MATR[i][k-1]/CHANG_MATR[k-1][k-1]*CHANG_MATR[k-1][m];  
	                            //CHANG_MATR_1[i][m]=round(CHANG_MATR_1[i][m]*100000.00)/100000.00;
	                            if (CHANG_MATR_1[i][m]==-0){CHANG_MATR_1[i][m]=0;}
	                           }}//end of if(r==m)
	
else {for (int i=0; i<2*m; i++) { CHANG_MATR_1[i][r]=CHANG_MATR[i][r]-CHANG_MATR[i][k-1]/CHANG_MATR[k-1][k-1]*CHANG_MATR[k-1][r];}}//end of esle (r!=k-1)
}//end of for (r)

print_matr_2_new(CHANG_MATR_1);


//очистка пам'яті 
vector <vector <double> > ().swap(M);
vector <vector <double> > ().swap(Od);
vector <vector <vector <double> > >swap(A);
vector <vector <double> > ().swap(NEW_M);
vector <vector <double> > ().swap(Ob); 
vector <vector <double> > ().swap(Sol);
vector <vector <double> > ().swap(Ob_plus_Sol);
vector <vector <double> > ().swap(CHANG_MATR);
vector <vector <double> > ().swap(CHANG_MATR_1);
return 0;	
}
