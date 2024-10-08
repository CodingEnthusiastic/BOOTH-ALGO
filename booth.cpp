#include<iostream>
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
void subtract(string multiplicant,string &multiplier,char &qn_1,string &a)
{
    multiplicant=complement(multiplicant);
    int i;
    for(i=multiplicant.size()-1;i>=0;i--)
    {
        if(multiplicant[i]=='0')
        {
            multiplicant[i]='1';
            break;
        }
        
    }
    add(multiplicant,multiplier,qn_1,a);
};

int main()
{
    string multiplicant="";
    cout<<"Enter the multiplicant in binary format : ";
    cin>>multiplicant;
    multiplicant='0'+multiplicant;
    string com_multipli=complement(multiplicant);
    cout<<"Complement : "<<com_multipli<<endl;
    string com_multiplicant=add_one(com_multipli);
    cout<<"2's Complement of Multiplicant : "<<com_multiplicant<<endl;
    string multiplier="";
    cout<<"Enter the multiplier in binary format : ";
    cin>>multiplier;
    multiplier='0'+multiplier;
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
    cout<<"\n\nAnswer :- "<<a<<multiplier<<endl;
}