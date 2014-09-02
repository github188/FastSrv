#ifndef __PS_FW_SUBJECT__
#define __PS_FW_SUBJECT__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月22日
//	Modify history :
//					2014年8月22日 zengpw 创建
//					2014年9月1日 zengpw 重新设计
//	File Property : private
//	Description :	I. 提供主动触发事件的入口
//					II. 如果一个类要主动通知其它类，则可以继承自 Subject
//					III. 抽象基类，无法被构造，只能被继承
//
//
////////////////////////////////////////////////////////////////////////////////////////

#include "observer.h"

namespace PS_FW
{
	class Subject
	{
	public:
		virtual ~Subject(){}
	public:
		virtual void Attach(Observer* pObserver)
		{
			m_pListObserver->push_back(pObserver);
		}

		virtual void Detach(Observer* pObserver)
		{
			m_pListObserver->remove(pObserver);
		}

		virtual void Notify()
		{
			std::list<Observer*>::iterator pos;
			for (pos = m_pListObserver->begin();pos != m_pListObserver->end();++pos)
			{
				(*pos)->Update(this);
			}
		}
	protected:
		Subject()
		{
			m_pListObserver = new std::list<Observer*>;
		}
	private:
		std::list<Observer*>* m_pListObserver;
	};
}	//PS_FW

#endif //__PS_FW_SUBJECT__
