#include <iostream>
#include<fstream>
#include<json/json.h>

using namespace std;
using namespace Json;

/*
[
	"luffy", 19, 170, false, 
	["ace", "sabo"],
	{"sex":"max", "girlfriend":"Hancock"}
]
*/

void writeJson()
{
	Value root;
	root.append("luffy");
	root.append(19);
	root.append(170);
	root.append(false);

	Value subArray;
	subArray.append("ace");
	subArray.append("sabo");
	root.append(subArray);

	Value obj;
	obj["sex"] = "max";
	obj["girlfriend"] = "Hancock";
	root.append(obj);

/*
#if CONDITION
	// 如果 CONDITION 为真，这部分代码会被编译
#else
	// 如果 CONDITION 为假，这部分代码会被编译
#endif
*/

#if 1
	string json = root.toStyledString();
#else 
	FastWriter w;
	string json = w.write(root);
#endif
	ofstream ofs("test.json");
	ofs << json;
	ofs.close();
}

void readJson()
{
	ifstream ifs("test.json");
	Reader rd;
	Value root;
	rd.parse(ifs, root);

	if (root.isArray())
	{
		for (unsigned i = 0; i < root.size(); i++)
		{
			Value item = root[i];
			if (item.isInt())
			{
				cout << item.asInt() << ",";
			}
			else if (item.isString())
			{
				cout << item.asString() << ", ";
			}
			else if (item.isBool())
			{
				cout << item.asBool() << ", ";
			}
			else if (item.isArray())
			{
				for (unsigned j = 0; j < item.size(); j++)
				{
					cout << item[j].asString() << ", ";
				}
			}
			else if (item.isObject())
			{
				Value::Members keys = item.getMemberNames();
				for (unsigned k = 0; k < keys.size(); k++)
				{
					cout << keys.at(k) << ":" << item[keys[k]] << ", ";
				}
			}
			cout << endl;
		}
	}
	else if (root.isObject())
	{

	}
}

int main()
{
	writeJson();
	readJson();
	return 0;
}