#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

struct Node
{
	string str;
	int freq;
	Node* left = 0;
	Node* right = 0;
	string code = "";
	Node(string str = "", int freq = 0, Node* left = nullptr, Node* right = nullptr)
	{
		this->str = str;
		this->freq = freq;
		this->left = left;
		this->right = right;
	}
};

void DFS(Node* root, map<string, string>& map)
{
	if (root->left) 
	{
		root->left->code += root->code + "0";
		DFS(root->left, map);
	}
	if (root->right) 
	{
		root->right->code += root->code + "1";
		DFS(root->right, map);
	}
	if (!root->left && !root->right && root->code != "")
		map[root->str] = root->code;

}

void Free(Node* root)
{
	if (root->left)
		Free(root->left);
	if (root->right)
		Free(root->right);
	root = nullptr;
}

string codeString(string inputStr, map<string, string>& codes)
{
	//шаг 1: подсчитываем частотность каждого символа в строке
	map<char, int> map;
	for (char ch : inputStr)
		map.count(ch) ? map[ch]++ : map[ch] = 1;

	//шаг 2: создаем набор плоских листьев
	set<Node*> flatLeaves;
	for (auto p : map) 
	{
		flatLeaves.insert(new Node(string(1, p.first), p.second));
	}

	//шаг 3: строим бинарное дерево
	while (flatLeaves.size() > 1)
	{
		Node* min1 = nullptr;
		Node* min2 = nullptr;

		for(Node* current : flatLeaves)
		{
			if (!min1) 
			{
				min1 = current;
				continue;
			}
			if (!min2)
			{
				if (current->freq < min1->freq)
				{
					min2 = min1;
					min1 = current;
				}
				else
					min2 = current;
				continue;
			}
			if (current->freq < min1->freq) 
			{
				if (min1->freq < min2->freq)
					min2 = min1;
				min1 = current;
			}
			if (current->freq < min2->freq && current != min1)
				min2 = current;
		}
		flatLeaves.erase(min1);
		flatLeaves.erase(min2);
		flatLeaves.insert(new Node(min1->str + min2->str, min1->freq + min2->freq, min1, min2));

	}
		
	///шаг 4: кодируем символы и храним кодировку в codes
	DFS(*flatLeaves.begin(), codes);

	//шаг 5: освобождаем уже ненужную память
	Free(*flatLeaves.begin());
	
	for(auto p : codes)
	{
		cout << p.first << ": " << p.second << '\n';
	}

	//шаг 6: кодируем строку
	string result = "";
	for (char ch : inputStr)
		result += codes[string(1, ch)];
	return result;
}

string decodeString(string codedString, map<string, string>& codes)
{
	//шаг 1: инвертируем кодировку из ключ->значение в значение->ключ
	map<string, string> decodes;
	for (auto p : codes)
		decodes[p.second] = p.first;

	string result = "";
	string builder = "";
	//шаг 2: декодируем строку
	for (int i = 0; i < codedString.length(); i++)
	{
		builder += codedString[i];
		if (decodes.count(builder)) 
		{
			result += decodes[builder];
			builder = "";
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	map<string, string> codes;
	string codedString = codeString(argv[1], codes);
	string decodedString = decodeString(codedString, codes);

	cout << "coded: " << codedString << endl;
	cout << "decoded:" << decodedString << endl;
	return 0;
}
