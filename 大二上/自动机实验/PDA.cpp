#include <iostream>
#include<vector>
#include<string>
#include<stack>
#include <algorithm>
using namespace std;
class Old2NewRelation {

private:
	string oldState;//当前状态
	char trans;//读取的字符
	string newState;//新状态
	char top;//栈顶字符
	char putInStack;//要压入栈中的字符

public:
	string getOldState() {
		return oldState;
	}
	void setOldState(string oldState) {
		this->oldState = oldState;
	}
	char getTrans() {
		return trans;
	}
	void setTrans(char trans) {
		this->trans = trans;
	}
	string getNewState() {
		return newState;
	}
	void setNewState(string newState) {
		this->newState = newState;
	}
	Old2NewRelation(string oldState, char trans, string newState, char top, char putInStack) {
		this->oldState = oldState;
		this->trans = trans;
		this->newState = newState;
		this->top = top;
		this->putInStack = putInStack;
	}
	string toString() {
		return "state tranfer relation [nowstate：" + oldState + ",  recognition char：" + trans + ", newState：" + newState + ", the operation for stack is ：" + putInStack
			+ "replace the top of stack：" + top + "]";
	}
	char getPutInStack() {
		return putInStack;
	}
	void setPutInStack(char putInStack) {
		this->putInStack = putInStack;
	}
	char getTop() {
		return top;
	}
	void setTop(char top) {
		this->top = top;
	}
};


static vector<Old2NewRelation> initRelation() {
	//用‘#’表示空字符
	//分别表示 当前状态-识别字符-转移状态-栈顶元素-替换栈顶的元素
	vector<Old2NewRelation> list;
	list.push_back(Old2NewRelation("q1", '#', "q2", '#', '$'));
	list.push_back(Old2NewRelation("q2", 'a', "q4", '#', '#'));
	list.push_back(Old2NewRelation("q2", 'b', "q2", '#', 'b'));
	list.push_back(Old2NewRelation("q2", 'c', "q3", 'b', '#'));
	list.push_back(Old2NewRelation("q2", 'c', "q6", '#', 'c'));
	list.push_back(Old2NewRelation("q2", '#', "q7", '$', '#'));
	list.push_back(Old2NewRelation("q3", 'a', "q4", '#', '#'));
	list.push_back(Old2NewRelation("q3", 'b', "q2", '#', 'b'));
	list.push_back(Old2NewRelation("q3", 'c', "q3", 'b', '#'));
	list.push_back(Old2NewRelation("q3", 'c', "q6", '#', 'c'));
	list.push_back(Old2NewRelation("q3", '#', "q7", '$', '#'));
	list.push_back(Old2NewRelation("q4", 'a', "q4", '#', '#'));
	list.push_back(Old2NewRelation("q4", 'b', "q5", 'c', '#'));
	list.push_back(Old2NewRelation("q4", 'b', "q2", '#', 'b'));
	list.push_back(Old2NewRelation("q4", 'c', "q3", 'b', '#'));
	list.push_back(Old2NewRelation("q4", 'c', "q6", '#', 'c'));
	list.push_back(Old2NewRelation("q4", '#', "q7", '$', '#'));
	list.push_back(Old2NewRelation("q5", 'a', "q4", '#', '#'));
	list.push_back(Old2NewRelation("q5", 'b', "q5", 'c', '#'));
	list.push_back(Old2NewRelation("q5", 'b', "q2", '#', 'b'));
	list.push_back(Old2NewRelation("q5", 'c', "q6", '#', 'c'));
	list.push_back(Old2NewRelation("q5", '#', "q7", '$', '#'));
	list.push_back(Old2NewRelation("q6", 'a', "q4", '#', '#'));
	list.push_back(Old2NewRelation("q6", 'b', "q5", 'c', '#'));
	list.push_back(Old2NewRelation("q6", 'c', "q6", '#', 'c'));
	list.push_back(Old2NewRelation("q6", '#', "q7", '$', '#'));
	return list;
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	cout << "input string【only include 'abc'】,judging the number of b is same c，accetp if same，refuse if different" << endl;
	//将字符存入字符数组中
	string str;
	getline(cin, str);
	str.insert(0, "#");//特殊处理，用来使栈中刚开始识别输入串时栈中栈顶符号为$
	vector<Old2NewRelation> list = initRelation();
	stack<int> stack;
	string strState = "q1";
	string endState = "q7";
	cout << "The original state of PDA： " << strState << "The accept state is ：" << endState << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	bool isTrave = false;
	//开始处理逐个识别字符，bc中需要选择一个进行压栈，此处选择对b进行操作
	for (int i = 0; i < str.length(); i++) {
		char cNow = str[i];
		if (cNow != '#') {
			cout << "The " << i << "of char be recognized is" << cNow << endl;
		}
		else {
			cout << " making special mark$" << endl;
			cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		}
		isTrave = false;
		for (int k = 0; k < list.size(); k++) {
			if (isTrave) {//状态发生转移之后，就不再遍历，而是对下一个字符重新开始判断
				break;
			}
			if (strState == list[k].getOldState() && (cNow == list[k].getTrans())) {
				//如果栈空或栈顶字符和当前识别的字符一致(stack.empty()栈的特殊处理也归到这一逻辑中)
				if (stack.empty() || ((char)stack.top()) == '$' || ((char)stack.top()) == cNow) {
					if (list[k].getTop() == '#') {
						strState = list[k].getNewState();//状态转移到新状态
						cout << list[k].toString() << endl;
						isTrave = true;
						if (list[k].getPutInStack() != '#') {//不管栈是否为空，只要是非空替换空，就入栈
							//非空替换空的状态，也就是要压入栈中一个字符								
							cout << "push into stack" << list[k].getPutInStack() << endl;
							cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
							stack.push(list[k].getPutInStack());
						}
						else {
							cout << "Replace empty space with empty space and do not operate on the stack" << endl;
							cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
						}
					}
				}
				else {//栈中有元素，且和输入字符不同
					strState = list[k].getNewState();//状态转移到新状态
					cout << list[k].toString();
					isTrave = true;
					if (list[k].getTop() != '#') {
						cout << "The out stack element is：" << stack.top() << endl;
						cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
						stack.pop();
					}
					else {
						cout << "Replace empty space with empty space and do not operate on the stack" << endl;
						cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
					}

				}
			}
		}
	}
	isTrave = false;
	if (!stack.empty() && ((char)stack.top()) == '$') {
		//根据状态转移函数得到最终处理的状态
		for (int k = 0; k < list.size(); k++) {
			if (isTrave) {
				break;
			}
			if (list[k].getTop() == '$' && strState == list[k].getOldState() && ('#' == list[k].getTrans())) {
				isTrave = true;
				strState = list[k].getNewState();//状态转移到新状态
				cout << "The top of stack is ：" << stack.top() << "deal the char，change the stack" << endl;
				cout << list[k].toString() << endl;
				cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			}
		}
	}
	else {
		cout << "After all strings are recognized, the top character of the stack is:" << stack.top() << "Not a makeing stack flag$" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}
	if (strState == endState) {
		cout << "The characters B and C appear in the string the same number of times, can be correctly accepted by the PDA," << endl << " the complete string recognition in the final state is" << strState << endl;
	}
	else {
		cout << "The characters B and C appear in the string for different times and are rejected by the PDA. after the string is all recognized ,The current state is  " << strState << endl;

	}
	return 0;

}