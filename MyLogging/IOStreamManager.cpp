#include<iostream>
#include<fstream>
#include<sstream>
#include "IOStreamManager.h"
using namespace std;
namespace logging
{
	vector<ostream*> IOStreamManager::GetDefaultOutputStreams(Priority pri)
	{
		return _defaultOutputStreams[pri];
	}
	IOStreamManager::IOStreamManager()
	{
	}
	IOStreamManager::~IOStreamManager()
	{
	}
	//��ʾ���´����������󣬼�����ÿһ��
	void IOStreamManager::SetOutputStream(ostream* outputStream, bool toManage)
	{
		for (auto outputStreaPtr : _defaultOutputStreams)
		{
			_defaultOutputStreams[outputStreaPtr.first].push_back(outputStream);
		}

		if (toManage)
		{
			_managedStreams.insert(outputStream);
		}
	}
	//ֻ�ڶ�Ӧ�����ȼ��½������
	void IOStreamManager::SetOutputStream(Priority pri, ostream* outputStream, bool toManage)
	{
		_defaultOutputStreams[pri].push_back(outputStream);
		if (toManage)
		{
			_managedStreams.insert(outputStream);
		}
	}

	//���ȼ������½������
	void IOStreamManager::SetOutputStream(vector<Priority> pris, ostream* outputStream, bool toManage)
	{
		for (const auto& priItem:pris)
		{
			_defaultOutputStreams[priItem].push_back(outputStream);
		}
		 
		if (toManage)
		{
			_managedStreams.insert(outputStream);
		}
	}
	//��ʾ�����µ��������Ҳ������־�ļ�
	void IOStreamManager::SetOutputFile(const string& fileName)
	{
		ostream* outputStream = CreateOutputFile(fileName);
		if (!outputStream) return;
		SetOutputStream(outputStream, true);
	}
	void IOStreamManager::SetOutputFile(Priority pri, const string& fileName)
	{
		ostream* outputStream = CreateOutputFile(fileName);
		if (!outputStream) return;
		SetOutputStream(pri, outputStream, true);
	}
	void IOStreamManager::SetOutputFile(vector<Priority> pris, const string& fileName)
	{
		ostream* outputStream = CreateOutputFile(fileName);
		if (!outputStream) return;
		SetOutputStream(std::move(pris), outputStream, true);
	}

	//��������ģʽ
	IOStreamManager& IOStreamManager::GetInstance()
	{
		static IOStreamManager instance;
		return instance;
	}

	ostream* IOStreamManager::CreateOutputFile(const string& fileName)
	{
		// Initialize file stream
		ofstream* fileStream = new ofstream();
		ios_base::openmode mode = ios_base::out;
		mode |= std::ios_base::trunc;
		fileStream->open(fileName, mode);

		// Error handling
		if (!fileStream->is_open()) {
			// Print error information
			ostringstream ss_error;
			ss_error << "FATAL ERROR:  could not Open log file: [" << fileName << "]";
			ss_error << "\n\t\t std::ios_base state = " << fileStream->rdstate();
			cerr << ss_error.str().c_str() << std::endl << std::flush;

			// Cleanup
			fileStream->close();
			delete fileStream;
			fileStream = nullptr;
		}

		return fileStream;
	}
}
