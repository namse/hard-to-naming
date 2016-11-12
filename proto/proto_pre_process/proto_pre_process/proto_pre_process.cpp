#include "stdafx.h"
#include "packet_parser_generator.h"


int main()
{
	std::ifstream in_stream("packet.preproto");
	std::ofstream out_stream("packet.proto");
	out_stream << "package packet;\n\n";

	std::vector<std::string> message_names;
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
			std::string upper_message_name = ToUppercaseUnderscore(message_name);

			message_names.push_back(message_name);
			uppercase_message_names.push_back(upper_message_name);

			out_stream << "message " << message_name << " {\n"
				<< "  required uint32 length = 1;\n"
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

	out_stream << "\n\n"
		<< "message PacketHeader {\n"
		<< "  required uint32 length = 1;\n"
		<< "  required PacketType type = 2;\n"
		<< "}\n\n"
		<< "enum PacketType {\n";
	int index = 1;
	for (auto& name : uppercase_message_names) {
		out_stream << "  " << name << " = " << index++ << ";\n";
	}
	out_stream << "}" << std::endl;

	PacketParserGenerator::Run(message_names);
    return 0;
}

