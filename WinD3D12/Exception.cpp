#include "Exception.h"
#include <format>

Exception::Exception(unsigned int line, const char* file) noexcept
	:line(line), file(file)
{}

const char* Exception::GetType() const noexcept
{
	return "Veritas Exception";
}
int Exception::GetLine() const noexcept
{
	return line;
}
const std::string& Exception::GetFile() const noexcept
{
	return file;
}
std::string Exception::GetOriginString() const noexcept
{
	return std::format("[File]: {}\n[Line]: {}", file, line);
}
const char* Exception::what() const noexcept
{
	if (whatBuffer.empty())
	{
		whatBuffer = std::format("{}\n{}", GetType(), GetOriginString());
	}
	return whatBuffer.c_str();
}
