#include<iostream>
#include<set>
#include<map>
#include<queue>
#include<stack>

using namespace std;

int main()
{
	set<int> st1 = { 5,4,3,2,1 };
	st1.insert(0);
	st1.insert(6);
	st1.insert(2);
	st1.insert(2);
	st1.erase(3);

	for (int i : st1)
	{
		cout << i << " ";
	}

	cout << endl;

	map<string, string> map1 = { pair<string, string>("apple", "mar") };
	map1.insert(pair<string, string>("car", "masina"));
	map1.insert(pair<string, string>("bus", "autobuz"));
	map1.erase("bus");

	map1["car"] = "Masina";
	map1["dog"] = "Caine";

	for (auto i : map1)
	{
		cout << i.first << " " << i.second << endl;
	}

	map<int, set<string>> grupe;
	set<string> grupa1 = { "Dan", "Andreea", "Silvia" };
	set<string> grupa2 = { "Laurentiu", "Denis", "Ana" };
	grupe.insert(pair<int, set<string>>(1060, grupa1));
	grupe.insert(pair<int, set<string>>(1059, grupa2));

	for (auto i : grupe)
	{
		cout << "Grupa " << i.first << ": ";
		for (auto j : i.second)
		{
			cout << j << " ";
		}

		cout << endl;
	}


	queue<int> q1; // First In First Out => FIFO
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.pop();

	while (!q1.empty())
	{
		cout << q1.front() << " ";

		q1.pop();
	}

	cout << endl;

	stack<int> stack1; // Last In First Out => LIFO
	stack1.push(1);
	stack1.push(2);
	stack1.push(3);
	stack1.push(4);
	stack1.pop();
	while (!stack1.empty())
	{
		cout << stack1.top() << " ";

		stack1.pop();
	}

	return 0;
}