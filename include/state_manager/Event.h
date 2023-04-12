#ifndef _EVENT_H_
#define _EVENT_H_

namespace HsmState
{
	enum EventDeal
	{
		tail = 0, // 事件结束处理
		keep_on	  // 事件继续传递
	};

	// 事件数据
	class EventData
	{
	public:
		EventData(int event_type)
		{
			event_type_ = event_type;
			data_ = nullptr;
		}

		template <class T>
		void SetData(T *t)
		{
			data_ = t;
		}

		template <class T>
		T *GetData()
		{
			return (T *)data_;
		}

		int event_type_;

	private:
		void *data_;
	};
}

#endif
