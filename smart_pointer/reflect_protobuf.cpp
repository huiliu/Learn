#include "reflect_protobuf.h"
#include "addressbook.pb.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <string>
#include <cassert>

using namespace google::protobuf;

Message* CreateMessage(const std::string& name)
{
	Message* message = nullptr;
	const Descriptor* pDescriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(name);
	if (nullptr != pDescriptor)
	{
		const Message* pMsg = MessageFactory::generated_factory()->GetPrototype(pDescriptor);
		if (nullptr != pMsg)
		{
			message = pMsg->New();
		}
	}
	return message;
}

void test_reflect_example()
{
	Message* pMsg = CreateMessage("tutorial.Person");
	assert(nullptr != pMsg);

	assert(typeid(*pMsg) == typeid(tutorial::Person::default_instance()));
}