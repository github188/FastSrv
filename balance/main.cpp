#include "protocol/protocol_inside.pb.h"
#include "protocol/protocol.h"
#include "event2/event.h"

int main()
{
	event_base* pEvbase = event_base_new();
	event_base_free(pEvbase);

	return 0;
}
