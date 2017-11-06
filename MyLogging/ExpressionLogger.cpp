#include "ExpressionLogger.h"
namespace logging
{
	ExpressionLogger::ExpressionLogger(Priority pri, const string&srcFile, int32_t srcLine, const string&expression):
		Logger(pri, srcFile, srcLine),_expression(expression)
	{

	}
	ExpressionLogger::~ExpressionLogger()
	{

	}
	string ExpressionLogger::GetExpression() const
	{
		return _expression;
	}
	void ExpressionLogger::SetExpression(const string&expression)
	{
		_expression = expression;
	}
}