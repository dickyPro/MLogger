#ifndef DIRECTLOGGERSTREAM_H
#define DIRECTLOGGERSTREAM_H
//该类不是线程安全的类
#include<vector>
#include <memory>
#include<ostream>
#include "LoggerStream.h"
#include "Priority.h"
using namespace std;
namespace logging
{

	class DirectLoggerStream :
		public LoggerStream
	{
	public:
		DirectLoggerStream(Priority pri);
		virtual ~DirectLoggerStream();

		virtual void Output(const string&message) override;
		virtual void Submit()override;

	private:
		vector<ostream*> _outputStreams;
	};
}
#endif


