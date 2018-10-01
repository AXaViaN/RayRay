#ifndef UTILITY__FILE
#define UTILITY__FILE

#include <string>

namespace Utility {

class File
{
public:
	enum class Type
	{
		Binary,
		Text
	};

public:
	File(const std::string& path, Type type=Type::Binary, bool create=true, bool isLogDisabled=false);

	void Write(const std::string& data);
	void WriteLine(const std::string& data);
	void Flush();

	std::string Read(size_t size);
	std::string ReadLine();
	std::string ReadUntil(char seperator);

	template<typename T> inline void WriteBinaryNumber(const T& value);
	template<typename T> inline T ReadBinaryNumber();

	void MoveHead(int delta);
	void MoveHeadToFront();
	void MoveHeadToEnd();

	void Delete();
	void DeleteContents();

	inline bool IsValid() const;
	inline bool IsEOF() const;

public:
	~File() noexcept;
	File(File&& other) noexcept;
	File& operator=(File&& other) noexcept;
	File(const File& other) = delete;
	File& operator=(const File& other) = delete;

private:
	void WriteBinaryNumber(const void* value, size_t size);
	void ReadBinaryNumber(void* value, size_t size);

private:
	void* m_Handle = nullptr;
	std::string m_Path;
	Type m_FileType;
	bool m_IsEOF = true;

};

/***** IMPLEMENTATION *****/

template<typename T> inline void File::WriteBinaryNumber(const T& value)
{
	WriteBinaryNumber(&value, sizeof(T));
}
template<typename T> inline T File::ReadBinaryNumber()
{
	T value = static_cast<T>(-1);
	ReadBinaryNumber(&value, sizeof(T));
	return value;
}

inline bool File::IsValid() const
{
	return (m_Handle != nullptr);
}
inline bool File::IsEOF() const
{
	return m_IsEOF;
}

} // namespace Utility

#endif // UTILITY__FILE
