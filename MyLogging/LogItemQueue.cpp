#include "LogItemQueue.h"
//还是一个单利模式
namespace logging
{
	LogItemQueue&LogItemQueue::GetInstance()
	{
		static LogItemQueue queue;
		return queue;
	}
	LogItemQueue::LogItemQueue()
	{
		
	}
}