#ifndef IOSTREAMMANAGER_H
#define IOSTREAMMANAGER_H

//����IO����,����ģʽ

#include<vector>
#include<map>
#include<set>
#include<string>

#include "Priority.h"

using namespace std;

namespace logging
{
	class IOStreamManager
	{
	public:
		static IOStreamManager & GetInstance();
		~IOStreamManager();
		vector<ostream*> GetDefaultOutputStreams(Priority pri);//��ȡ��Ĭ�ϵ����������

		//����ostream������Ӱ��������õ�������
		void SetOutputStream(ostream* outputStream, bool toManage = true);
		void SetOutputStream(Priority pri, ostream* outputStream, bool toManage = true);
		void SetOutputStream(vector<Priority> pris, ostream* outputStream, bool toManage = true);

		void SetOutputFile(const string& fileName);
		void SetOutputFile(Priority pri, const string& fileName);
		void SetOutputFile(vector<Priority> pris, const string& fileName);


	private:

		IOStreamManager();
		ostream* CreateOutputFile(const string& fileName);
	private:
		map<Priority, vector<ostream*>> _defaultOutputStreams;
		set<ostream*> _managedStreams;
	};
}
#endif


