#include "MetadataSerializable.hpp"

namespace SharedCacheCore {

using namespace BinaryNinja;

struct DeserializationContext;

void Serialize(SerializationContext& context, std::string_view name, bool b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, bool& b) {
	b = context.doc[name.data()].GetBool();
}

void Serialize(SerializationContext& context, std::string_view name, uint8_t b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, uint8_t& b)
{
	b = static_cast<uint8_t>(context.doc[name.data()].GetUint64());
}

void Serialize(SerializationContext& context, std::string_view name, uint16_t b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, uint16_t& b)
{
	b = static_cast<uint16_t>(context.doc[name.data()].GetUint64());
}

void Serialize(SerializationContext& context, std::string_view name, uint32_t b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, uint32_t& b)
{
	b = static_cast<uint32_t>(context.doc[name.data()].GetUint64());
}

void Serialize(SerializationContext& context, std::string_view name, uint64_t b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, uint64_t& b)
{
	b = context.doc[name.data()].GetUint64();
}

void Serialize(SerializationContext& context, std::string_view name, int8_t b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, int8_t& b)
{
	b = context.doc[name.data()].GetInt64();
}

void Serialize(SerializationContext& context, std::string_view name, int16_t b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, int16_t& b)
{
	b = context.doc[name.data()].GetInt64();
}

void Serialize(SerializationContext& context, std::string_view name, int32_t b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, int32_t& b)
{
	b = context.doc[name.data()].GetInt();
}

void Serialize(SerializationContext& context, std::string_view name, int64_t b)
{
	rapidjson::Value key(name.data(), context.allocator);
	context.doc.AddMember(key, b, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, int64_t& b)
{
	b = context.doc[name.data()].GetInt64();
}

void Serialize(SerializationContext& context, std::string_view name, std::string_view b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value value(b.data(), context.allocator);
	context.doc.AddMember(key, value, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::string& b)
{
	b = context.doc[name.data()].GetString();
}

void Serialize(SerializationContext& context, std::string_view name, const std::map<uint64_t, std::string>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value p(rapidjson::kArrayType);
		p.PushBack(i.first, context.allocator);
		rapidjson::Value value(i.second.c_str(), context.allocator);
		p.PushBack(value, context.allocator);
		bArr.PushBack(p, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::map<uint64_t, std::string>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
		b[i.GetArray()[0].GetUint64()] = i.GetArray()[1].GetString();
}

void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<uint64_t, std::string>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value p(rapidjson::kArrayType);
		p.PushBack(i.first, context.allocator);
		rapidjson::Value value(i.second.c_str(), context.allocator);
		p.PushBack(value, context.allocator);
		bArr.PushBack(p, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<std::string, std::string>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value p(rapidjson::kArrayType);
		rapidjson::Value _key(i.first.c_str(), context.allocator);
		rapidjson::Value value(i.second.c_str(), context.allocator);
		p.PushBack(_key, context.allocator);
		p.PushBack(value, context.allocator);
		bArr.PushBack(p, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<uint64_t, std::string>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
		b[i.GetArray()[0].GetUint64()] = i.GetArray()[1].GetString();
}

void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<uint64_t, uint64_t>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value p(rapidjson::kArrayType);
		p.PushBack(i.first, context.allocator);
		p.PushBack(i.second, context.allocator);
		bArr.PushBack(p, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<uint64_t, uint64_t>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
		b[i.GetArray()[0].GetUint64()] = i.GetArray()[1].GetUint64();
}

// std::unordered_map<std::string, std::unordered_map<uint64_t, uint64_t>>
void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<std::string, std::unordered_map<uint64_t, uint64_t>>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value classes(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value classArr(rapidjson::kArrayType);
		rapidjson::Value classKey(i.first.c_str(), context.allocator);
		classArr.PushBack(classKey, context.allocator);
		rapidjson::Value membersArr(rapidjson::kArrayType);
		for (auto& j : i.second)
		{
			rapidjson::Value member(rapidjson::kArrayType);
			member.PushBack(j.first, context.allocator);
			member.PushBack(j.second, context.allocator);
			membersArr.PushBack(member, context.allocator);
		}
		classArr.PushBack(membersArr, context.allocator);
		classes.PushBack(classArr, context.allocator);
	}
	context.doc.AddMember(key, classes, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<std::string, std::unordered_map<uint64_t, uint64_t>>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
	{
		std::string key = i.GetArray()[0].GetString();
		std::unordered_map<uint64_t, uint64_t> memArray;
		for (auto& member : i.GetArray()[1].GetArray())
		{
			memArray[member.GetArray()[0].GetUint64()] = member.GetArray()[1].GetUint64();
		}
		b[key] = memArray;
	}
}

void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<std::string, std::string>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
		b[i.GetArray()[0].GetString()] = i.GetArray()[1].GetString();
}

void Serialize(SerializationContext& context, std::string_view name, const std::vector<std::string>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (const auto& s : b)
	{
		rapidjson::Value value(s.c_str(), context.allocator);
		bArr.PushBack(value, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::vector<std::string>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
		b.emplace_back(i.GetString());
}

void Serialize(SerializationContext& context, std::string_view name, const std::vector<std::pair<uint64_t, std::pair<uint64_t, uint64_t>>>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value segV(rapidjson::kArrayType);
		segV.PushBack(i.first, context.allocator);
		segV.PushBack(i.second.first, context.allocator);
		segV.PushBack(i.second.second, context.allocator);
		bArr.PushBack(segV, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::vector<std::pair<uint64_t, std::pair<uint64_t, uint64_t>>>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
	{
		std::pair<uint64_t, std::pair<uint64_t, uint64_t>> j;
		j.first = i.GetArray()[0].GetUint64();
		j.second.first = i.GetArray()[1].GetUint64();
		j.second.second = i.GetArray()[2].GetUint64();
		b.push_back(j);
	}
}

void Serialize(SerializationContext& context, std::string_view name, const std::vector<std::pair<uint64_t, bool>>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value segV(rapidjson::kArrayType);
		segV.PushBack(i.first, context.allocator);
		segV.PushBack(i.second, context.allocator);
		bArr.PushBack(segV, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::vector<std::pair<uint64_t, bool>>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
	{
		std::pair<uint64_t, bool> j;
		j.first = i.GetArray()[0].GetUint64();
		j.second = i.GetArray()[1].GetBool();
		b.push_back(j);
	}
}

void Serialize(SerializationContext& context, std::string_view name, const std::vector<uint64_t>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		bArr.PushBack(i, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::vector<uint64_t>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
	{
		b.push_back(i.GetUint64());
	}
}

// std::unordered_map<std::string, uint64_t>
void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<std::string, uint64_t>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value p(rapidjson::kArrayType);
		rapidjson::Value _key(i.first.c_str(), context.allocator);
		p.PushBack(_key, context.allocator);
		p.PushBack(i.second, context.allocator);
		bArr.PushBack(p, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<std::string, uint64_t>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
	{
		b[i.GetArray()[0].GetString()] = i.GetArray()[1].GetUint64();
	}
}

// std::vector<std::pair<uint64_t, std::vector<std::pair<uint64_t, std::string>>>>
void Serialize(SerializationContext& context, std::string_view name, const std::vector<std::pair<uint64_t, std::vector<std::pair<uint64_t, std::string>>>>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& i : b)
	{
		rapidjson::Value segV(rapidjson::kArrayType);
		segV.PushBack(i.first, context.allocator);
		rapidjson::Value segArr(rapidjson::kArrayType);
		for (auto& j : i.second)
		{
			rapidjson::Value segPair(rapidjson::kArrayType);
			segPair.PushBack(j.first, context.allocator);
			rapidjson::Value segStr(j.second.c_str(), context.allocator);
			segPair.PushBack(segStr, context.allocator);
			segArr.PushBack(segPair, context.allocator);
		}
		segV.PushBack(segArr, context.allocator);
		bArr.PushBack(segV, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::vector<std::pair<uint64_t, std::vector<std::pair<uint64_t, std::string>>>>& b)
{
	for (auto& i : context.doc[name.data()].GetArray())
	{
		std::pair<uint64_t, std::vector<std::pair<uint64_t, std::string>>> j;
		j.first = i.GetArray()[0].GetUint64();
		for (auto& k : i.GetArray()[1].GetArray())
		{
			j.second.push_back({k.GetArray()[0].GetUint64(), k.GetArray()[1].GetString()});
		}
		b.push_back(j);
	}
}

} // namespace SharedCacheCore
