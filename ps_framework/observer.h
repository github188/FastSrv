#ifndef __PS_FW_OBSERVER__
#define __PS_FW_OBSERVER__
////////////////////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月22日
//	Modify history :
//					2014年8月22日 zengpw 创建
//					2014年9月1日 zengpw 重新设计
//	File Property : private
//	Description :	I. 事件观察者，它持有 Subject 对象
//					II. Subject 对象在有事件发生时，会主动调用观察者的 Update 接口
//					III. 抽象基类，无法被构造，只能被继承
//
//
////////////////////////////////////////////////////////////////////////////////////////

namespace PS_FW
{
	class Subject;

	class Observer
	{
	public:
		virtual ~Observer(){}
	public:
		virtual void Update(Subject* pSubject) = 0;
	protected:
		Observer(){}
	};
}	//PS_FW

#endif //__PS_FW_OBSERVER__
