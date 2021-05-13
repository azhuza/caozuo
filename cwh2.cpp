//os_2new
#include<iostream>
#include<vector>

#include<algorithm>
using namespace std;

struct PCB {
	char ID;
	int num; //磁道号
};

void FCFS(int start);
void Shortest(int start);
void Scan(int start,char direction);
bool shortFirst(const PCB&p1,const PCB&p2);
int startNum;
int sumDistance;
double aveDistance;
char id[14] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N' };
int diskNum[14] = { 30,50,100,180,20,90,150,70,80,10,160,120,40,110 };
vector<PCB>list;

int main() {
	
	PCB pcb;
	for (int i = 0; i < 14; i++) {
		pcb.ID = id[i];
		pcb.num = diskNum[i];
		list.push_back(pcb);
	}
	int choice;
	char direction_;
	while (true) {
		cout << endl;
		cout << "************************************************************" << endl;
		cout << "请输入你要使用的磁盘调度算法序号" << endl;
		cout << "1、先来先服务（FCFS）\t2、最短寻道优先\t 3、电梯调度算法" << endl;
		cout << "Choice:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "输入起始的磁道号：";
			cin >> startNum;
			FCFS(startNum); break;
		case 2:
			cout << "输入起始的磁道号：";
			cin >> startNum;
			Shortest(startNum); break;
		case 3:
			cout << "输入起始的磁道号：";
			cin >> startNum;
			cout << "输入扫描方向(l/L)or(r/R):";
			cin >> direction_;
			Scan(startNum,direction_); break;
		default:
			cout << "输入有误！" << endl;
			break;
		}
	}
	system("pause");
	return 0;

}
bool shortFirst(const PCB&p1,const PCB&p2) {
	return p1.num < p2.num;
}
void FCFS(int start) {
	sumDistance = 0;
	aveDistance = 0;
	cout << "先来先服务算法结果如下：" << endl;
	vector<PCB>::iterator i;
	i = list.begin();
	cout << start << "(起始点)";
	for (;i<list.end();i++) {
		cout << "—>" << (*i).ID << "(" << (*i).num << ")";
		sumDistance += abs(start-(*i).num);
		start = (*i).num;
	}
	aveDistance = (double)sumDistance / 14;
	cout << "\n平均移动距离：" <<aveDistance<< endl;
}
void Shortest(int start) {
	sumDistance = 0;
	aveDistance = 0;
	sort(list.begin(), list.end(), shortFirst);
	cout << "最短寻道优先算法结果如下：" << endl;
	vector<PCB>::iterator i;
	i = list.begin();
	int point=0;//定位在起始点两边最近的点的位置
	while(i<list.end()){
		if ((*i).num <= start) {
			i++;
			point++;
		}
		else i++;
	}
	//i的值为小于等于起始点的个数
	int small=point-1;
	int large=point;
	int finish = 0; //记录已经写入点的个数
	cout << start << "(起始点)";
	while (finish < list.size()) {
		if (((large < list.size() && small >= 0) && (abs(start - list[small].num) <= abs(list[large].num - start)))||large>= list.size()) {
			//if (abs(start - list[small].num) <= abs(list[large].num - start)) {
			cout << "—>" << list[small].ID << "(" << list[small].num << ")";
			sumDistance += abs(start - list[small].num);
			finish++;
			start = list[small].num;
			small--;
		}
		else if (((large < list.size() && small >= 0) && (abs(start - list[small].num) > abs(list[large].num - start))) || small < 0) {
				cout << "—>" << list[large].ID << "(" << list[large].num << ")";
				sumDistance += abs(start - list[large].num);
				finish++;
				start = list[large].num;
				large++;
			}
		
	}
	aveDistance = (double)sumDistance / 14;
	cout << "\n平均移动距离：" << aveDistance << endl;

}
void Scan(int start, char direction) {
	sumDistance = 0;
	aveDistance = 0;
	sort(list.begin(), list.end(), shortFirst);
	cout << "电梯调度算法结果如下：" << endl;
	vector<PCB>::iterator i;
	i = list.begin();
	int point = 0;//定位在起始点两边最近的点的位置
	while (i < list.end()) {
		if ((*i).num <= start) {
			i++;
			point++;
		}
		else i++;
	}
	//i的值为小于等于起始点的个数
	int small = point - 1;
	int large = point;
	cout << start << "(起始点)";
	if (direction == 'r' || direction == 'R') {
		for (; large < list.size(); large++) {
			cout << "—>" << list[large].ID << "(" << list[large].num << ")";
			sumDistance += abs(start - list[large].num);
			start = list[large].num;
		}
		for (; small >= 0; small--) {
			cout << "—>" << list[small].ID << "(" << list[small].num << ")";
			sumDistance += abs(start - list[small].num);
			start = list[small].num;
		}
	}
	else {
		for (; small >= 0; small--) {
			cout << "—>" << list[small].ID << "(" << list[small].num << ")";
			sumDistance += abs(start - list[small].num);
			start = list[small].num;
		}
		for (; large < list.size(); large++) {
			cout << "—>" << list[large].ID << "(" << list[large].num << ")";
			sumDistance += abs(start - list[large].num);
			start = list[large].num;
		}
		
	}
	aveDistance = (double)sumDistance / 14;
	cout << "\n平均移动距离：" << aveDistance << endl;
}

