#include <string>  
#include <json.h>
#include <iostream>  
#include <fstream>  
using namespace std;

void readStrJson(); //从字符串中读取JSON  
void readStrProJson(); //从字符串中读取JSON（内容复杂些）  
void readFileJson(); //从文件中读取JSON 
void writeFileJson();  //将信息保存为JSON格式  

int main(int argc, char* argv[])
{
	 readStrJson(); //从字符串中读取JSON  
	 cout << "\n";
     readStrProJson(); //从字符串中读取JSON（内容复杂些） 
	 cout << "\n";
	 readFileJson(); //从文件中读取JSON 
	 cout << "\n";
	 writeFileJson();  //将信息保存为JSON格式  
	system("pause");
	return 0;
}
void readStrJson()
{
	//字符串  
	string str =
		"{\"name\":\"shuiyixin\",\"age\":21,\"sex\":\"man\"}";

	Json::Reader reader;
	Json::Value root;

	//从字符串中读取数据  
	if (reader.parse(str, root))
	{
		string name = root["name"].asString();
		int age = root["age"].asInt();
		string sex = root["sex"].asString();
		cout << name+ "," << age << "," << sex << endl;
	}

}

void readStrProJson()
{
	string strValue =
		"{\"name\":\"wangqinghe\",\"major\":[{\"AI\":\"MachineLearning\"},{\"AI\":\"DeepLearning\"},{\"AI\":\"PictureLearning\"}]}";
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(strValue, value))
	{
		string str = value["name"].asString();
		cout << "name:" <<str<< endl;
		Json::Value arrayobj = value["major"];
		for (unsigned int i = 0; i < arrayobj.size(); i++)
		{
			str = arrayobj[i]["AI"].asString();
			cout << str << endl;
		}
	}
}

void readFileJson()
{ 
	Json::Reader reader;
	Json::Value root;

	ifstream in("demo.json", ios::binary);
	if (!in.is_open())
	{
		cout << "Error opening file\n";
		return ;
	}
	if (reader.parse(in, root))
	{
		string name = root["name"].asString();
		string age = root["age"].asString();
		string sex = root["sex"].asString();

		cout << "name:" << name << endl;
		cout << "age:" << age << endl;
		cout << "sex:" << sex << endl;


		string friend_name = root["bro"]["friend_name"].asString();
		string friend_age = root["bro"]["friend_age"].asString();
		string friend_sex = root["bro"]["friend_sex"].asString();
		cout << "friend_name:" << friend_name << endl;
		cout << "friend_age:" << friend_age << endl;
		cout << "friend_sex:" << friend_sex << endl;


		for (unsigned int i = 0; i < root["hobby"].size(); i++)
		{
			string str = root["hobby"][i].asString();
			cout << str << "\t";
		}

	}
	else
	{
		cout << "parse error\n" << endl;
	}
	in.close();

}

void writeFileJson()
{
	//根节点
	Json::Value root;
	root["name"] = Json::Value("Wangqinghe");
	root["age"] = Json::Value("22");
	root["sex"] = Json::Value("man");

	//子节点
	Json::Value bro;
	bro["friend_name"] = Json::Value("Wangwenjian");
	bro["friend_age"] = Json::Value("25");
	bro["friend_sex"] = Json::Value("man");

	root["bro"] = Json::Value(bro);

	//数组形式
	root["hobby"].append("sing");
	root["hobby"].append("run");
	root["hobby"].append("basketball");


	cout << "StyledWriter:" << endl;
	Json::StyledWriter sw;
	cout << sw.write(root) << endl << endl;

	ofstream os;
	os.open("demo.json", std::ios::out);
	if (!os.is_open())
	{
		cout << "error:can't find the file" << endl;
	}
	os << sw.write(root);
	os.close();

}