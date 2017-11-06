#include<vector>
#include "LoggerOutputThread.h"
#include "LogItemQueue.h"
#include "LogItem.h"
#include "IOStreamManager.h"

using namespace logging;
namespace logging
{
	static LogItemThread LogItemThreadInstance;
	LogItemThread::LogItemThread():_needToStop(false)
	{
		_workThread=thread(&LogItemThread::ThreadEntry,this);
		_workThread.detach();
	}
	
	LogItemThread::~LogItemThread()
	{
		_needToStop=true;
	}
	//该线程处理函数
	void LogItemThread::ThreadEntry()
	{
		//线程安全队列
		LogItemQueue&logItemQueue=LogItemQueue::GetInstance();
		while(!_needToStop)
		{
			LogItem logItem;
			logItemQueue.Pop(logItem);
			vector<ostream*> outputStreams=IOStreamManager::GetInstance().GetDefaultOutputStreams(logItem.GetPriority());
			
			for(const auto &os : outputStreams)
			{
				*os<<logItem.GetContent();
			}
		}
	}
}