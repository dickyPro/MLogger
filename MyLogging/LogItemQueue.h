#ifndef LOGITEMQUEUE_H
#define LOGITEMQUEUE_H
#include "BlockQueue.h"
#include "LogItem.h"
using namespace CommonUtils;
namespace logging
{
	class LogItemQueue :public CBlockingQueue<LogItem>
	{
		public:
			static LogItemQueue& GetInstance();
			LogItemQueue(const LogItemQueue&)=delete;
			LogItemQueue& operator=(const LogItemQueue&)=delete;
			
		private:
			LogItemQueue();
	};
}

#endif