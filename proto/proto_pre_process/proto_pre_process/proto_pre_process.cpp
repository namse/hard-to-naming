// proto_pre_process.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

std::string ToUppercase(std::string target) {
	std::string ret;
	for (auto i = 0; i < target.length(); i++) {
		auto current_char = target[i];
		ret.push_back(std::toupper(current_char));

		if (i + 1 < target.length()) {
			auto next_char = target[i + 1];
			if ('A' <= next_char && next_char <= 'Z') {
				ret.push_back('_');
			}
		}
	}
	return ret;
}

int main()
{
	std::ifstream in_stream("packet.preproto");
	std::ofstream out_stream("packet.proto");
	std::vector<std::string> uppercase_message_names;
	while (!in_stream.eof()) {
		std::string first_line;
		std::getline(in_stream, first_line);

		std::stringstream sstream(first_line);

		std::string type;
		sstream >> type;

		if (type == "packet") {
			std::string message_name;
			sstream >> message_name;
			std::string upper_message_name = ToUppercase(message_name);
			uppercase_message_names.push_back(upper_message_name);

			out_stream << "message " << message_name << " {\n"
				<< "  required int32 length = 1;\n"
				<< "  required PacketType type = 2 [default = " << upper_message_name << "];\n\n";
			
			int index = 3;
			for (std::string line; std::getline(in_stream, line);) {
				if (line[0] == '}') {
					break;
				}
				out_stream << line << " = " << index++ << ";\n";
			}

			out_stream << "}\n\n";
		}
		else if(!first_line.empty()) {
			for (std::string line; std::getline(in_stream, line);) {
				if (line[0] == '}') {
					out_stream << line << "\n";
					break;
				}
				out_stream << line << "\n";
			}
		}
		else {
			out_stream << "\n";
		}
	}

	out_stream << "\nenum PacketType {\n";
	int index = 1;
	for (auto& name : uppercase_message_names) {
		out_stream << "  " << name << " = " << index++ << ";\n";
	}
	out_stream << "}" << std::endl;
    return 0;
}

