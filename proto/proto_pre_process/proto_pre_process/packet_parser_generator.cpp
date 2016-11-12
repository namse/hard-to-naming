#include "stdafx.h"
#include "packet_parser_generator.h"

void PacketParserGenerator::Run(std::vector<std::string>& message_names)
{
	{
		std::ofstream out_stream("packet_parser.cpp");

		out_stream << "#include \"stdafx.h\"\n"
			<< "#include \"packet_parser.h\"\n"
			<< "\n"
			<< "void PacketParser::ParseTypeAndCallPacketHandler(\n"
			<< "\t\tgoogle::protobuf::int32 type,\n"
			<< "\t\tconst char* buffer,\n"
			<< "\t\tstd::size_t length) {\n"
			<< "\tswitch (type) {\n";
		for (auto& name : message_names) {
			out_stream << "\tcase packet::PacketType::" << ToUppercaseUnderscore(name) << ":\n"
				<< "\t\treturn CallPacketHandler<packet::" << name << ">(buffer, length);\n";
		}
		out_stream << "\tdefault:\n"
			<< "\t\tthrow std::exception(\"wrong packet type\");\n"
			<< "\t}\n"
			<< "}" << std::endl;
	}
	for (auto& name : message_names) {
		std::ofstream out_stream("packet_handler_" + ToLowercaseUnderscore(name) + ".generated.cpp");

		out_stream << "#include \"stdafx.h\"\n"
			<< "#include \"packet_parser.h\"\n"
			<< "\n"
			<< "template <>\n"
			<< "static void PacketParser::PacketHandler<packet::" << name << ">(packet::" << name << "& packet) {\n"
			<< "\n"
			<< "}" << std::endl;
	}
}
