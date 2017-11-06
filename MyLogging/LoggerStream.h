#ifndef LOGGERSTREAM_H
#define LOGGERSTREAM_H
//�������ܵĿ��ǣ����Զ���һ��stream��Ŀǰֻ֧���ַ��������
//����muduo��Դ�����־����LogStream�������������Ͱ�ȫ�����Ϳ���չ�ԣ�
//Ч��Ҳ�ߣ���֧�ֶ��Ƹ�ʽ������֧��locale��facet��û�м̳У�bufferҲû�м̳����麯����û�ж�̬�����ڴ棬buffer�̶�
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

		//���麯��

		//muduo������<<�����
		virtual void Output(const string& message) = 0;
		//�ύ
		virtual void Submit() = 0;
	private:
		Priority _pri;

	};
}
#endif