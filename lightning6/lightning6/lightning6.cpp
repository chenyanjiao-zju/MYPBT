// lightning5.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <iostream>
//#include <stream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include<ctime>
#define MAX 50 //4000
#define INF 9999999999999//
using namespace std;
//暂时设k1k2=1
float k1 = 0.1, k2 = 0.1;
int start = 1; //起点
int dest = 8; //终点
float pay = 10; //1233000
float dis[MAX][MAX];
float dis1[MAX][MAX];
int preNode[MAX][MAX];
int nodenum = MAX;
float e[MAX][MAX];
int vis[MAX];

//int dis[MAX];
int n = 50; //n为节点最大编号数 不是节点个数 3147 !!!!!!!
float minfee = 90000000000000;

int u = 0;

int hopNum[MAX];
int path[MAX];
long balance[MAX][MAX];

bool check_cap(vector<int> path)
{
	int sumF = 0;
	vector<int>::iterator it = path.end();
	if (path.empty() == true)
	{
		//cout << "empty" << endl;
		return false;
	}
	else
	{
		while ((it - 1) != path.begin())
		{
			sumF += e[*(it - 2)][*(it - 1)];
			if (balance[*(it - 2)][*(it - 1)]<pay + sumF)
			{
				return false;
			}
			it--;
		}
		return true;
	}



}
int get_f1(int num)
{
	return num*(num + 1) / 2;
}
void initial(int start)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (i == j)
			{
				e[i][j] = 0;
			}
			else
			{
				e[i][j] = -1;
			}
		}
	}
}
void initial2(int s, int index, float dis[][MAX], float dis1[][MAX])
{
	hopNum[s] = 0;
	//hopNum[start] = -1;
	for (int i = 0; i <= n; i++)//初始化dis数组和hop数组
	{
		preNode[index][i] = -1;
		dis[index][i] = INF;
		dis1[index][i] = INF;
		hopNum[i] = 0;
		if (e[s][i]>0 && i != s)
		{
			preNode[index][i] = s;
			hopNum[i] = hopNum[s] + 1;
			//dis[index][i] = k1*e[s][i] + k2*hopNum[i];
			//dis[index][i] = k1*e[s][i] + k2*hopNum[i];
			//由于交换了起始节点和目的节点，所以需要改
			dis[index][i] = k1*e[i][s];
			dis1[index][i] = k1*e[i][s] + k2*hopNum[i];
		}
	}
	//hopNum[start] = -1;
	hopNum[s] = 0;
	dis[index][s] = 0;
	dis1[index][s] = 0;

	//初始化vis数组
	for (int c = 0;c <= n;c++)
	{
		vis[c] = 0;
	}
	vis[s] = 1;
}
void dijkstra(int index, int start, int dest, float dis[][MAX], float dis1[][MAX])
{
	float dis2;
	float dis3;
	for (int i = 0; i < n; i++)//迭代n次
	{

		minfee = 90000000000000;
		u = -1;
		//寻找距离最短节点
		for (int j = 0; j <= n; j++)
		{
			if (dis[index][j] != INF && dis[index][j] != float(0) && vis[j] == 0 && dis[index][j] < minfee)
			{
				minfee = dis[index][j];
				u = j;
			}
		}
		//对距离最短节点进行操作
		if (vis[u] == 0 && u != -1)
		{
			for (int v = 0; v <= n; v++)
			{
				// 对于每个u可达的v来说
				if (e[u][v] >0 && vis[v] == 0)
				{
					if (v == dest)
					{
						dis[index][v] = dis[index][u];//更新距离
						dis1[index][v] = dis1[index][u];
						hopNum[v] = hopNum[u] + 1; //跳数+1
						preNode[index][v] = u;
					}
					else
					{
						//dis2 = dis[index][u] + k1*(e[u][v]) + k2*(hopNum[u] + 1);
						dis2 = dis[index][u] + k1*(e[v][u]);
						dis3 = dis1[index][u] + k1*(e[v][u]) + k2*(hopNum[u] + 1);
						//判断 节点余额是否足够用来支付 
						if (balance[v][u] < dis3*pay)
						{
							continue;
						}
						if (dis[index][v] > dis2)
						{
							hopNum[v] = hopNum[u] + 1; //跳数+1										
							dis[index][v] = dis2;//更新距离
							dis1[index][v] = dis3;
							preNode[index][v] = u;
						}
					}

				}
			}
			vis[u] = 1;
		}

		if (u == dest) //如果目标节点已加入最短路径集合
		{
			cout << "reach the dest" << endl;
			return;
		}
	}
	if (vis[dest] != 1) //如果不能达到dest终点
	{
		cout << "cannot reach the destination" << endl;
		preNode[index][dest] = -1;
		return;
	}
}


inline void file_to_string(vector<string> &record, const string& line, char delimiter)
{
	int linepos = 0;
	char c;
	int linemax = line.length();
	string curstring;
	record.clear();
	while (linepos<linemax)
	{
		c = line[linepos];
		if (isdigit(c) || c == '.') {
			curstring += c;
		}
		else if (c == delimiter&&curstring.size()) {
			record.push_back(curstring);
			curstring = "";
		}
		++linepos;
	}
	if (curstring.size())
		record.push_back(curstring);
	return;
}

