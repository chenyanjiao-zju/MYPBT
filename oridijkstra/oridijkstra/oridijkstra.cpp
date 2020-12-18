// oridijkstra.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
//#include <stream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#define MAX 4000 //4000
using namespace std;
//暂时设k1k2=1
float k1 = 0.001, k2 = 0.1;
int start = 1; //起点
int dest = 300; //终点
float pay = 323298313; //1233000
float dis[MAX][MAX];
int preNode[MAX][MAX];
int nodenum = MAX;
float e[MAX][MAX];
int vis[MAX];
//int dis[MAX];
int n = 3147; //n为节点最大编号数 不是节点个数 3147 !!!!!!!
float minfee = 90000000000000;
int u = 0;

int hopNum[MAX];
int path[MAX];
long balance[MAX][MAX];

bool check_cap(vector<int> path)
{
	int sumF = 0;
	vector<int>::iterator it = path.end();
	while ((it - 1) != path.begin())
	{
		//cout<<"*(it-2):"<<*(it-2)<<"*(it-1):"<<*(it-1)<<endl;
		sumF += e[*(it - 2)][*(it - 1)];
		if (balance[*(it - 2)][*(it - 1)]<pay + sumF)
		{
			return false;
		}
		it--;
	}
	return true;
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
void initial2(int s, int index, float dis[][MAX])
{
	hopNum[s] = 0;
	hopNum[start] = -1;
	for (int i = 0; i <= n; i++)
	{

		//if (e[s][i]!=-1) cout<<"e["<<s<<"]["<<i<<"]"<<e[s][i]<<endl;

		preNode[index][i] = -1;
		dis[index][i] = -1;
		hopNum[i] = 0;
		// if(i==6) cout<<"1.hop["<<s<<"]:"<<hopNum[s]<<endl;
		if (e[s][i]>0 && i != start&&i != s)
		{

			preNode[index][i] = s;
			hopNum[i] = hopNum[s] + 1;
			//if(index==43&&i==6) cout<<"hop6++!!!="<<hopNum[6]<<" 2.hop["<<s<<"]:"<<hopNum[s]<<endl;
			dis[index][i] = k1*e[s][i] + k2*hopNum[i];
			//cout<<"change dis["<<i<<"]"<<endl;
		}
		//if(i==6) cout<<"3.hop["<<s<<"]:"<<hopNum[s]<<endl;
		//cout<<"test1111:"<<dis[index][i]<<endl;
	}
	hopNum[start] = -1;
	hopNum[s] = 0;
	dis[index][s] = 0;

	//if(index==43) cout<<"dis[index][i]"<<dis[2439][6];
	//if(index==43) cout<<"preNode[index]["<<s<<"]:"<<preNode[index][s];
	for (int c = 0;c <= n;c++)
	{
		if (e[start][c] != -1 && e[start][c] != 0)
			vis[c] = 1;
		else
			vis[c] = 0;
		//cout<<"dis["<<c<<"]:"<<dis[index][c]<<endl;
	}
	vis[start] = 1;


}
void dijkstra(int index, int start, int dest, float dis[][MAX])
{
	//cout<<"-----index:"<<index<<"----start:"<<start<<"-----"<<endl;
	// cout<<"preNode[index][i]:"<<preNode[index][start]<<endl;
	float dis2;
	//cout<<"hopnum[1]:"<<hopNum[1]<<endl;

	for (int i = 0; i < n; i++)
	{
		/*
		minfee = dis[index][3]; u = 3;
		if(minfee == 0||minfee == 0)
		{minfee = dis[index][1]; u=1;}
		*/
		//minfee<1*k1 //minfee = 16777216000;
		//cout<<"--------"<<i<<"th---------"<<endl;

		for (int a = 0; a <= n; a++) //初始化minfee
			if (dis[index][a] != float(-1) && dis[index][a] != float(0) && vis[a] == 0)
			{
				minfee = dis[index][a];u = a;break;
			}

		for (int j = 0; j <= n; j++)
		{

			// cout<<j<<":"<<minfee<<" "<<dis[index][j]<<" "<<vis[j]<<endl;
			if (dis[index][j] != float(-1) && dis[index][j] != float(0) && vis[j] == 0 && dis[index][j] < minfee)
			{
				// cout<<" minfee:"<<minfee<<" dis[index][j]:"<<dis[index][j]<<endl;
				//cout<<"change"<<endl;

				minfee = dis[index][j];
				u = j;

			}
		}


		// if (index==43) cout<<"!!!!!! "<<u<<" in!!!!!"<<endl;
		// if(index==43) cout<<"dis[2439][6]"<<dis[2439][6]<<endl;
		// cout<<"get_f1(hopNum[u]):"<<get_f1(hopNum[u])<<endl;
		if (vis[u] == 0)
		{
			for (int v = 0; v <= n; v++)
			{
				// 对于每个u可达的v来说

				if (e[u][v] >0 && vis[v] == 0)
				{

					//cout<<"!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
					//cout<<u<<"可达"<<v<<endl;
					// dis2 = dis[index][u] + k1*(e[u][v])-k2*(get_f1(hopNum[u]))+k2*(get_f1(hopNum[u]+1));
					dis2 = dis[index][u] + k1*(e[u][v]) + k2*(hopNum[u] + 1);
					if (dis[index][v] > dis2 || dis[index][v] == -1)
					{
						hopNum[v] = hopNum[u] + 1; //跳数+1
												   /*
												   if (index==31&&(u==1675||u==2504))
												   cout<<"change v:"<<v<<"by u:"<<u<< " dis[u]:"<<dis[index][u]<<" e[u][v]:"<<e[u][v]<<" change dis of "<<v<<" from "<<dis[index][v]<<" to "<<dis2<<endl;
												   */
						dis[index][v] = dis2;

						preNode[index][v] = u;
						// if(index==43&&v==6) cout<<"hopnum of "<<v<<":"<<hopNum[v]<<endl;



					}
				}
			}
			vis[u] = 1;
		}


		if (u == dest) //如果目标节点已加入最短路径集合
		{
			//cout<<"arrive at "<<u<<" prenode:"<<endl;
			/*
			for(int h=1;h<n+1;h++)
			{
			//if(preNode[index][h]!=-1)
			cout<<h<<":"<<preNode[index][h]<<" ";
			}
			cout<<endl;
			*/
			/* if(index==43)
			{
			cout<<"dis[index][6]:"<<dis[index][6]<<endl;
			cout<<"hopnum[1]:"<<hopNum[1]<<endl;
			cout<<"hopnum[2439]:"<<hopNum[2439]<<endl;
			cout<<"hopnum[6]:"<<hopNum[6]<<endl;

			}*/
			return;
		}

	}
	/*
	if(start==16755)
	for(int m=0;m<n+1;m++)
	{
	//if(preNode[index][m]!=-1)
	cout<<m<<":"<<preNode[index][m]<<" ";
	}
	cout<<endl;

	*/
	if (vis[dest] != 1) //如果不能达到dest终点
	{
		//cout<<"cannot reach the destination"<<endl;
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
	ifstream in("/Users/ninga/Desktop/network/channelInfoLN.csv");
	///Users/ninga/Desktop/network/channelInfoLN.csv
	//if (in.fail())  { cout << "File not found" <<endl; return ; }
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
	initial(start);


	get_all_f2();

	/*
	for(int b = 1;b<=n;b++)
	for(int c=1;c<=n;c++)
	{


	cout<<b<<"->"<<c<<e[b][c]<<endl;



	}
	*/
	//cout<<"e[2439][6]:"<<e[2439][6]<<endl;
	int second_num = 0; //start之后的第二个节点  跟start邻接节点个数
						//cout<<e[2][4]<<" "<<e[4][6]<<endl;
	for (int i = 0; i <= n; i++)
	{

		if (e[start][i]>0)
		{
			second_num++;

			// vis[i]=1;
			//preNode[i] = start;
			//cout<<"vis[i]=1;"<<i<<endl;
			// hopNum[i] = 0;
		}

	}



	int index = 0;
	for (int i = 0; i < n + 1; i++)
	{


		if (e[start][i] != -1 && e[start][i] != 0)
		{

			initial2(i, index, dis);
			preNode[index][i] = start;
			//if(i==2439) cout<<"first preNode[index][i]:"<<preNode[index][i]<<endl;
			//cout<<"test"<<dis[index][1]<<endl;
			dijkstra(index, i, dest, dis);
			index++;
		}

	}
	//cout<<"--------------OVER----------------"<<endl;
	vector<int > path;
	vector<int> finalPath;
	int m;
	float short_dis;
	int short_path = -1;
	bool change = false;

	//cout<<"second_num:"<<second_num<<endl;
	for (int k = 0;k<second_num;k++) //为每个second节点设一个path
	{
		m = dest;
		//cout<<"~~~~~index:"<<k<<"~~~~~"<<endl;
		int exit = 0;
		while (m != start)
		{
			//!!!!!!!!!!!!!!!!!!!
			// cout<<"e["<<preNode[k][m]<<"]["<<m<<"]:"<<e[preNode[k][m]][m]<<endl;
			// cout<<"hopnum["<<m<<"]:"<<hopNum[m]<<endl;
			m = preNode[k][m];
			//cout<<m<<endl;

			if (m == -1) //如果这条path没能到达dest终点
			{
				// cout<<"the "<<k<<"th path of this round cannot reach the end"<<endl;
				exit = 1;
				break;
			}
			path.insert(path.begin(), m);

		}
		if (!exit)
		{
			if (check_cap(path))
			{
				//cout<<"found"<<endl;
				/*
				vector<int>::iterator it = path.begin();
				while(it!=path.end())
				{
				cout<<*it<<"-";
				it++;
				}
				cout<<dest<<endl;
				*/
				// cout<<"dis:"<<dis[k][dest]<<endl;
				//cout<<"fee:"<<dis[k][dest]*pay<<endl;

				if (!change)
				{
					short_dis = dis[k][dest];
					short_path = k;
					change = true;
				}
				else {
					if (dis[k][dest]< short_dis)
					{

						short_dis = dis[k][dest];
						short_path = k;
						finalPath = path;
					}
				}

			}
			else
			{
				//cout<<"the "<<k<<"th path of failed because the capacity is not enough"<<endl;
				//cout<<"capacity not enough"<<endl;
			}

		}
		//if(k==43) cout<<k<<":"<<dis[k][dest]<<endl;
		path.clear();


	}
	// cout<<"------finished---------"<<endl;
	if (short_path != -1)
	{
		cout << "fee:" << short_dis << endl;

	}
	vector<int>::iterator i = finalPath.begin();
	while (i != finalPath.end())
	{
		cout << *i << "-";
		i++;
	}
	cout << dest << endl;

	cout << "The run time is:" << (double)clock() / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	// cout<<balance[5][9]<<" "<<balance[4][9];
	//"/Users/ninga/Desktop/BLOCK CHAIN/LN/LN/re.csv"
	ofstream write;
	ifstream read;


	write.open("/Users/ninga/Desktop/BLOCK CHAIN/LN/LN/time1.csv", ios::app);                //用ios::app不会覆盖文件内容
	write << (double)clock() / CLOCKS_PER_SEC * 1000 << endl;
	write.close();
	read.close();
	ofstream write2;
	ifstream read2;
	// /Users/ninga/Desktop/network/10000nodes.csv

	write2.open("/Users/ninga/Desktop/BLOCK CHAIN/LN/LN/fee1.csv", ios::app);                //用ios::app不会覆盖文件内容
	write2 << short_dis << endl;
	write2.close();
	read2.close();

	return 0;



}
