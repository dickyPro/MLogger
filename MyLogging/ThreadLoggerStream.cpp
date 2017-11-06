#include "ThreadLoggerStream.h"
#include "LogItemQueue.h"
#include "LogItem.h"

using namespace logging;
using namespace std;

namespace logging
{
	ThreadLoggerStream::ThreadLoggerStream(Priority pri):
		LoggerStream(pri),_isSubmitted(false)
		{
			
		}
	//当流结束之时，则将内容压缩到安全队列
	ThreadLoggerStream::~ThreadLoggerStream()
	{
		Submit();
	}
	
	void ThreadLoggerStream::Output(const string& message)
	{
		_buffer+=message;
	}
	//判断是否已经提交到任务队列中
	void ThreadLoggerStream::Submit()
	{
		if(!_isSubmitted)
		{
			LogItem logItem(GetPriority(),_buffer);
			LogItemQueue::GetInstance().Push(logItem);
			_isSubmitted=true;
		}
	}
}