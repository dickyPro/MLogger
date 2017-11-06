#ifndef LOGGERSTREAM_H
#define LOGGERSTREAM_H
//处于性能的考虑，将自定义一个stream，目前只支持字符串的输出
//参照muduo开源库的日志流，LogStream，其做到了类型安全和类型可扩展性，
//效率也高，不支持定制格式化，不支持locale、facet，没有继承，buffer也没有继承与虚函数。没有动态分配内存，buffer固定
#include"Priority.h"
#include<string>
using namespace std;
using namespace logging;

namespace logging
{
	class LoggerStream
	{
	public:
		LoggerStream(Priority pri) :_pri(pri)
		{

		}
		void SetPriority(Priority pri)
		{
			_pri = pri;
		}
		Priority GetPriority()
		{
			return _pri ;
		}

		//纯虚函数

		//muduo重载了<<运算符
		virtual void Output(const string& message) = 0;
		//提交
		virtual void Submit() = 0;
	private:
		Priority _pri;

	};
}
#endif