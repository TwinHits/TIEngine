#include "../pch.h"

TEST(Message, CreateMessage) {
	TIE::GlobalId sender = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::GlobalId reciever = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Message message = TIE::Message(sender, reciever);

	ASSERT_EQ(sender, message.getSenderId());
	ASSERT_EQ(reciever, message.getReceiverId());
}


TEST(Message, GetSenderId) {
	TIE::GlobalId sender = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::GlobalId reciever = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Message message = TIE::Message(sender, reciever);

	ASSERT_EQ(sender, message.getSenderId());
}

TEST(Message, SetSenderId) {
	TIE::GlobalId sender = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::GlobalId reciever = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Message message = TIE::Message(sender, reciever);

	TIE::GlobalId expected = TIE::HashManager::Instance()->getNewGlobalId();
	message.setSenderId(expected);
	TIE::GlobalId actual = message.getSenderId();

	ASSERT_EQ(expected, actual);
}


TEST(Message, GetReceiverId) {
	TIE::GlobalId sender = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::GlobalId reciever = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Message message = TIE::Message(sender, reciever);

	ASSERT_EQ(reciever, message.getReceiverId());
}


TEST(Message, SetReceiverId) {
	TIE::GlobalId sender = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::GlobalId receiver = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Message message = TIE::Message(sender, receiver);

	TIE::GlobalId expected = TIE::HashManager::Instance()->getNewGlobalId();
	message.setReceiverId(expected);
	TIE::GlobalId actual = message.getReceiverId();

	ASSERT_EQ(expected, actual);
}


TEST(Message, SetMessageType) {
	TIE::GlobalId sender = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::GlobalId receiver = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Message message = TIE::Message(sender, receiver);

	TIE::Message::MessageType expected = TIE::Message::MessageType::Move;
	message.setMessageType(expected);
	TIE::Message::MessageType actual = message.getMessageType();

	ASSERT_EQ(expected, actual);
}


TEST(Message, GetMessageType) {
	TIE::GlobalId sender = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::GlobalId receiver = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Message message = TIE::Message(sender, receiver);

	TIE::Message::MessageType expected = TIE::Message::MessageType::Move;
	message.setMessageType(expected);
	TIE::Message::MessageType actual = message.getMessageType();

	ASSERT_EQ(expected, actual);
}
