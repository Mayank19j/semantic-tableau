#include<iostream>
#include<vector>
#include<string>

using namespace std;

int path;
int loc_flag;
int open;
int skip_brack(string str,int i)
{
	if(str[i]!='(') return i;
	for(i++;(str[i]!='\0'&& str[i]!=')');i++)
	{
		if(str[i]=='(') i=skip_brack(str,i);
	}
	if(str[i]=='\0')
	{
		cerr<<"some error in input\nbrackets not balanced";
		cout<<endl;
		exit(1);
	}
	else return i;
}

int find_imply(string str)
{
	int i;
	for(i=0;(str[i]!='\0'&& str[i]!='>');i++)
	{
		if(str[i]=='(') i=skip_brack(str,i);
	}
	if(str[i]=='\0') return -1;
	else return i;
}

int find_or(string str)
{
	int i;
	for(i=0;(str[i]!='\0'&& str[i]!='+');i++)
	{
		if(str[i]=='(') i=skip_brack(str,i);
	}
	if(str[i]=='\0') return -1;
	else return i;
}

int find_and(string str)
{
	int i;
	for(i=0;(str[i]!='\0'&& str[i]!='.');i++)
	{
		if(str[i]=='(') i=skip_brack(str,i);
	}
	if(str[i]=='\0') return -1;
	else return i;
}

int main_op(string str)
{
	int i;
	i=find_imply(str);
	if (i!=-1) return i;
	i=find_or(str);
	if (i!=-1) return i;
	i=find_and(str);
	if (i!=-1) return i;
	return 0;
}

