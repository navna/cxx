#pragma once

#include <cstddef>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

enum class RequestType : std::size_t {
	GetMessages,
	SendMessage
};

struct Protocol final {
	struct GetMessages final {
		static void sendRequest(std::ostream& stream, std::size_t index);
		static std::size_t recvRequest(std::istream& stream);

		static void sendResponse(std::ostream& stream, const std::vector<std::string>& data);
		static std::vector<std::string> recvResponse(std::istream& stream);
	};

	struct SendMessage {
		// TODO
	};

	static const std::size_t UNSIGNED_SIZE = 4;

	static std::size_t readUnsigned(std::istream& stream);
	static void writeUnsigned(std::ostream& stream, std::size_t value);

	static std::string readString(std::istream& stream);
	static void writeString(std::ostream& stream, const std::string& value);

	static bool canRecv(std::istream& stream);
};
