#include "protocol.h"
#include <stdexcept>

using namespace std;

// =====================
// Protocol::GetMessages
// =====================

using GetMessages = Protocol::GetMessages;

void GetMessages::sendRequest(ostream& stream, size_t index) {
	writeUnsigned(stream, 2 * UNSIGNED_SIZE);
	writeUnsigned(stream, (size_t)RequestType::GetMessages);
	writeUnsigned(stream, index);
}

size_t GetMessages::recvRequest(istream& stream) {
	return readUnsigned(stream);
}

void GetMessages::sendResponse(ostream& stream, const vector<string>& data) {
	size_t size = 0;
	for (const auto& item : data) {
		size += item.size() + 1;
	}
	writeUnsigned(stream, UNSIGNED_SIZE + size);
	writeUnsigned(stream, (size_t)RequestType::GetMessages);
	for (const auto& item : data) {
		writeString(stream, item);
	}
}

vector<string> GetMessages::recvResponse(istream& stream) {
	vector<string> data;
	while (true) {
		const auto s = readString(stream);
		if (stream.good()) {
			data.push_back(s);
		}
		else {
			return data;
		}
	}
}

// =====================
// Protocol::SendMessage
// =====================

// TODO

// ========
// Protocol
// ========

size_t Protocol::readUnsigned(istream& stream) {
	const auto b3 = (unsigned char)stream.get();
	const auto b2 = (unsigned char)stream.get();
	const auto b1 = (unsigned char)stream.get();
	const auto b0 = (unsigned char)stream.get();
	return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}

void Protocol::writeUnsigned(ostream& stream, size_t value) {
	stream.put((char)((value & 0xFF000000) >> 24));
	stream.put((char)((value & 0xFF0000) >> 16));
	stream.put((char)((value & 0xFF00) >> 8));
	stream.put((char)(value & 0xFF));
}

string Protocol::readString(istream& stream) {
	string value;
	while (true) {
		const auto b = stream.get();
		if (b == EOF)
			return string();
		else if (b == '\0')
			return value;
		else
			value += b;
	}
}

void Protocol::writeString(std::ostream& stream, const string& value) {
	// Обращение к value[value.size()] гарантированно корректно только в C++11 и выше
	stream.write(value.data(), value.size() + 1);
}

bool Protocol::canRecv(istream& stream) {
	const auto begin = stream.tellg();
	stream.seekg(0, ios::end);
	const auto end = stream.tellg();
	const auto available = (size_t)(end - begin);

	stream.seekg(begin);
	if (available < UNSIGNED_SIZE) {
		return false;
	}

	const auto messageSize = Protocol::readUnsigned(stream);
	stream.seekg(begin);

	return available >= UNSIGNED_SIZE + messageSize;
}
