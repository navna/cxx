#include "protocol.h"

#include <algorithm>
#include <stdexcept>

using namespace std;

// ========
// Protocol
// ========

void Protocol::writeUnsigned(Buffer& buffer, size_t value) {
	const auto b3 = (value & 0xFF000000) >> 24;
	const auto b2 = (value & 0xFF0000) >> 16;
	const auto b1 = (value & 0xFF00) >> 8;
	const auto b0 = (value & 0xFF);
	buffer.push_back((Byte)b3);
	buffer.push_back((Byte)b2);
	buffer.push_back((Byte)b1);
	buffer.push_back((Byte)b0);
}

size_t Protocol::readUnsigned(Buffer& buffer, bool extractBytes) {
	if (buffer.size() < 4) {
		throw runtime_error("Not enough bytes to read unsigned.");
	}
	const auto b3 = buffer[0];
	const auto b2 = buffer[1];
	const auto b1 = buffer[2];
	const auto b0 = buffer[3];
	if (extractBytes) {
		buffer.pop_front();
		buffer.pop_front();
		buffer.pop_front();
		buffer.pop_front();
	}
	return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}

void Protocol::writeData(Buffer& buffer, const string& data) {
	writeUnsigned(buffer, data.size());
	buffer.insert(buffer.end(), data.begin(), data.end());
}

string Protocol::readData(Buffer& buffer) {
	const auto size = readUnsigned(buffer);
	if (buffer.size() < size) {
		throw runtime_error("Not enough bytes to read data.");
	}

	string data;
	for (size_t i = 0; i < size; ++i) {
		const auto c = buffer.front();
		buffer.pop_front();
		data += c;
	}
	return data;
}

bool Protocol::canParse(Buffer& buffer) {
	const auto available = buffer.size();
	if (available < UNSIGNED_SIZE) {
		return false;
	}
	const auto payloadSize = Protocol::readUnsigned(buffer, false);
	return available >= UNSIGNED_SIZE + payloadSize;
}

// =====================
// Protocol::GetMessages
// =====================

using GetMessages = Protocol::GetMessages;

Protocol::Buffer GetMessages::makeRequest(size_t fromIndex) {
	Buffer buffer;
	writeUnsigned(buffer, 2 * UNSIGNED_SIZE);
	writeUnsigned(buffer, (size_t)QueryType::GetMessages);
	writeUnsigned(buffer, fromIndex);
	return buffer;
}

size_t GetMessages::parseRequest(Buffer& buffer) {
	return readUnsigned(buffer);
}

Protocol::Buffer GetMessages::makeResponse(const vector<string>& messages) {
	Buffer buffer;
	writeUnsigned(buffer, (size_t)QueryType::GetMessages);
	writeUnsigned(buffer, messages.size());
	for (const auto& message : messages) {
		writeData(buffer, message);
	}

	Buffer payloadSizeBuffer;
	const auto payloadSize = buffer.size();
	writeUnsigned(payloadSizeBuffer, payloadSize);
	buffer.insert(buffer.begin(), payloadSizeBuffer.begin(), payloadSizeBuffer.end());

	return buffer;
}

vector<string> GetMessages::parseResponse(Buffer& buffer) {
	const auto messageCount = readUnsigned(buffer);

	vector<string> messages;
	messages.reserve(messageCount);
	for (size_t i = 0; i < messageCount; ++i) {
		const auto message = readData(buffer);
		messages.push_back(message);
	}

	return messages;
}

// =====================
// Protocol::SendMessage
// =====================

// TODO [Protocol] Написать определения методов для отправки сообщения
