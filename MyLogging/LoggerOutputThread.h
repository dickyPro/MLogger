#ifndef LOGGEROUTPUTTHREAD_H
#define LOGGEROUTPUTTHREAD_H

#include<thread>
using namespace std;

namespace logging
{
	class LogItemThread
	{
		public:
			LogItemThread();
			~LogItemThread();
			
		private:
			void ThreadEntry();
		private:
			bool _needToStop;
			thread _workThread;
	};
}
#endif