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
		//���캯������־�����ȼ�����־�ļ������Ŀ¼���Լ�ԭʼ��������к�
		Logger(Priority pri,const string& logFile,int32_t sourceLine);
		 
		virtual ~Logger();

		//���ǰ׺
		virtual void OutputPrefix() ;
		//��ʽ���ַ���
		virtual string FormatPrefix();

		//��־���
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
		//������һ��function�����԰󶨺���
		Logger& operator<<(LoggerHandle logHandler)
		{
			return logHandler(*this);
		}


		//����<<��������������õ�Ŀ�����ܹ��������
		template<typename Value> Logger&operator<<(Value value)
		{
			return Output(std::forward<Value>(value));
		}

		//��ȡ��ǰ���������
		Logger& Reference()
		{
			return *this;
		}

		//Ҳ���ǽ��л���
		void endl()
		{
			_bufferStream << std::endl;
		}
	private:
		Priority _pri;
	protected:
		//����ļ�
		ostringstream _bufferStream;
		shared_ptr<LoggerStream> _loggerStreamPtr;
		 
	private:
		string _srcFile;//ԭʼ�ļ�·��
		string _srcFileName;//ԭʼ�ļ�����
		int32_t _srcLine;//ԭʼ��������к�
		bool _inOutput;
	};
	//ʹ�ð�������
	//#define LAZY_STREAM(stream, condition)  !(condition) ? (void)0 : ::logging::LogMessageVoidify() & (stream)//�����������ص�
	//ȥ�������ڵľ���
	//����һ�������������־,�����һ����������Ȩ�Ĳ�����
	//����Ȩ����<<���Ǹ���?:
	class LogMessageVoidify
	{
	public:
		LogMessageVoidify(){}
		void operator&(Logger&) { }
	};
	
	//�ж�log�����Ƿ�Ϊ��
	void WaitLoggerThread();
}


#endif

