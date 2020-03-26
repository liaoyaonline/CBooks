#include <iostream>
using namespace std;
void Tree_Node::generate_ChildNode();
int main()
{
    return 0;
}
void Tree_Node::generate_ChildNode()
{
	//样本个数
	int N = (int)MyDateTable[data_Attribute[0]].size();
	
	//将数据集中类别种类和数量放入map里面，只需判断最后一列即可
	map<string,int> category;
	for (int i = 0; i < N; i++)
	{	
		vector<string> temp_Class;
		temp_Class = MyDateTable[data_Attribute[attribute_Num]];
		category[temp_Class[i]]++;
	}

	//第一种情况
	//只有一个类别，标记为叶节点
	if (1 == category.size())
	{
		map<string, int>::iterator it = category.begin();
		node_Attribute = it->first;
		return;
	}
	//第二种情况
	//先判断所有属性是否取相同值
	bool isAllSame = false;
	for (int i = 0; i < remain_Attributes.size(); i++)
	{
		isAllSame = true;
		vector<string> temp;
		temp = MyDateTable[remain_Attributes[i]];
		for (int j = 1; j < temp.size(); j++)
		{
			//只要有一个不同，即可退出
			if (temp[0] != temp[j])
			{
				isAllSame = false;
				break;
			}
		}
		if (isAllSame == false)
		{
			break;
		}
	}
	//若属性集为空或者样本中的全部属性取值相同
	if (remain_Attributes.empty()||isAllSame)
	{
		//找出数量最多的类别及其出现的个数，并将该节点标记为该类
		map<string, int>::iterator it = category.begin();
		node_Attribute = it->first;
		int max = it->second;
		it++;
		for (; it != category.end(); it++)
		{
			int num = it->second;
			if (num > max)
			{
				node_Attribute = it->first;
				max = num;
			}
		}
		return;
	}
	//第三种情况
	//从remian_attributes中划分最优属性
	string best_Attribute = findBestAttribute();
	//将本节点设置为最优属性
	node_Attribute = best_Attribute;
	//对最优属性的每个属性值
	for (int i = 0; i < data_AttValues[best_Attribute].size(); i++)
	{
		string best_AttValues = data_AttValues[best_Attribute][i];
		//计算属性对应的数据集D
		//定义map用来存放该属性值下的数据子集
		map<string, vector<string>> sub_DataTable;
		for (int j = 0; j < MyDateTable[best_Attribute].size(); j++)
		{
			//寻找最优属性在数据集中属性值相同的数据样本
			if (best_AttValues == MyDateTable[best_Attribute][j])
			{
				//找到对应的数据集，存入子集中sub_DataTable（该样本的全部属性都要存入）
				for (int k = 0; k < data_Attribute.size(); k++)
				{
					sub_DataTable[data_Attribute[k]].push_back(MyDateTable[data_Attribute[k]][j]);
				}
			}
		}
		//若子集为空，将分支节点（子节点）标记为叶节点，类别为MyDateTable样本最多的类
		if (sub_DataTable.empty())
		{
			//生成子节点
			Tree_Node * p = new Tree_Node(sub_DataTable, data_Attribute, data_AttValues, remain_Attributes);
			//找出样本最多的类，作为子节点的属性
			map<string, int>::iterator it = category.begin();
			string childNode_Attribute = it->first;
			int max_Num = it->second;
			it++;
			for (; it != category.end(); it++)
			{
				if (it->second > max_Num)
				{
					max_Num = it->second;
					childNode_Attribute = it->first;
				}
			}
			//设置子叶节点属性
			p->set_NodeAttribute(childNode_Attribute);
			//将子节点存入childNode，预测样本的时候会用到
			childNode[best_AttValues] = p;
		}
		else//若不为空，则从剩余属性值剔除该属性，调用generate_ChildNode继续往下细分
		{
			vector<string> child_RemainAtt;
			child_RemainAtt = remain_Attributes;
			//找出child_RemainAtt中的与该最佳属性相等的属性
			vector<string>::iterator it = child_RemainAtt.begin();
			for (; it != child_RemainAtt.end(); it++)
			{
				if (*it == best_Attribute)
				{
					break;
				}
			}
			//删除
			child_RemainAtt.erase(it);

			//生成子节点
			Tree_Node * pt = new Tree_Node(sub_DataTable, data_Attribute, data_AttValues, child_RemainAtt);
			//将子节点存入childNode
			childNode[best_AttValues] = pt;
			//子节点再调用generate_ChildNode函数
			pt->generate_ChildNode();
		}
	}

}

