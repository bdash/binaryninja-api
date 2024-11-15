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

void Serialize(SerializationContext& context, std::string_view name, const mach_header_64& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	bArr.PushBack(b.magic, context.allocator);
	bArr.PushBack(b.cputype, context.allocator);
	bArr.PushBack(b.cpusubtype, context.allocator);
	bArr.PushBack(b.filetype, context.allocator);
	bArr.PushBack(b.ncmds, context.allocator);
	bArr.PushBack(b.sizeofcmds, context.allocator);
	bArr.PushBack(b.flags, context.allocator);
	bArr.PushBack(b.reserved, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, mach_header_64& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	b.magic = bArr[0].GetUint();
	b.cputype = bArr[1].GetUint();
	b.cpusubtype = bArr[2].GetUint();
	b.filetype = bArr[3].GetUint();
	b.ncmds = bArr[4].GetUint();
	b.sizeofcmds = bArr[5].GetUint();
	b.flags = bArr[6].GetUint();
	b.reserved = bArr[7].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const symtab_command& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	bArr.PushBack(b.cmd, context.allocator);
	bArr.PushBack(b.cmdsize, context.allocator);
	bArr.PushBack(b.symoff, context.allocator);
	bArr.PushBack(b.nsyms, context.allocator);
	bArr.PushBack(b.stroff, context.allocator);
	bArr.PushBack(b.strsize, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, symtab_command& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	b.cmd = bArr[0].GetUint();
	b.cmdsize = bArr[1].GetUint();
	b.symoff = bArr[2].GetUint();
	b.nsyms = bArr[3].GetUint();
	b.stroff = bArr[4].GetUint();
	b.strsize = bArr[5].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const dysymtab_command& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	bArr.PushBack(b.cmd, context.allocator);
	bArr.PushBack(b.cmdsize, context.allocator);
	bArr.PushBack(b.ilocalsym, context.allocator);
	bArr.PushBack(b.nlocalsym, context.allocator);
	bArr.PushBack(b.iextdefsym, context.allocator);
	bArr.PushBack(b.nextdefsym, context.allocator);
	bArr.PushBack(b.iundefsym, context.allocator);
	bArr.PushBack(b.nundefsym, context.allocator);
	bArr.PushBack(b.tocoff, context.allocator);
	bArr.PushBack(b.ntoc, context.allocator);
	bArr.PushBack(b.modtaboff, context.allocator);
	bArr.PushBack(b.nmodtab, context.allocator);
	bArr.PushBack(b.extrefsymoff, context.allocator);
	bArr.PushBack(b.nextrefsyms, context.allocator);
	bArr.PushBack(b.indirectsymoff, context.allocator);
	bArr.PushBack(b.nindirectsyms, context.allocator);
	bArr.PushBack(b.extreloff, context.allocator);
	bArr.PushBack(b.nextrel, context.allocator);
	bArr.PushBack(b.locreloff, context.allocator);
	bArr.PushBack(b.nlocrel, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, dysymtab_command& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	b.cmd = bArr[0].GetUint();
	b.cmdsize = bArr[1].GetUint();
	b.ilocalsym = bArr[2].GetUint();
	b.nlocalsym = bArr[3].GetUint();
	b.iextdefsym = bArr[4].GetUint();
	b.nextdefsym = bArr[5].GetUint();
	b.iundefsym = bArr[6].GetUint();
	b.nundefsym = bArr[7].GetUint();
	b.tocoff = bArr[8].GetUint();
	b.ntoc = bArr[9].GetUint();
	b.modtaboff = bArr[10].GetUint();
	b.nmodtab = bArr[11].GetUint();
	b.extrefsymoff = bArr[12].GetUint();
	b.nextrefsyms = bArr[13].GetUint();
	b.indirectsymoff = bArr[14].GetUint();
	b.nindirectsyms = bArr[15].GetUint();
	b.extreloff = bArr[16].GetUint();
	b.nextrel = bArr[17].GetUint();
	b.locreloff = bArr[18].GetUint();
	b.nlocrel = bArr[19].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const dyld_info_command& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	bArr.PushBack(b.cmd, context.allocator);
	bArr.PushBack(b.cmdsize, context.allocator);
	bArr.PushBack(b.rebase_off, context.allocator);
	bArr.PushBack(b.rebase_size, context.allocator);
	bArr.PushBack(b.bind_off, context.allocator);
	bArr.PushBack(b.bind_size, context.allocator);
	bArr.PushBack(b.weak_bind_off, context.allocator);
	bArr.PushBack(b.weak_bind_size, context.allocator);
	bArr.PushBack(b.lazy_bind_off, context.allocator);
	bArr.PushBack(b.lazy_bind_size, context.allocator);
	bArr.PushBack(b.export_off, context.allocator);
	bArr.PushBack(b.export_size, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, dyld_info_command& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	b.cmd = bArr[0].GetUint();
	b.cmdsize = bArr[1].GetUint();
	b.rebase_off = bArr[2].GetUint();
	b.rebase_size = bArr[3].GetUint();
	b.bind_off = bArr[4].GetUint();
	b.bind_size = bArr[5].GetUint();
	b.weak_bind_off = bArr[6].GetUint();
	b.weak_bind_size = bArr[7].GetUint();
	b.lazy_bind_off = bArr[8].GetUint();
	b.lazy_bind_size = bArr[9].GetUint();
	b.export_off = bArr[10].GetUint();
	b.export_size = bArr[11].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const routines_command_64& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	bArr.PushBack(b.cmd, context.allocator);
	bArr.PushBack(b.cmdsize, context.allocator);
	bArr.PushBack(b.init_address, context.allocator);
	bArr.PushBack(b.init_module, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, routines_command_64& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	b.cmd = bArr[0].GetUint();
	b.cmdsize = bArr[1].GetUint();
	b.init_address = bArr[2].GetUint();
	b.init_module = bArr[3].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const function_starts_command& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	bArr.PushBack(b.cmd, context.allocator);
	bArr.PushBack(b.cmdsize, context.allocator);
	bArr.PushBack(b.funcoff, context.allocator);
	bArr.PushBack(b.funcsize, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, function_starts_command& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	b.cmd = bArr[0].GetUint();
	b.cmdsize = bArr[1].GetUint();
	b.funcoff = bArr[2].GetUint();
	b.funcsize = bArr[3].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const std::vector<section_64>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& s : b)
	{
		rapidjson::Value sArr(rapidjson::kArrayType);
		std::string sectNameStr;
		char sectName[16];
		memcpy(sectName, s.sectname, 16);
		sectName[15] = 0;
		sectNameStr = std::string(sectName);
		sArr.PushBack(
			rapidjson::Value(sectNameStr.c_str(), context.allocator), context.allocator);
		std::string segNameStr;
		char segName[16];
		memcpy(segName, s.segname, 16);
		segName[15] = 0;
		segNameStr = std::string(segName);
		sArr.PushBack(
			rapidjson::Value(segNameStr.c_str(), context.allocator), context.allocator);
		sArr.PushBack(s.addr, context.allocator);
		sArr.PushBack(s.size, context.allocator);
		sArr.PushBack(s.offset, context.allocator);
		sArr.PushBack(s.align, context.allocator);
		sArr.PushBack(s.reloff, context.allocator);
		sArr.PushBack(s.nreloc, context.allocator);
		sArr.PushBack(s.flags, context.allocator);
		sArr.PushBack(s.reserved1, context.allocator);
		sArr.PushBack(s.reserved2, context.allocator);
		sArr.PushBack(s.reserved3, context.allocator);
		bArr.PushBack(sArr, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::vector<section_64>& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	for (auto& s : bArr)
	{
		section_64 sec;
		auto s2 = s.GetArray();
		std::string sectNameStr = s2[0].GetString();
		memset(sec.sectname, 0, 16);
		memcpy(sec.sectname, sectNameStr.c_str(), sectNameStr.size());
		std::string segNameStr = s2[1].GetString();
		memset(sec.segname, 0, 16);
		memcpy(sec.segname, segNameStr.c_str(), segNameStr.size());
		sec.addr = s2[2].GetUint64();
		sec.size = s2[3].GetUint64();
		sec.offset = s2[4].GetUint();
		sec.align = s2[5].GetUint();
		sec.reloff = s2[6].GetUint();
		sec.nreloc = s2[7].GetUint();
		sec.flags = s2[8].GetUint();
		sec.reserved1 = s2[9].GetUint();
		sec.reserved2 = s2[10].GetUint();
		sec.reserved3 = s2[11].GetUint();
		b.push_back(sec);
	}
}

void Serialize(SerializationContext& context, std::string_view name, const linkedit_data_command& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	bArr.PushBack(b.cmd, context.allocator);
	bArr.PushBack(b.cmdsize, context.allocator);
	bArr.PushBack(b.dataoff, context.allocator);
	bArr.PushBack(b.datasize, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, linkedit_data_command& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	b.cmd = bArr[0].GetUint();
	b.cmdsize = bArr[1].GetUint();
	b.dataoff = bArr[2].GetUint();
	b.datasize = bArr[3].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const segment_command_64& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	std::string segNameStr;
	char segName[16];
	memcpy(segName, b.segname, 16);
	segName[15] = 0;
	segNameStr = std::string(segName);
	bArr.PushBack(rapidjson::Value(segNameStr.c_str(), context.allocator), context.allocator);
	bArr.PushBack(b.vmaddr, context.allocator);
	bArr.PushBack(b.vmsize, context.allocator);
	bArr.PushBack(b.fileoff, context.allocator);
	bArr.PushBack(b.filesize, context.allocator);
	bArr.PushBack(b.maxprot, context.allocator);
	bArr.PushBack(b.initprot, context.allocator);
	bArr.PushBack(b.nsects, context.allocator);
	bArr.PushBack(b.flags, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, segment_command_64& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	std::string segNameStr = bArr[0].GetString();
	memset(b.segname, 0, 16);
	memcpy(b.segname, segNameStr.c_str(), segNameStr.size());
	b.vmaddr = bArr[1].GetUint64();
	b.vmsize = bArr[2].GetUint64();
	b.fileoff = bArr[3].GetUint64();
	b.filesize = bArr[4].GetUint64();
	b.maxprot = bArr[5].GetUint();
	b.initprot = bArr[6].GetUint();
	b.nsects = bArr[7].GetUint();
	b.flags = bArr[8].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const std::vector<segment_command_64>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& s : b)
	{
		rapidjson::Value sArr(rapidjson::kArrayType);
		std::string segNameStr;
		char segName[16];
		memcpy(segName, s.segname, 16);
		segName[15] = 0;
		segNameStr = std::string(segName);
		sArr.PushBack(
			rapidjson::Value(segNameStr.c_str(), context.allocator), context.allocator);
		sArr.PushBack(s.vmaddr, context.allocator);
		sArr.PushBack(s.vmsize, context.allocator);
		sArr.PushBack(s.fileoff, context.allocator);
		sArr.PushBack(s.filesize, context.allocator);
		sArr.PushBack(s.maxprot, context.allocator);
		sArr.PushBack(s.initprot, context.allocator);
		sArr.PushBack(s.nsects, context.allocator);
		sArr.PushBack(s.flags, context.allocator);
		bArr.PushBack(sArr, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::vector<segment_command_64>& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	for (auto& s : bArr)
	{
		segment_command_64 sec;
		auto s2 = s.GetArray();
		std::string segNameStr = s2[0].GetString();
		memset(sec.segname, 0, 16);
		memcpy(sec.segname, segNameStr.c_str(), segNameStr.size());
		sec.vmaddr = s2[1].GetUint64();
		sec.vmsize = s2[2].GetUint64();
		sec.fileoff = s2[3].GetUint64();
		sec.filesize = s2[4].GetUint64();
		sec.maxprot = s2[5].GetUint();
		sec.initprot = s2[6].GetUint();
		sec.nsects = s2[7].GetUint();
		sec.flags = s2[8].GetUint();
		b.push_back(sec);
	}
}

void Serialize(SerializationContext& context, std::string_view name, const build_version_command& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	bArr.PushBack(b.cmd, context.allocator);
	bArr.PushBack(b.cmdsize, context.allocator);
	bArr.PushBack(b.platform, context.allocator);
	bArr.PushBack(b.minos, context.allocator);
	bArr.PushBack(b.sdk, context.allocator);
	bArr.PushBack(b.ntools, context.allocator);
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, build_version_command& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	b.cmd = bArr[0].GetUint();
	b.cmdsize = bArr[1].GetUint();
	b.platform = bArr[2].GetUint();
	b.minos = bArr[3].GetUint();
	b.sdk = bArr[4].GetUint();
	b.ntools = bArr[5].GetUint();
}

void Serialize(SerializationContext& context, std::string_view name, const std::vector<build_tool_version>& b)
{
	rapidjson::Value key(name.data(), context.allocator);
	rapidjson::Value bArr(rapidjson::kArrayType);
	for (auto& s : b)
	{
		rapidjson::Value sArr(rapidjson::kArrayType);
		sArr.PushBack(s.tool, context.allocator);
		sArr.PushBack(s.version, context.allocator);
		bArr.PushBack(sArr, context.allocator);
	}
	context.doc.AddMember(key, bArr, context.allocator);
}

void Deserialize(DeserializationContext& context, std::string_view name, std::vector<build_tool_version>& b)
{
	auto bArr = context.doc[name.data()].GetArray();
	for (auto& s : bArr)
	{
		build_tool_version sec;
		auto s2 = s.GetArray();
		sec.tool = s2[0].GetUint();
		sec.version = s2[1].GetUint();
		b.push_back(sec);
	}
}


} // namespace SharedCacheCore
