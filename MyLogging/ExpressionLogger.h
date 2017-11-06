#ifndef EXPRESSIONLOGGER_H
#define EXPRESSIONLOGGER_H
//支持表达式比较
#include "Logger.h"

using namespace logging;
namespace logging
{
	class ExpressionLogger:public Logger
	{
		public:
			ExpressionLogger(Priority pri,const string&srcFile,int32_t srcLine,const string&expression);
			virtual~ExpressionLogger();
			string GetExpression() const;
			void SetExpression(const string&expression);
		private:
			string _expression;
	};
}
#endif