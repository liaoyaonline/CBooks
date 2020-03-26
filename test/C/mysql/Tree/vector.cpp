#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "Tree_Node.h"
using namespace std;


//定义属性数组，存放可能的属性，包括类别
vector<string> data_Attributes;
//定义各属性对应的属性值
map<string, vector<string>> data_AttValues;
//定义剩余属性，不包括类别
vector<string> remain_Attributes;
//定义数据表,属性-属性值（全部数据的属性值放在同一个数组）
map<string, vector<string>>data_Table;


//输入数据生成数据集
void data_Input()
{
	//输入属性（色泽 根蒂 敲声 纹理 脐部 触感 好瓜）
	string input_Line,temp_Attributes;
	cout << "请输入属性：" << endl;
	//获取一行数据，然后绑定到数据流istringstream
	getline(cin, input_Line);
	istringstream input_Attributes(input_Line);
	//将数据流内容（空格不输出）输入数据属性数组中
	while (input_Attributes >> temp_Attributes)
	{
		data_Attributes.push_back(temp_Attributes);
	}
	//剔除类别这个属性
	remain_Attributes = data_Attributes;
	remain_Attributes.pop_back();
	//定义样本数量
	int N = 0;
	cout << "请输入样本数量：" << endl;
	cin >> N;
	cin.ignore();//清空cin缓冲区中的留下的换行符
	//输入数据(属性值）
	cout << "请输入样本：" << endl;
	//一共N个训练样本
	for (int j = 0; j < N; j++)
	{
		string temp_AttValues;
		//获取一行属性值输入
		getline(cin, input_Line);
		istringstream input_AttValues(input_Line);
		//将各属性值输入到数据表data_table中
		for (int i = 0; i < data_Attributes.size(); i++)
		{
			input_AttValues >> temp_AttValues;
			data_Table[data_Attributes[i]].push_back(temp_AttValues);
		}
	}
    map<string,vector<string>>::reverse_iterator iter;
    for(iter = data_Table.rbegin();iter != data_Table.rend();iter++)
    {
        cout<< iter->first <<endl;
        for(auto it=(iter->second).begin();it != (iter->second).end();it++)
            cout<< *it<<" ";
    }
    for (int i = 0; i < data_Attributes.size(); i++)
	{
		set<string> attValues;
		for (int j = 0; j < N; j++)
		{
			string temp = data_Table[data_Attributes[i]][j];
			//若有重复属性值，set是不会插入的
			attValues.insert(temp);
		}
		for (set<string>::iterator it = attValues.begin(); it != attValues.end(); it++)
		{
			data_AttValues[data_Attributes[i]].push_back(*it);
		}

	}
    cout << "\n"<<endl;
    for(iter = data_AttValues.rbegin();iter != data_AttValues.rend();iter++)
    {
        cout<< iter->first <<endl;
        for(auto it=(iter->second).begin();it != (iter->second).end();it++)
            cout<< *it<<" ";
    }
}
int main()
{
    data_Input();
    return 0;
}

