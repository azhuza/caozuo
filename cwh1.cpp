//os_1new
#include<iostream>
#include<vector>
#include<algorithm>    //sort()
#include<iomanip>	   //setw()
using namespace std;

struct PCB
{
	char ID;
	int ComeTime;
	int FinishTime;
	int RunTime;
	int TurnoverTime; //周转时间
	double WeightTurnoverTime; //带权周转时间
};

vector<PCB>List; //总容器
vector<PCB>List1; //先到先服务
vector<PCB>List2; //
vector<PCB>List3; //高响应比
vector<PCB>recentList1; //
vector<PCB>finalList1; //
vector<PCB>recentList2; //
vector<PCB>finalList2; //

void FCFS(vector<PCB> &list);
void ShortFirst_HighFirst(vector<PCB> &list, vector<PCB> &list1, vector<PCB> &list2, int choice);//选1是短进程优先，选2是高响应比优先
void display(vector<PCB> &List);
bool cometimePaixu(const PCB &p1, const PCB &p2);
bool runtimePaixu(const PCB &p1, const PCB &p2);
bool xiangyingPaixu(const PCB &p1, const PCB &p2);
int main() {
//###########################保存进程信息###########################################
	PCB pcb;
	char id[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	int cometime[10] = { 0,2,5,7,12,15,4,6,8,10 };
	int runtime[10] = { 7,10,20,30,40,8,8,20,10,12 };
	for (int i = 0; i < 10;i++) {
		pcb.ID = id[i];
		pcb.ComeTime = cometime[i];
		pcb.RunTime = runtime[i];
		List.push_back(pcb);
	}
//###################将List赋值List1进行先来先服务##################################
	List1.assign(List.begin(), List.end());
	List2.assign(List.begin(), List.end());
	List3.assign(List.begin(), List.end());
	cout << "***************************************************************************" << endl;
	cout << "                            先到先服务算法                                 " << endl;
	FCFS(List1);
	cout << "***************************************************************************" << endl;
	cout << "                            短进程优先算法                                 " << endl;
	ShortFirst_HighFirst(List2,finalList1,recentList1,1);
	cout << "***************************************************************************" << endl;
	cout << "                            高响应比优先算法                               " << endl;
	ShortFirst_HighFirst(List3,finalList2,recentList2,2);
	cout << "***************************************************************************" << endl;
	system("pause");
}

bool cometimePaixu(const PCB &p1, const PCB &p2) {
	return p1.ComeTime < p2.ComeTime;
}
void display(vector<PCB> &List) {
	int totalTurnoverTime = 0;
	double totalWeightTime = 0;
	cout<<setw(10) << "进程名：";
	for (vector<PCB>::iterator i = List.begin(); i<List.end(); i++)
		cout << setw(6) << (*i).ID;
	cout << endl;

	cout << setw(11) << "到达时间：";
	for (vector<PCB>::iterator i = List.begin(); i<List.end(); i++)
		cout << setw(6) << (*i).ComeTime;
	cout << endl;

	cout << setw(11) << "运行时间：";
	for (vector<PCB>::iterator i = List.begin(); i<List.end(); i++)
		cout << setw(6) << (*i).RunTime;
	cout << endl;

	cout << setw(11) << "结束时间：";
	for (vector<PCB>::iterator i = List.begin(); i < List.end(); i++)
		cout << setw(6) << (*i).FinishTime;
	cout << endl;

	cout << setw(11) << "周转时间：";
	for (vector<PCB>::iterator i = List.begin(); i < List.end(); i++)
		{
			cout << setw(6) << (*i).TurnoverTime;
			totalTurnoverTime += (*i).TurnoverTime;
		}
	cout << endl;

	cout << setw(14) << "带权周转时间：";
	for (vector<PCB>::iterator i = List.begin(); i < List.end(); i++)
		{
			cout << setw(6) << fixed << setprecision(2) << (*i).WeightTurnoverTime;
			totalWeightTime += (*i).WeightTurnoverTime;
		}
	cout << endl;

	cout << "平均周转时间： " << fixed << setprecision(2) << ((double)totalTurnoverTime / List.size()) << endl;
	cout << "平均带权周转时间： " << fixed << setprecision(2) << ((double)totalWeightTime / List.size()) << endl;

}
void FCFS(vector<PCB> &list) {
	sort(list.begin(), list.end(), cometimePaixu);
	//display(list);
	int finishTimeMin, finishTimeMax;
	vector<PCB>::iterator i;
	i = list.begin();  //first
//###############完成第一个#########################################################
	(*i).FinishTime = (*i).ComeTime + (*i).RunTime;
	(*i).TurnoverTime = (*i).RunTime;
	(*i).WeightTurnoverTime = (double)(*i).TurnoverTime/(double)(*i).RunTime;
//###############完成第二个#########################################################
	i++;
	(*i).FinishTime = (*i).ComeTime + (*i).RunTime;
	(*i).TurnoverTime = (*i).RunTime;
	(*i).WeightTurnoverTime = (double)(*i).TurnoverTime / (double)(*i).RunTime;
//################存储两个结束时间##################################################
	finishTimeMin = min(list[0].FinishTime,list[1].FinishTime);
	finishTimeMax = max(list[0].FinishTime, list[1].FinishTime);
//###############从第三个开始#######################################################
	i++;
	while (i != list.end()) {
		if ((*i).ComeTime<=finishTimeMin) {//如果下一个进程比最小结束时间早
			(*i).FinishTime = (*i).RunTime + finishTimeMin;
			(*i).TurnoverTime = (*i).FinishTime-(*i).ComeTime;
			(*i).WeightTurnoverTime = (double)(*i).TurnoverTime / (double)(*i).RunTime;
			finishTimeMin = min(finishTimeMax, (*i).FinishTime);
			finishTimeMax = max(finishTimeMax, (*i).FinishTime);
			i++;
		}
		else {
			(*i).FinishTime = (*i).RunTime + (*i).ComeTime;
			(*i).TurnoverTime = (*i).FinishTime - (*i).ComeTime;
			(*i).WeightTurnoverTime = (double)(*i).TurnoverTime / (double)(*i).RunTime;
			finishTimeMin = min(finishTimeMax, (*i).FinishTime);
			finishTimeMax = max(finishTimeMax, (*i).FinishTime);
			i++;
		}
	}
	display(list);
}
bool runtimePaixu(const PCB &p1, const PCB &p2) {
	return p1.RunTime > p2.RunTime;
}
bool xiangyingPaixu(const PCB &p1, const PCB &p2)
{
	return p1.WeightTurnoverTime<p2.WeightTurnoverTime;
}
void ShortFirst_HighFirst(vector<PCB> &list, vector<PCB> &list1, vector<PCB> &list2, int choice) {
	int index = 0;	
	sort(list.begin(), list.end(), cometimePaixu);
	//	display(list);
	int finishTimeMin, finishTimeMax;
	vector<PCB>::iterator i;
	i = list.begin();  //first
//###############完成第一个#########################################################
	(*i).FinishTime = (*i).ComeTime + (*i).RunTime;
	(*i).TurnoverTime = (*i).RunTime;
	(*i).WeightTurnoverTime = (double)(*i).TurnoverTime / (double)(*i).RunTime;
//###############完成第二个#########################################################
	i++;
	(*i).FinishTime = (*i).ComeTime + (*i).RunTime;
	(*i).TurnoverTime = (*i).RunTime;
	(*i).WeightTurnoverTime = (double)(*i).TurnoverTime / (double)(*i).RunTime;
//################存储两个结束时间##################################################
	finishTimeMin = min(list[0].FinishTime, list[1].FinishTime);
	finishTimeMax = max(list[0].FinishTime, list[1].FinishTime);
//###############从第三个开始#######################################################
	list1.push_back(list[0]);
	list1.push_back(list[1]);
	i++;
	/*while (i != list.end()) {
		if ((*i).ComeTime <= finishTimeMin) {//如果下一个进程比最小结束时间早
			(*i).FinishTime = (*i).RunTime + finishTimeMin;
			(*i).TurnoverTime = (*i).FinishTime - (*i).ComeTime;
			(*i).WeightTurnoverTime = (double)(*i).TurnoverTime / (double)(*i).RunTime;
			finishTimeMin = min(finishTimeMax, (*i).FinishTime);
			finishTimeMax = max(finishTimeMax, (*i).FinishTime);
			i++;
		}
		else {
			(*i).FinishTime = (*i).RunTime + (*i).ComeTime;
			(*i).TurnoverTime = (*i).FinishTime - (*i).ComeTime;
			(*i).WeightTurnoverTime = (double)(*i).TurnoverTime / (double)(*i).RunTime;
			finishTimeMin = min(finishTimeMax, (*i).FinishTime);
			finishTimeMax = max(finishTimeMax, (*i).FinishTime);
			i++;
		}
	}*/
	for (; i < list.end();) //从第三个开始
	{
		if ((*i).RunTime == 0)break;

		if ((*i).ComeTime <= finishTimeMin)
		{
			if ((*i).RunTime == 0)break;
			while ((*i).ComeTime <= finishTimeMin)
			{
				if ((*i).RunTime == 0)break;

				list2.push_back(*i); //只要第一个结束了，在此之前到了的都可以插进去
				index++;
				i++;

				if (i == list.end()) break;
			}
		}
		else if (!list2.empty())
		{

		}
		else if ((*i).ComeTime <= finishTimeMax) {
			list2.push_back(*i);
			index++;
			i++;

			list2[index - 1].FinishTime = list2[index - 1].ComeTime + list2[index - 1].RunTime;
			list2[index - 1].TurnoverTime = list2[index - 1].FinishTime - list2[index - 1].ComeTime;
			list2[index - 1].WeightTurnoverTime = (double)list2[index - 1].TurnoverTime / (double)list2[index - 1].RunTime;

			finishTimeMin = min(finishTimeMax, list2[0].FinishTime);
			finishTimeMax = max(finishTimeMax, list2[0].FinishTime);

			list1.push_back(*(list2.end() - 1));
			list2.pop_back();
			index--;
			break;
		}
		else {
			list2.push_back(*i);
			index++;
			i++;
			list2.push_back(*i);
			index++;
			i++;

			for (int i = 0; i < index; i++)
			{
				list2[i].FinishTime = list2[i].ComeTime + list2[i].RunTime;
				list2[i].TurnoverTime = list2[i].FinishTime - list2[i].ComeTime;
				list2[i].WeightTurnoverTime = (double)list2[i].TurnoverTime / (double)list2[i].RunTime;
			}
			finishTimeMin = min(list2[0].FinishTime, list2[1].FinishTime);
			finishTimeMax = max(list2[0].FinishTime, list2[1].FinishTime);

			list1.push_back(*(list2.end() - 1));
			list2.pop_back();
			index--;
			list1.push_back(*(list2.end() - 1));
			list2.pop_back();
			index--;
			break;
		}

		for (int i = 0; i < index; i++)
		{
			list2[i].FinishTime = finishTimeMin + list2[i].RunTime;
			list2[i].TurnoverTime = list2[i].FinishTime - list2[i].ComeTime;
			list2[i].WeightTurnoverTime = (double)list2[i].TurnoverTime / (double)list2[i].RunTime;

		}
		if(choice==1)sort(list2.begin(), list2.end(), runtimePaixu);
		if(choice==2)sort(list2.begin(), list2.end(), xiangyingPaixu);

		finishTimeMin = min(finishTimeMax, list2[index - 1].FinishTime);
		finishTimeMax = max(finishTimeMax, list2[index - 1].FinishTime);

		list1.push_back(*(list2.end() - 1));
		list2.pop_back();
		index--;

	}

	while (!list2.empty())
	{
		for (int i = 0; i < index; i++)
		{
			list2[i].FinishTime = finishTimeMin + list2[i].RunTime;
			list2[i].TurnoverTime = list2[i].FinishTime - list2[i].ComeTime;
			list2[i].WeightTurnoverTime = (double)list2[i].TurnoverTime / (double)list2[i].RunTime;
		}
		if (choice == 1)sort(list2.begin(), list2.end(), runtimePaixu);
		if (choice == 2)sort(list2.begin(), list2.end(), xiangyingPaixu);
		finishTimeMin = min(finishTimeMax, list2[index - 1].FinishTime);
		finishTimeMax = max(finishTimeMax, list2[index - 1].FinishTime);

		list1.push_back(*(list2.end() - 1));
		list2.pop_back();
		index--;
	}
	display(list1);
}
