#ifndef THREADLOGGERSTREAM_H
#define THREADLOGGERSTREAM_H

#include<string>
#include<vector>
#include<iostream>
#include "Priority.h"
#include "LoggerStream.h"
using namespace std;
using namespace logging;
namespace logging
{
	class ThreadLoggerStream:public LoggerStream
	{
		public:
			ThreadLoggerStream(Priority pri);
			virtual ~ThreadLoggerStream();
			
			virtual void Output(const string&message) override;
			virtual void Submit();
		private:
			string _buffer;
			bool _isSubmitted;
			
	};
}
#endif