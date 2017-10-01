#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

namespace messaging
{
	struct message_base  // ������Ļ�����
	{
		virtual ~message_base()
		{
		}
	};

	template<typename Msg>
	struct wrapped_message :  // ÿ����Ϣ���Ͷ���Ҫ�ػ�
		message_base
	{
		Msg contents;

		explicit wrapped_message(Msg const& contents_) :
			contents(contents_)
		{
		}
	};

	class queue  // ���ǵĶ���
	{
		std::mutex m;
		std::condition_variable c;
		std::queue<std::shared_ptr<message_base> > q;  // ʵ�ʴ洢ָ��message_base��ָ��Ķ���
	public:
		template<typename T>
		void push(T const& msg)
		{
			std::lock_guard<std::mutex> lk(m);
			q.push(std::make_shared<wrapped_message<T> >(msg));  // ��װ�Ѵ��ݵ���Ϣ���洢ָ��
			c.notify_all();
		}

		std::shared_ptr<message_base> wait_and_pop()
		{
			std::unique_lock<std::mutex> lk(m);
			c.wait(lk, [&] {return !q.empty(); });  // ������Ϊ��ʱ����
			auto res = q.front();
			q.pop();
			return res;
		}
	};
}

//sender
namespace messaging
{
	class sender
	{
		queue*q;  // sender��һ������ָ��İ�װ��
	public:
		sender() :  // sender�޶���(Ĭ�Ϲ��캯��)
			q(nullptr)
		{
		}

		explicit sender(queue*q_) :  // ��ָ����е�ָ����й���
			q(q_)
		{
		}

		template<typename Message>
		void send(Message const& msg)
		{
			if(q)
			{
				q->push(msg);  // ��������Ϣ���͸�����
			}
		}
	};
}

//receiver
namespace messaging
{
	class receiver
	{
		queue q;  // ������ӵ�ж�Ӧ����
	public:
		operator sender()  // �������ж�����ʽת��Ϊһ��sender����
		{
			return sender(&q);
		}
		dispatcher wait()  // �ȴ��Զ��н��е���
		{
			return dispatcher(&q);
		}
	};
}


//diapatcher
namespace messaging
{
	class close_queue  // ���ڹرն��е���Ϣ
	{
	};

	class dispatcher
	{
		queue* q;
		bool chained;

		dispatcher(dispatcher const&) = delete;  // dispatcherʵ�����ܱ�����
		dispatcher& operator=(dispatcher const&) = delete;

		template<
			typename Dispatcher,
			typename Msg,
			typename Func>  // ����TemplateDispatcherʵ�������ڲ���Ա
			friend class TemplateDispatcher;

		void wait_and_dispatch()
		{
			for(;;)  // 1 ѭ�����ȴ�������Ϣ
			{
				auto msg = q->wait_and_pop();
				dispatch(msg);
			}
		}

		bool dispatch(  // 2 dispatch()����close_queue��Ϣ��Ȼ���׳�
					  std::shared_ptr<message_base> const& msg)
		{
			if(dynamic_cast<wrapped_message<close_queue>*>(msg.get()))
			{
				throw close_queue();
			}
			return false;
		}
	public:
		dispatcher(dispatcher&& other) :  // dispatcherʵ�������ƶ�
			q(other.q), chained(other.chained)
		{
			other.chained = true;  // Դ���ܵȴ���Ϣ
		}

		explicit dispatcher(queue* q_) :
			q(q_), chained(false)
		{
		}

		template<typename Message, typename Func>
		TemplateDispatcher<dispatcher, Message, Func>
			handle(Func&& f)  // 3 ʹ��TemplateDispatcher����ָ�����͵���Ϣ
		{
			return TemplateDispatcher<dispatcher, Message, Func>(
				q, this, std::forward<Func>(f));
		}

		~dispatcher() noexcept(false)  // 4 �����������ܻ��׳��쳣
		{
			if(!chained)
			{
				wait_and_dispatch();
			}
		}
	};
}

namespace messaging
{
	template<typename PreviousDispatcher, typename Msg, typename Func>
	class TemplateDispatcher
	{
		queue* q;
		PreviousDispatcher* prev;
		Func f;
		bool chained;

		TemplateDispatcher(TemplateDispatcher const&) = delete;
		TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

		template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
		friend class TemplateDispatcher;  // �����ػ���TemplateDispatcher����ʵ��������Ԫ��

		void wait_and_dispatch()
		{
			for(;;)
			{
				auto msg = q->wait_and_pop();
				if(dispatch(msg))  // 1 �����Ϣ������󣬻�����ѭ��
					break;
			}
		}

		bool dispatch(std::shared_ptr<message_base> const& msg)
		{
			if(wrapped_message<Msg>* wrapper =
			   dynamic_cast<wrapped_message<Msg>*>(msg.get()))  // 2 �����Ϣ���ͣ����ҵ��ú���
			{
				f(wrapper->contents);
				return true;
			}
			else
			{
				return prev->dispatch(msg);  // 3 ���ӵ�֮ǰ�ĵ�������
			}
		}
	public:
		TemplateDispatcher(TemplateDispatcher&& other) :
			q(other.q), prev(other.prev), f(std::move(other.f)),
			chained(other.chained)
		{
			other.chained = true;
		}
		TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_) :
			q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false)
		{
			prev_->chained = true;
		}

		template<typename OtherMsg, typename OtherFunc>
		TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
			handle(OtherFunc&& of)  // 4 ������������������
		{
			return TemplateDispatcher<
				TemplateDispatcher, OtherMsg, OtherFunc>(
					q, this, std::forward<OtherFunc>(of));
		}

		~TemplateDispatcher() noexcept(false)  // 5 �����������Ҳ��noexcept(false)��
		{
			if(!chained)
			{
				wait_and_dispatch();
			}
		}
	};
}