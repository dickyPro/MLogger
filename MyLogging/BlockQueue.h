#ifndef LOGGING_BLOCKQUEUE_H
#define LOGGING_BLOCKQUEUE_H
//通用类
//线程安全队列，对于没有IO而光有计算任务的线程，使用blockqueue来完成任务队列
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
			//唤醒所有线程，退出操作
			
		}
		//压入任务
		void Push(const _Ty & ele)
		{
			unique_lock<mutex> lock(_mutex);
			{
				_queue.push(ele);
				_emptyCv.notify_one();
			}
		}
		//获取队列中任务
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

		//获取队列的队列头，但是不需要弹出
		bool Peek(_Ty & ele)const
		{
			std::unique_lock<std::mutex> locker(_mutex);

			if (!_queue.size()) {
				return false;
			}

			ele = std::move(_queue.front());
			return true;
		}
		//判断是否为空
		bool Empty()const
		{
			std::unique_lock<std::mutex> locker(_mutex);

			return _queue.size() == 0;
		}
		//任务队列的大小
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