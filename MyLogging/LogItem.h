#ifndef LOGITEM_H
#define LOGITEM_H

#include<string>
#include "Logger.h"
#include "Priority.h"
//日志条目信息，判断是否为空+优先级+具体类型
using namespace std;

namespace logging
{
	class LogItem
	{
		public:
			LogItem():_empty(true){}
			
			LogItem(Priority pri,const string& content):_empty(false),_pri(pri),_content(content){}
			
			bool Empty()const
			{
				return _empty;
			}
			void SetEmpty(bool empty)
			{
				_empty=empty;
			}
			
			Priority GetPriority()const
			{
				return _pri;
			}
			void SetPriority(Priority pri)
			{
				_pri=pri;
			}
			
			const string& GetContent()const
			{
				return _content;
			}
			void SetContent(const string& content)
			{
				_content=content;
			}
		
		private:
			bool _empty;
			Priority _pri;
			string _content;
	};
}
#endif