void get_all_f2()
{
	vector<string> row;
	string line;
	//string filename;
	//float f2 = -1.0;
	int  peer1;
	int peer2;
	long balance1;
	long balance2;///Users/ninga/Desktop/BLOCK CHAIN/LN/LN/data.csv
	ifstream in("D:/APP/data/test2.csv");
	///Users/ninga/Desktop/network/channelInfoLN.csv
	if (in.fail()) { cout << "File not found" << endl; return; }
	int id = 0;
	// /Users/ninga/Desktop/network/channelInfoLN.csv
	while (getline(in, line) && in.good())
	{
		file_to_string(row, line, ',');  //把line里的单元格数字字符提取出来，“,”为单元格分隔符
										 /*
										 for(int i=0, leng=row.size(); i<leng; i++){
										 b.push_back(string_to_float(row[i]));
										 }
										 */
										 /*
										 if(row[3]==peer1&&row[4]==peer2)
										 {
										 f2 = row[6]/row[6]+row[7];
										 break;
										 }
										 */
										 //a.push_back(b);
										 //b.clear();
		peer1 = stoi(row[3]);
		peer2 = stoi(row[4]);
		// if(peer1>700||peer2>700) continue;
		// else{
		balance1 = stol(row[6]);
		balance2 = stol(row[7]);
		//if((peer1==2504&&peer2==1675)||(peer2==2504&&peer1==1675)) cout<<"2504:id"<<id<<endl;
		id++;
		//e[row[3]][row[4]] = row[6]/(row[6]+row[7]);
		balance[peer1][peer2] = balance1;
		balance[peer2][peer1] = balance2;
		//e[peer1][peer2] = float(balance2) / (float(balance1 + balance2));
		//e[peer2][peer1] = float(balance1) / (float(balance1 + balance2));
		e[peer1][peer2] = float(balance2) / (float(balance1 + balance2));
		e[peer2][peer1] = float(balance1) / (float(balance1 + balance2));
		// }
	}
	in.close();
	//cout<<"e[523][533]="<<e[523][533]<<endl;



}
int main()
{
	//cin >> n >> m;
	// 初始化邻接表
	//cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC*1000<< "ms" << endl;
	int starttime, endtime;
	vector<string> row;
	string line;
	int startarray[100] = { 0 };int destarray[100] = { 0 };//用于保存文件中的start和dest
														   //------------------读目的节点
	ifstream startfile("D:/APP/data/start.csv");
	///Users/ninga/Desktop/network/channelInfoLN.csv
	if (startfile.fail()) { cout << "File not found" << endl; }
	// /Users/ninga/Desktop/network/channelInfoLN.csv
	int index = 0;
	while (getline(startfile, line) && startfile.good())
	{
		file_to_string(row, line, ',');  //把line里的单元格数字字符提取出来，“,”为单元格分隔符
		startarray[index] = stoi(row[0]);
		index++;
	}
	row.clear();
	startfile.close();
	//------------------读目的节点
	ifstream destfile("D:/APP/data/dest.csv");
	///Users/ninga/Desktop/network/channelInfoLN.csv
	if (destfile.fail()) { cout << "File not found" << endl; }
	// /Users/ninga/Desktop/network/channelInfoLN.csv
	index = 0;
	while (getline(destfile, line) && destfile.good())
	{
		file_to_string(row, line, ',');  //把line里的单元格数字字符提取出来，“,”为单元格分隔符
		destarray[index] = stoi(row[0]);
		index++;
	}
	row.clear();
	destfile.close();

	//循环一百次 
	for (int turn = 0;turn < 1;turn++)
	{
		cout << "-------------------------" << endl;
		//随机生成起始节点和目的节点
		//srand(clock());
		//start = rand() % MAX;
		//dest = rand() % MAX;
		//交换起始节点和目的节点
		//start = destarray[turn];
		//dest = startarray[turn];
		start = 1;
		dest = 39;
		int temp = start;
		start = dest;
		dest = temp;
		//cout << "start" << start << endl;
		initial(start);
		get_all_f2();

		starttime = clock();//======================开始时间

		int index = 0;
		initial2(start, index, dis,dis1);

		dijkstra(index, start, dest, dis,dis1);
		vector<int > path;
		vector<int> finalPath;
		int m;
		float short_dis = 0;
		float short_dis1 = 0;

		int short_path = -1;
		bool change = false;

		//保存路径
		path.push_back(dest);
		m = dest;
		while (m != start)
		{
			m = preNode[0][m];
			if (m == -1) //如果这条path没能到达dest终点
			{
				cout << "the path cannot reach the end" << endl;
				path.clear();
				break;
			}
			//path.insert(path.begin(), m);
			path.push_back(m);
		}
		//计算fee 
		cout << "fee:" << dis1[0][dest] << endl;

		vector<int>::iterator i = path.begin();

		cout << "path:" << endl;
		while (i != path.end())
		{
			cout << *i << "-";
			i++;
		}
		endtime = clock();
		cout << "The run time is:" << endtime - starttime << "ms" << endl;
		ofstream write;
		ifstream read;


		write.open("D:/APP/data/time1.csv", ios::app);                //用ios::app不会覆盖文件内容
		write << endtime - starttime << endl;
		write.close();
		read.close();
		ofstream write2;
		ifstream read2;
		// /Users/ninga/Desktop/network/10000nodes.csv

		write2.open("D:/APP/data/fee1.csv", ios::app);                //用ios::app不会覆盖文件内容
		write2 << short_dis1 *pay << endl;
		write2.close();
		read2.close();

		//清空vector的内容
		path.clear();
		finalPath.clear();
	}
	system("PAUSE");
	return 0;
}





