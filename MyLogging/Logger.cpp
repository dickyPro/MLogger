#include<thread>
#include<chrono>
#include<map>
#include<iomanip>
#include<cstdint>
#include "Logger.h"
#include "Priority.h"

#ifndef LOG_ENABLE_THREAD
#include "DirectLoggerStream.h"
//当前不是线程安全
namespace logging
{
	typedef DirectLoggerStream ActiveLoggerStream;
}
#else
#include<thread>
#include "ThreadLoggerStream.h"
#include "LogItemQueue.h"
//线程安全输出流
namespace logging
{
	typedef ThreadLoggerStream ActiveLoggerStream;
}
#endif

using namespace std;
using namespace logging;
namespace logging
{
	
	template<typename DestDuration,typename SrcDuration> int64_t DurationCount(SrcDuration srcDu);
	
	template<typename TimePoint> string FormatBasicTime(const TimePoint& timePoint);
	
	template<typename TimePoint> string FormatExtendTime(const TimePoint& timePoint);
	
	//获取对应优先级下的消息
	static map<Priority,string> &GetPriNameByPriority();
	
	//列表初始化
	Logger::Logger(Priority pri, const string& logFile, int32_t sourceLine):
		_pri(pri), _srcFile(logFile), _loggerStreamPtr(new ActiveLoggerStream(pri)),
		_srcLine(sourceLine), _inOutput(false)
	{

	}

	//日志对象释放
	Logger::~Logger()
	{
		endl();
		_loggerStreamPtr->Output(_bufferStream.str());
		_loggerStreamPtr->Submit();
		//使用智能指针，在这里自动释放
	}
	
	//获取文件全路径下的名称
	static string GetRelativeFileName(const string& filePath)
	{
		#ifndef WIN32
			const char PATH_SPLASH='/';
		#else
			const char PATH_SPLASH='\\';
		#endif
		//反向查找
		auto pos=filePath.rfind(PATH_SPLASH);
		if(pos==string::npos) return filePath;
		
		//防止出现两个目录符号
		char prefix=filePath[pos];
		if(prefix==PATH_SPLASH)
		{
			return std::move(filePath.substr(pos+1));
		}
		return std::move(filePath.substr(pos));
	}
	
	//输出前缀路径
	void Logger::OutputPrefix()
	{
		string prefix=FormatPrefix();
		_bufferStream<<prefix;
	}
	
	//每天会产生很多日志，因此我们需要一个公共的前缀
	string Logger::FormatPrefix()
	{
		auto now=chrono::system_clock::now();
		string basicTime=FormatBasicTime(now);
		string extendTime=FormatExtendTime(now);
		
		if(_srcFileName.empty())
		{
			_srcFileName=GetRelativeFileName(_srcFile);
		}
		
		ostringstream formatter;
		//公共前缀格式:"[+当前优先级+]+[当前时间+扩展时间+文件名称]+[原代码的行号]"
		formatter<<"["<<GetPriNameByPriority()[_pri]<<"]"<<
		"["<<basicTime<<extendTime<<"]"<<
		"["<<_srcFileName<<":"<<_srcLine<<"]";
		
		return std::move(formatter.str());
	}
	
	//计算SrcDuration模式下，有多个目标单位的数量
	template<typename DestDuration,typename SrcDuration> int64_t DurationCount(SrcDuration srcDu)
	{
		return srcDu.count()*DestDuration::period::den*SrcDuration::period::num/
		       DestDuration::period::num/SrcDuration::period::den;
	}
	
	template<typename TimePoint> string FormatBasicTime(const TimePoint& timePoint)
	{
		//转成C下的time
		time_t rawtime=TimePoint::clock::to_time_t(timePoint);
		
		char timeBuffer[80];
		//localtime_s运行在windows下
		//localtime_r运行在linux
		//因为原始的localtime不是系统安全的
		#ifdef WIN32
			tm timeInfoObj;
			tm *timeInfo=&timeInfoObj;
			//转为tm结构
			localtime_s(timeInfo,&rawtime);
		#else
			tm* timeInfo=localtime(&rawtime);
		#endif
		
		strftime(timeBuffer,80,"%Y-%m-%d %H:%M:%S",timeInfo);
		return string(timeBuffer);
	}
	//计算扩展时间，time_since_epoch函数用来获得1970年1月1日到time_point时间经过的duration
	template<typename TimePoint> string FormatExtendTime(const TimePoint& timePoint)
	{
		//创建时间点
		typename TimePoint::duration du=timePoint.time_since_epoch();
		
		//计算出有多少纳秒
		int64_t ns=DurationCount<chrono::nanoseconds>(du)%(1000*1000*1000);
		//微秒数
		int64_t microsenconds=ns/1000;
		//毫秒
		int64_t millisenconds = microsenconds % 1000;
		
		ostringstream formatter;
		formatter<<setw(3)<<setfill('0')<<millisenconds<<
		           setw(3)<<setfill('0')<<microsenconds;
		
		return std::move(formatter.str());
	}
	//根据优先级来获取起对应的字符串类型的参数
	static map<Priority,string> &GetPriNameByPriority()
	{
		static map<Priority,string> priNames=
		{
			{LOG_DEBUG,"DEBUG"},
				{LOG_INFO,"INFO"},
					{LOG_WARNING,"WARNING"},
						{LOG_ERROR,"ERROR"},
							{LOG_FATAL,"FATAL"}
					
		};
		return priNames;
	}
	//当当前的日志队列为空的时，则将线程进行挂起操作
	void WaitLoggerThread()
	{
		#ifdef LOG_ENABLE_THREAD
			while(!LogItemQueue::GetInstance().Empty())
			{
				this_thread::sleep_for(chrono::millisenconds(500));
			}
		#endif
	}
}
//如果他连续调用endl()

logging::Logger& endl(logging::Logger& logger)
{
	logger.endl();
	return logger;
}