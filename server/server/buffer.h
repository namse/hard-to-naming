#pragma once


class Buffer
{
	static const unsigned int BUFFER_SIZE = 8096;
public:
	std::size_t ReadableLength() { return write_index_ - read_index_; }
	char * Begin() { return buffer_ + read_index_; }
	char * End() { return buffer_ + write_index_; }
	std::size_t WriteableLength() { return BUFFER_SIZE - write_index_; }

	void OnWritten(std::size_t bytes_written) { write_index_ += bytes_written; }
	bool Shift();
	void Consume(std::size_t bytes) { read_index_ += bytes;	};

private:
	char buffer_[BUFFER_SIZE];
	std::size_t read_index_ = 0;
	std::size_t write_index_ = 0;
};

