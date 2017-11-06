#ifndef LOGGER_H
#define LOGGER_H
#include<string>
#include<cstdint>
#include<sstream>
#include<memory>
#include<functional>
#include "Priority.h"
#include "LoggerStream.h"
using namespace std;
using namespace logging;
namespace logging
{
	class Logger;
}
//namespace std
//{
//	logging::Logger& endl(logging::Logger&logger);
//}
namespace logging
{
	class Logger
	{

		using LoggerHandle = function<Logger&(Logger&)>;
	public:
		//构造函数，日志的优先级，日志文件的输出目录，以及原始代码的行列号
		Logger(Priority pri,const string& logFile,int32_t sourceLine);
		 
		virtual ~Logger();

		//输出前缀
		virtual void OutputPrefix() ;
		//格式化字符串
		virtual string FormatPrefix();

		//日志输出
		template<typename Value>Logger& Output(Value value)
		{
			if (!_inOutput)
			{
				_inOutput = true;
				OutputPrefix();
			}
			_bufferStream << value;
			return *this;
		}
		//参数是一个function，可以绑定函数
		Logger& operator<<(LoggerHandle logHandler)
		{
			return logHandler(*this);
		}


		//重载<<运算符，返回引用的目的是能够连续输出
		template<typename Value> Logger&operator<<(Value value)
		{
			return Output(std::forward<Value>(value));
		}

		//获取当前对象的引用
		Logger& Reference()
		{
			return *this;
		}

		//也就是进行换行
		void endl()
		{
			_bufferStream << std::endl;
		}
	private:
		Priority _pri;
	protected:
		//输出文件
		ostringstream _bufferStream;
		shared_ptr<LoggerStream> _loggerStreamPtr;
		 
	private:
		string _srcFile;//原始文件路径
		string _srcFileName;//原始文件名称
		int32_t _srcLine;//原始代码的行列号
		bool _inOutput;
	};
	//使用案例如下
	//#define LAZY_STREAM(stream, condition)  !(condition) ? (void)0 : ::logging::LogMessageVoidify() & (stream)//这两个是重载的
	//去除编译期的警告
	//满足一定条件下输出日志,这个是一个具有优先权的操作符
	//优先权低于<<但是高于?:
	class LogMessageVoidify
	{
	public:
		LogMessageVoidify(){}
		void operator&(Logger&) { }
	};
	
	//判断log队列是否为空
	void WaitLoggerThread();
}


#endif

