// #pragma once
// #include <string>
//
// class ConstString
// {
// 	const size_t hashCode = 0;
// 	const std::string dataStr;
//
// public:
// 	// ReSharper disable once CppNonExplicitConvertingConstructor
// 	ConstString(const std::string& dataStr) : hashCode(std::hash<std::string>{}(dataStr)), dataStr(dataStr){
// 	}
//
// 	ConstString(const ConstString& other) = default;
//
// 	ConstString(ConstString&& other) noexcept
// 		: hashCode(other.hashCode),
// 		  dataStr(other.dataStr){
// 	}
//
// 	ConstString& operator=(const ConstString& other) = delete;
//
// 	ConstString& operator=(ConstString&& other) = delete;
// };
//