void partition(string str,vector<string> list,vector<string> rem_list)
{
	int i,len;
	cout<<'\t'<<str<<endl;
	string temp;
	len=str.length();
	if(len ==1) 		//negeted ones will not be here
	{
		int flag=0;
		temp='-'+str;
		//tree *p=current;
		for(auto j=(list.begin());j!=(list.end());j++)
		{
			if((*j).compare(temp)==0)
			{
				flag=1;
				break;
			}
		}
		list.push_back(str);
		if(flag==1)
		{
			
			cout<<"this path is closed ";
			for(auto j=(list.begin());j!=(list.end());j++)
			{
				cout<<*j<<";";
			}
			cout<<"\nboth "<<str<<" and "<<temp<<" are present"<<endl;
			return;
		}
		//else check rem_list;

		if(rem_list.size()!=0)
		{
			string temp_str=*(rem_list.rbegin());
			rem_list.pop_back();
			partition(temp_str,list,rem_list);
			return;
		}
		cout<<"this path is open ";
		open=1;
		for(auto j=(list.begin());j!=(list.end());j++)
		{
			cout<<*j<<";";
		}
		cout<<endl;
		if(loc_flag==1)
		{
			cout<<endl<<"since this path is open it is consistent\n";
			exit(0);
		}
		if(loc_flag==2)
		{
			cout<<endl<<"since this path is open it is not valid\n";
			exit(0);
		}
		return;
	}
	i=find_imply(str);
	if (i!=-1)
	{
		cout<<endl<<"using rule alpha -> beta on "<<str<<" split into two paths \n-"<<str.substr(0,i)<<"  .."<<path+1;
		cout<<"\n"<<str.substr(i+1,len-i-1)<<"  .."<<path+2<<endl<<endl;
		if(i==1)
		{	temp='-'+str.substr(0,1);
		}
		else
		{	temp="-(";
			temp+=str.substr(0,i)+')';
		}
		cout<<"path "<<path+1<<':'<<endl;
		int loc_path=path+2;
		path+=2;
		partition(temp,list,rem_list);
		cout<<"path "<<loc_path<<':'<<endl;
		partition(str.substr(i+1,len-i-1),list,rem_list);
		return;
	}
	i=find_or(str);
	if (i!=-1)
	{
		cout<<endl<<"using rule alpha + beta on "<<str<<" will split into two paths\n"<<str.substr(0,i)<<"  .."<<path+1;
		cout<<"\n"<<str.substr(i+1,len-i-1)<<"  .."<<path+2<<endl<<endl;
		cout<<"path "<<path+1<<':'<<endl;
		int loc_path=path+2;
		path+=2;
		partition(str.substr(0,i),list,rem_list);
		cout<<"path "<<loc_path<<':'<<endl;
		partition(str.substr(i+1,len-i-1),list,rem_list);
		return;
	}
	i=find_and(str);
	if (i!=-1)
	{
		cout<<endl<<"using rule alpha (.) beta on "<<str<<endl<<str.substr(0,i)<<endl<<str.substr(i+1,len-i-1)<<" comes on the branch"<<endl;
		rem_list.push_back(str.substr(i+1,len-i-1));
		partition(str.substr(0,i),list,rem_list);
		return;
	}
	if(str[0]=='-')
	{
		if((str[1]=='(')&&(str[len-1]==')'))
		{
			int j=main_op(str.substr(2,len-3));
			if(j==0)
			{
				if (str[2]=='-')
				{
					cout<<"using--alpha rule on "<<str<<" results in"<<str.substr(3,len-4)<<endl;
					partition(str.substr(3,len-4),list,rem_list);
				}
				else if(str[2]=='(')
				{
					temp='-'+str.substr(2,len-3);
					partition(temp,list,rem_list);
				}
				else
				{
					temp=str.substr(2,len-3);
					int flag=0;
					for(auto j=(list.begin());j!=(list.end());j++)
					{
						if((*j).compare(temp)==0)
						{
							flag=1;
							break;
						}
					}
					string temp2 = temp;
					temp='-';
					temp+=str[2];
					list.push_back(temp);
					if(flag==1)
					{
						cout<<"this path is closed ";
						for(auto j=(list.begin());j!=(list.end());j++)
						{
							cout<<*j<<";";
						}
						cout<<"\nboth "<<str<<" and "<<temp2<<" are present"<<endl;
						return;
					}
					
					if(rem_list.size()!=0)
					{
						string temp_str=*(rem_list.rbegin());
						rem_list.pop_back();
						partition(temp_str,list,rem_list);
						return;
					}
					cout<<"this path is open ";
					open=1;
					for(auto j=(list.begin());j!=(list.end());j++)
					{
						cout<<*j<<";";
					}
					cout<<endl;
					if(loc_flag==1)
					{
						cout<<endl<<"since this path is open it is consistent\n";
						exit(0);
					}
					if(loc_flag==2)
					{
						cout<<endl<<"since this path is open it is not valid\n";
						exit(0);
					}
					return;	
				}
			}
			else if(str[2+j]=='>')
			{
				cout<<"using rule -(alpha>beta) on "<<str<<endl<<str.substr(2,j)<<endl<<"-("+str.substr(3+j,len-j-4)+')'<<" comes on the branch"<<endl;
				temp="-("+str.substr(3+j,len-j-4)+')';
				rem_list.push_back(temp);
				partition(str.substr(2,j),list,rem_list);
				return;
			}
			else if(str[2+j]=='+')
			{
				cout<<"using rule -(alpha+beta) on "<<str<<endl<<"-("+str.substr(2,j)+')'<<endl<<"-("+str.substr(3+j,len-j-4)+')'<<" comes on the branch"<<endl;
				temp="-("+str.substr(3+j,len-j-4)+')';
				rem_list.push_back(temp);
				temp="-("+str.substr(2,j)+')';
				partition(temp,list,rem_list);
				return;
			}
			else
			{
				cout<<endl<<"using rule -(alpha . beta) \n"<<str<<" will split into two paths\n-("<<str.substr(2,j)<<")  .."<<path+1;
				cout<<"\n"<<"-("<<str.substr(3+j,len-j-4)<<")  .."<<path+2<<endl<<endl;
				temp="-("+str.substr(2,j)+')';
				cout<<"path "<<path+1<<':'<<endl;
				int loc_path=path+2;
				path+=2;
				partition(temp,list,rem_list);
				temp="-("+str.substr(3+j,len-j-4)+')';
				cout<<"path "<<loc_path+1<<':'<<endl;
				partition(temp,list,rem_list);
				return;
			}
			return;
		}
		else if((str[1]!='(')&&(str[len-1]!=')'))
		{
			temp=str[1];
			int flag=0;
			for(auto j=(list.begin());j!=(list.end());j++)
			{
				if((*j).compare(temp)==0)
				{
					flag=1;
					break;
				}
			}
			list.push_back(str);
			if(flag==1)
			{
				cout<<"this path is closed ";
				for(auto j=(list.begin());j!=(list.end());j++)
				{
					cout<<*j<<";";
				}
				cout<<"\nboth "<<str<<" and "<<temp<<" are present"<<endl;
				return;
			}

			if(rem_list.size()!=0)
			{
				string temp_str=*(rem_list.rbegin());
				rem_list.pop_back();
				partition(temp_str,list,rem_list);
				return;
			}
			cout<<"this path is open ";
			open=1;
			for(auto j=(list.begin());j!=(list.end());j++)
			{
				cout<<*j<<";";
			}
			cout<<endl;
			if(loc_flag==1)
			{
				cout<<endl<<"since this path is open it is consistent\n";
				exit(0);
			}
			if(loc_flag==2)
			{
				cout<<endl<<"since this path is open it is not valid\n";
				exit(0);
			}
			return;
		}
		else
		{
			cerr<<"some error in given input";
			cout<<endl;
			exit(1);
		}
	}
	if((str[0]=='(')&&(str[len-1]==')'))
	{
		partition(str.substr(1,len-2),list,rem_list);
		return;
	}
	cerr<<"some error in input";
	cout<<endl;
	exit(1);
}

int main()
{
	path=0;
	open=0;
	string input;
	int i,j;
	vector<string> list;
	vector<string> rem_list;
	cout<<"Enter a propositional logic using\n> implies\n+ or\n. and\n- not\n() brackets\nand single letter literals\n";
inp:	getline(cin,input);
	for(i=0,j=0;input[i]!='\0';i++,j++)
	{
		if(input[i]==' ')
		{
			j--;
			continue;
		}
		input[j]=input[i];
	}
	if (j==0)
	{
		cerr<<"enter some input";
		cout<<endl;
		goto inp;
	}
	input.resize(j);
	cout<<endl<<"Enter your choice\n1.consistency\n2.validity\n3.check all paths\n";
	cin>>loc_flag;
	switch(loc_flag)
	{
		case 1:
			partition(input,list,rem_list);
			cout<<endl<<"It is inconsistent since all path are closed"<<endl;
			break;
		case 2:
			input="-("+input+')';
			cout<<"passing "<<input<<" for checking validity"<<endl;
			partition(input,list,rem_list);
			cout<<endl<<"It is valid by contradiction since all path are closed"<<endl;
			break;
		default :
			partition(input,list,rem_list);
			if(open==1)
			{
				cout<<input<<" is consistent"<<endl;
			}
			else
			{
				cout<<input<<" is inconsistent"<<endl;
			}
	}
}
