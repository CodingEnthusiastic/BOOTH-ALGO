#include<iostream>
#include <string>
#include<vector>
#include<cmath>
using namespace std;  
void result(string a,string multiplier)
{
    cout<<"\nResult is : ";
    for(int i=0;i<a.size();i++)
    {
        cout<<a[i]<<' ';
    };
    for(int j=0;j<multiplier.size();j++)
    {
        cout<<multiplier[j]<<' ';
    }
    cout<<endl;
}
void asr(string multiplicant,string &multiplier,char &qn_1,string &a,char carry)
{
    qn_1=multiplier[multiplier.size()-1];
    for(int i=multiplier.size()-1;i>0;i--)
    {
        multiplier[i]=multiplier[i-1];
    };
    multiplier[0]=a[a.size()-1];
    for(int i=a.size()-1;i>0;i--)
    {
        a[i]=a[i-1];
    };
    cout<<"ASR result"<<endl;
    result(a,multiplier);
}
string to_binary(int num)
{
    if(num==0)
    {
        return "0";
    }
    string ans1="";
    num=abs(num);
    while(num!=0)
    {
        char c=((num % 2) + '0');
        ans1 = c + ans1;
        num=num/2;
    };
    return ans1;
}
string complement(string a)
{
    for(int i=0;i<a.size();i++)
    {
        if(a[i]=='0')
        {
            a[i]='1';
        }
        else
        {
            a[i]='0';
        }
    };
    return a;
}  
void add(string multiplicant,string &multiplier,char &qn_1,string &a)
{
    char carry = '0';
    for(int i=multiplicant.size()-1;i>=0;i--)
    {
        int sum=(multiplicant[i]-'0')+(a[i]-'0')+(carry-'0');
        a[i]=(sum%2)+'0';
        carry=(sum/2)+'0';
    };
    cout<<"Addition/Substraction results : \n";
    result(a,multiplier);
    asr(multiplicant,multiplier,qn_1,a,carry);
}
string add_one(string &a)
{
    int carry=1;
    for(int i=a.size()-1;i>=0;i--)
    {
        int sum=(a[i]-'0') + carry;
        carry=sum / 2;
        sum=sum % 2;
        a[i]=sum + '0';
        if(carry==0)
        {
            break;
        }
    };
    return a;
}
int main()
{
    int num1;
    cout<<"Enter the multiplicant : ";
    cin>>num1;
    int num2;
    cout<<"\nEnter the multiplier : ";
    cin>>num2;
    string multiplicant="";
    multiplicant=to_binary(num1);
    if(num1>=0)
        multiplicant='0'+multiplicant;
    else
        multiplicant='1'+multiplicant;
    string com_multipli=complement(multiplicant);
    cout<<"1's Complement of multiplicant : "<<com_multipli<<endl;
    string com_multiplicant=add_one(com_multipli);
    cout<<"2's Complement of Multiplicant : "<<com_multiplicant<<endl;
    string multiplier="";
    multiplier=to_binary(num2);
    if(num2>=0)
        multiplier='0'+multiplier;
    else
        multiplier='1'+multiplier;
    for(int i=multiplier.size();i<multiplicant.size();i++)
    {
        multiplier='0'+multiplier;
    }
    cout<<"Multiplier : "<<multiplier<<endl;
    string a;
    a="";
    for(int i=0;i<multiplicant.size();i++)
    {
        a = a + '0';
    }
    cout<<"Accumulator : "<<a<<endl;
    int count=multiplicant.size();
    char qn_1='0';
    int m=count;
    while(m--)
    {

        if(multiplier[multiplier.size()-1]=='0' && qn_1=='1')
        {
            cout<<"\nQ0 = 0 Q-1 = 1 Perform A=A+M ";
            add(multiplicant,multiplier,qn_1,a);
        }
        else if(multiplier[multiplier.size()-1]=='1' && qn_1=='0')
        {
            cout<<"\nQ0 = 1 Q-1 = 0 Perform A=A-M ";
            add(com_multiplicant,multiplier,qn_1,a);
        }
        else if(multiplier[multiplier.size()-1]=='0' && qn_1=='0')
        {
            cout<<"\nQ0 = 0 Q-1 = 0  ";
            asr(multiplicant,multiplier,qn_1,a,'0');
        }
        else
        {
            cout<<"\nQ0 = 1 Q-1 = 1  ";
            asr(multiplicant,multiplier,qn_1,a,'0');
        }
        cout<<"\n\n";
    };
    string finalans=a+multiplier;
    if(finalans[0]=='0')
        cout<<"\n\nAnswer :- "<<finalans<<endl;
    else{
        string f=complement(finalans);
        string f_one=add_one(f);
        cout<<"\n\nAnswer is negative with magnitude  :- "<<f_one<<endl;
    }
}