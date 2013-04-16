// list AddressBook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
#include <string>
#include <regex>
#include "iostream"
using namespace std;

//个人信息结构
class PersonInfo 
{
public:
	PersonInfo(){}
	~PersonInfo(){}
	string strName;
	string strPhoneNum;
	string strAddr;
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::list<PersonInfo*> listPeople;
	string strCommand;
	while(true)
	{
		cin>>strCommand;
		if (strCommand.substr(0,1) == "!")
		{
			if (strCommand.substr(1) == "help")
			{
				cout<<("Current support command:add,search,delete,!help,!quit\n");
				continue;
			}
			if (strCommand.substr(1) == "quit")
			{
				cout<<("Exiting!\n");
				goto GO_EXIT;
			}
			cout<<("Invalid command,Try !help\n");
			continue;
		}
		else
		{
			if (strCommand == "add")
			{
				PersonInfo * pInfo = new PersonInfo();
				if (pInfo == NULL)
				{
					cout<<("Failed to allocate PersonInfo struct!\n");
					continue;
				}
				cout<<"name:";
				cin>>pInfo->strName;
				cout<<"mobile:";
				cin>>pInfo->strPhoneNum;
				cout<<"address:";
				cin>>pInfo->strAddr;
				listPeople.push_back(pInfo);
				continue;
			}
			if (strCommand == "search")
			{
				string strFindby;
				string strPattern;
				cout<<"by (name|mobile|address):";
				cin>>strFindby;
				cout<<strFindby<<":";
				cin>>strPattern;
				//Type=1 name;  Type=2 mobile;  Type=3 address
				int iSearchType = 0;
				if (strFindby == "name")
					iSearchType = 1;
				if (strFindby == "mobile")
					iSearchType = 2;
				if (strFindby == "address")
					iSearchType = 3;
				if (iSearchType == 0)
				{
					cout<<"Invalid input of:"<<strFindby<<", must be name|mobile|address"<< endl;
					continue;
				}
				std::regex pattern;
				try
				{
					pattern.assign(strPattern.c_str());
				}
				catch (const std::regex_error& e)
				{
					std::cout << "regex_error caught: " << e.what() << '\n';
				}	
				std::cmatch  result;
				std::list<PersonInfo*>::iterator listIT;
				PersonInfo * pInfo = NULL;
				for (listIT = listPeople.begin(); listIT != listPeople.end(); ++listIT)
				{
					pInfo = *listIT;
					bool bMatch = false;
					switch(iSearchType)
					{
					case 1:
						bMatch = std::regex_search(pInfo->strName.c_str(), result, pattern);
						break;
					case 2:
						bMatch = std::regex_search(pInfo->strPhoneNum.c_str(), result, pattern);
						break;
					case 3:
						bMatch = std::regex_search(pInfo->strAddr.c_str(), result, pattern);
						break;
					}
					if (bMatch)
					{
						cout<<"name:"<<pInfo->strName<<"\t\t"<<"mobile:"<<pInfo->strPhoneNum<<"\t\t"<<"address:"<<pInfo->strAddr<<endl;
					}
				}
				continue;
			}
			if (strCommand == "delete")
			{
				string strFindby;
				string strPattern;
				cout<<"by (name|mobile|address):";
				cin>>strFindby;
				cout<<strFindby<<":";
				cin>>strPattern;
				//Type=1 name;  Type=2 mobile;  Type=3 address
				int iSearchType = 0;
				if (strFindby == "name")
					iSearchType = 1;
				if (strFindby == "mobile")
					iSearchType = 2;
				if (strFindby == "address")
					iSearchType = 3;
				if (iSearchType == 0)
				{
					cout<<"Invalid input of:"<<strFindby<<", must be name|mobile|address"<< endl;
					continue;
				}
				std::regex pattern;
				try
				{
					pattern.assign(strPattern.c_str());
				}
				catch (const std::regex_error& e)
				{
					std::cout << "regex_error caught: " << e.what() << '\n';
				}	
				std::cmatch  result;
				std::list<PersonInfo*>::iterator listIT;
				PersonInfo * pInfo = NULL;
				for (listIT = listPeople.begin(); listIT != listPeople.end();)
				{
					pInfo = *listIT;
					bool bMatch = false;
					switch(iSearchType)
					{
					case 1:
						bMatch = std::regex_search(pInfo->strName.c_str(), result, pattern);
						break;
					case 2:
						bMatch = std::regex_search(pInfo->strPhoneNum.c_str(), result, pattern);
						break;
					case 3:
						bMatch = std::regex_search(pInfo->strAddr.c_str(), result, pattern);
						break;
					}
					if (bMatch)
					{
						delete *listIT;
						listIT = listPeople.erase(listIT);
					}
					else
					{
						++listIT;
					}
				}
				continue;
			}
			cout<<("Invalid command,Try !help\n");
			continue;
		}
	}
GO_EXIT:
	std::list<PersonInfo*>::iterator listIT;
	for (listIT = listPeople.begin(); listIT != listPeople.end(); ++listIT)
	{
		delete *listIT;
	}
	return 0;
}

