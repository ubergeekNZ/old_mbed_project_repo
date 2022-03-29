#include "Controller.h"

Controller::Controller(IFSM& fsm,
					   ISettings& settings, 
			           IQueue<sEvent>& queue) :
		m_fsm(fsm),
		m_settings(settings),
		m_queue(queue)
{

}

void Controller::ProcessEvents()
{
	if (!m_queue.isEmpty())
	{
		sEvent event = m_queue.dequeue();
		m_fsm.ScheduleEvent(event);
	}
}

void Controller::Process()
{
	ProcessEvents();
	m_fsm.Update();
}