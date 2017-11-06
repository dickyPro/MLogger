#ifndef LOGGING_BLOCKQUEUE_H
#define LOGGING_BLOCKQUEUE_H
//ͨ����
//�̰߳�ȫ���У�����û��IO�����м���������̣߳�ʹ��blockqueue������������
#include <condition_variable>
#include <string>
#include <queue>
#include <chrono>
#include <mutex>
using namespace std;
namespace CommonUtils
{

	template<typename _Ty> class CBlockingQueue
	{
	public:
		CBlockingQueue():_queue(),_mutex(),_emptyCv() {
		}

		virtual ~CBlockingQueue() {
			//���������̣߳��˳�����
			
		}
		//ѹ������
		void Push(const _Ty & ele)
		{
			unique_lock<mutex> lock(_mutex);
			{
				_queue.push(ele);
				_emptyCv.notify_one();
			}
		}
		//��ȡ����������
		bool Pop(_Ty&ele, int32_t millisecond = 0)
		{
			unique_lock<mutex> lock(_mutex);
			if (!_queue.size())
			{
				if (millisecond == 0)
				{
					_emptyCv.wait(lock);
				}
				else
				{
					_emptyCv.wait_for(lock, chrono::milliseconds(millisecond));
					if (!_queue.size()) return false;
				}
			}
			ele=_queue.front();
			_queue.pop();
			return true;
		}

		//��ȡ���еĶ���ͷ�����ǲ���Ҫ����
		bool Peek(_Ty & ele)const
		{
			std::unique_lock<std::mutex> locker(_mutex);

			if (!_queue.size()) {
				return false;
			}

			ele = std::move(_queue.front());
			return true;
		}
		//�ж��Ƿ�Ϊ��
		bool Empty()const
		{
			std::unique_lock<std::mutex> locker(_mutex);

			return _queue.size() == 0;
		}
		//������еĴ�С
		int32_t Size()const
		{
			std::unique_lock<std::mutex> locker(_mutex);

			return _queue.size();
		}
	 
	private:
		mutable mutex _mutex;
		condition_variable _emptyCv;
		queue<_Ty> _queue;
	};

}
#endif