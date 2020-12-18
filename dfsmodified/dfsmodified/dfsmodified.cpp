// dfsmodified.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <time.h>
#define MAX 2001
#define k1 0.1
#define k2 0.1
using namespace std;


// utility function for printing
// the found path in graph
void printpath(vector<int>& path)
{
	int size = path.size();
	for (int i = 0; i < size; i++)
		cout << path[i] << " ";
	cout << endl;
}

// utility function to check if current
// vertex is already present in path



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

long balance[MAX][MAX];
float e[MAX][MAX];
int pay = 250000000;
float fee;
int hop;
bool success;
bool check_cap(vector<int> path)
{
	float sumF = 0;
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
float get_fee(vector<int> path)
{
	float sumF = 0;
	vector<int>::iterator it = path.begin();
	if (path.empty() == true)
	{
		//cout << "empty" << endl;
		return -1;
	}
	else
	{
		it++;
		while ((it + 1) != path.end())
		{
			sumF += k1*e[*(it)][*(it + 1)];
			it++;
		}
		sumF += k2*(path.size() - 2)*(path.size() - 1) / 2;
		return sumF;
	}
}
void get_all_f2(vector<vector<int> > &g)
{

	vector<string> row;
	string line;
	//string filename;
	//float f2 = -1.0;
	int  peer1;
	int peer2;
	long balance1;
	long balance2;///Users/ninga/Desktop/BLOCK CHAIN/LN/LN/data.csv
	ifstream in("D:/APP/data/data-density/1000-1nodes.csv");
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
		g[peer1].push_back(peer2);
		g[peer2].push_back(peer1);

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

int unvisited(int x, vector<int>& path)
{
	int size = path.size();
	for (int i = 0; i < size; i++)
		if (path[i] == x)
			return 0;
	return 1;
}

// utility function for finding paths in graph
// from source to destination

void findpaths(vector<vector<int> >&g, int src,
	int dst, int v)
{

	int count = 0;
	float feetmp = 0;
	float feemin = 1000000;
	vector<int> pathmin;
	queue<vector<int> > q;
	vector<int> path;
	path.push_back(src);
	q.push(path);
	while (!q.empty()) {
		path = q.front();
		q.pop();
		int last = path[path.size() - 1];
		if (path.size() > 30)
		{

		}
		else
		{
			if (last == dst)
			{
				count++;

				if (check_cap(path))
				{
					success = true;
					feetmp = get_fee(path);
					if (feetmp<feemin) { feemin = feetmp; pathmin = path; }
				}

				if (count == 30) {//如果找到30条路径
					hop = pathmin.size() - 2;
					fee = get_fee(pathmin);
					cout << endl;printpath(pathmin);cout << "fee:" << get_fee(pathmin) << endl;return;
				}
			}
		}

		for (int i = 0; i < g[last].size(); i++) { //g 邻接表
			if (unvisited(g[last][i], path)) {//如果末尾节点的相邻节点不在path中
				vector<int> newpath(path);
				newpath.push_back(g[last][i]);
				q.push(newpath);
			}
		}
	}
}
int main()
{

	// number of vertices


	// construct a graph

	int src = 1, dst = 49;
	double starttime, endtime, timetotal;
	int not_found = -1;

	vector<string> row;
	string line;
	int startarray[500] = { 0 };int destarray[500] = { 0 };//用于保存文件中的start和dest
														   //------------------读目的节点
	ifstream startfile("D:/APP/data/start.csv");
	///Users/ninga/Desktop/network/channelInfoLN.csv
	if (startfile.fail()) { cout << "File not found" << endl; }
	// /Users/ninga/Desktop/network/channelInfoLN.csv
	int index = 0;

	while (getline(startfile, line) && startfile.good())
	{
		//if(index==0) continue;
		file_to_string(row, line, ',');  //把line里的单元格数字字符提取出来，“,”为单元格分隔符
		startarray[index] = stoi(row[0]);

		//cout<<stoi(row[0])<<endl;
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
		//if(index==0) continue;
		file_to_string(row, line, ',');  //把line里的单元格数字字符提取出来，“,”为单元格分隔符
		destarray[index] = stoi(row[0]);
		//cout<<stoi(row[0])<<endl;
		index++;
	}
	row.clear();
	destfile.close();

	for (int turn = 0;turn < 500;turn++)
	{
		starttime = clock();
		src = startarray[turn];
		dst = destarray[turn];

		fee = -1;hop = -1;success = false;
		vector<vector<int> > g;
		int v = MAX;
		g.resize(MAX);
		get_all_f2(g);
		// function for finding the paths
		findpaths(g, src, dst, v);
		if (!success) cout << "not found!" << endl;
		endtime = clock();

		cout << "time:" << (endtime - starttime) / CLOCKS_PER_SEC * 1000;

		ofstream write;
		ifstream read;
		write.open("D:/APP/data/time3.csv", ios::app);
		write << (endtime - starttime) / CLOCKS_PER_SEC * 1000 << endl;
		write.close();
		read.close();

		ofstream write2;
		ifstream read2;
		write2.open("D:/APP/data/hopnum3.csv", ios::app);
		write2 << hop << endl;
		write2.close();
		read2.close();

		ofstream write3;
		ifstream read3;
		write3.open("D:/APP/data/fee3.csv", ios::app);
		write3 << fee << endl;
		write3.close();
		read3.close();

		ofstream write4;
		ifstream read4;
		write4.open("D:/APP/data/success3.csv", ios::app);
		if (success)
			write4 << 1 << endl;
		else
			write4 << 0 << endl;
		write4.close();
		read4.close();



	}
	system("PAUSE");
	return 0;
}



