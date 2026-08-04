#include<iostream>
using namespace std;
int main()
{ 
    int n;
    cout<<"Enter frame lenth:";
    cin >>n;
    int a[100],b[200];
    cout<<"Enter the frame bits(0and1):\n";
for (int i=0;i<n;i++)
{ 
    cin>>a[i];
}
int i=0,j=0,count=0;
while(i<n)
{
    b[j]=a[i];
    if(a[i]==1)
    count++;
else
count=0;
if(count==5)
{
    j++;
    b[j]=0; //stuff a 0 after five consecutive 1's
    count=0;
}
i++;
j++;
}
cout<<"\nFrame after Bit Stuffimg:\n";
for (int k=0;k<j;k++)
{
    cout<< b[k]<<" ";

}
cout<<endl;
return 0;
}