//
// Created by kat on 5/31/23.
//

/*
 * Welcome to, this file.
 *
 * This is a metadata serialization helper.
 *
 * Have you ever wished turning a complex datastructure into a Metadata object was as easy in C++ as it is in python?
 * Do you like macros and templates?
 *
 * Great news.
 *
 * Implement these on your `public MetadataSerializable<T>` subclass:
 * ```
    class MyClass : public MetadataSerializable<MyClass> {
		void Store(SerializationContext& context) const {
			MSS(m_someVariable);
			MSS(m_someOtherVariable);
		}
		void Load(DeserializationContext& context) {
			MSL(m_someVariable);
			MSL(m_someOtherVariable);
		}
	}
 ```
 * Then, you can turn your object into a Metadata object with `AsMetadata()`, and load it back with
 `LoadFromMetadata()`.
 *
 * Serialized fields will be automatically repopulated.
 *
 * Other ser/deser formats (rapidjson objects, strings) also exist. You can use these to achieve nesting, but probably
 avoid that.
 * */

#include "binaryninjaapi.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "../api/sharedcachecore.h"
#include "view/macho/machoview.h"

#ifndef SHAREDCACHE_CORE_METADATASERIALIZABLE_HPP
#define SHAREDCACHE_CORE_METADATASERIALIZABLE_HPP

namespace SharedCacheCore {

#define MSS(name)						 context.store(#name, name)
#define MSS_CAST(name, type)			 context.store(#name, (type) name)
#define MSS_SUBCLASS(name)		 		 Serialize(context, #name, name)
#define MSL(name)						 name = context.load<decltype(name)>(#name)
#define MSL_CAST(name, storedType, type) name = (type)context.load<storedType>(#name)
#define MSL_SUBCLASS(name)				 Deserialize(context, #name, name)

using namespace BinaryNinja;

struct DeserializationContext;

struct SerializationContext {
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType allocator;

	SerializationContext() {
		doc.SetObject();
		allocator = doc.GetAllocator();
	}

	template <typename T>
	void store(std::string_view x, const T& y)
	{
		Serialize(*this, x, y);
	}
};

struct DeserializationContext {
	rapidjson::Document doc;

	template <typename T>
	T load(std::string_view x)
	{
		T value;
		Deserialize(*this, x, value);
		return value;
	}
};

template <typename Derived>
class MetadataSerializable
{
public:
	std::string AsString() const
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(strbuf);
		AsDocument().Accept(writer);

		return strbuf.GetString();
	}

	rapidjson::Document AsDocument() const {
		SerializationContext context;
		AsDerived().Store(context);
		return std::move(context.doc);
	}

	void LoadFromString(const std::string& s)
	{
		DeserializationContext context;
		context.doc.Parse(s.c_str());
		AsDerived().Load(context);
	}

	void LoadFromValue(rapidjson::Value& s)
	{
		DeserializationContext context;
		context.doc.CopyFrom(s, context.doc.GetAllocator());
		AsDerived().Load(context);
	}

	Ref<Metadata> AsMetadata() { return new Metadata(AsString()); }

	bool LoadFromMetadata(const Ref<Metadata>& meta)
	{
		if (!meta->IsString())
			return false;
		LoadFromString(meta->GetString());
		return true;
	}

private:
	const Derived& AsDerived() const { return static_cast<const Derived&>(*this); }
	Derived& AsDerived() { return static_cast<Derived&>(*this); }
};

// These are not part of the FFI API, but are exported so that sharedcacheui can use them.
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, bool b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, bool& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, uint8_t b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, uint8_t& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, uint16_t b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, uint16_t& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, uint32_t b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, uint32_t& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, uint64_t b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, uint64_t& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, int8_t b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, int8_t& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, int16_t b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, int16_t& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, int32_t b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, int32_t& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, int64_t b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, int64_t& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, std::string_view b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::string& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::map<uint64_t, std::string>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::map<uint64_t, std::string>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<uint64_t, std::string>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<std::string, std::string>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<uint64_t, std::string>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<uint64_t, uint64_t>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<uint64_t, uint64_t>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<std::string, std::unordered_map<uint64_t, uint64_t>>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<std::string, std::unordered_map<uint64_t, uint64_t>>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<std::string, std::string>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::vector<std::string>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::vector<std::string>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::vector<std::pair<uint64_t, std::pair<uint64_t, uint64_t>>>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::vector<std::pair<uint64_t, std::pair<uint64_t, uint64_t>>>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::vector<std::pair<uint64_t, bool>>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::vector<std::pair<uint64_t, bool>>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::vector<uint64_t>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::vector<uint64_t>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::unordered_map<std::string, uint64_t>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::unordered_map<std::string, uint64_t>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext& context, std::string_view name, const std::vector<std::pair<uint64_t, std::vector<std::pair<uint64_t, std::string>>>>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext& context, std::string_view name, std::vector<std::pair<uint64_t, std::vector<std::pair<uint64_t, std::string>>>>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const mach_header_64& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, mach_header_64& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const symtab_command& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, symtab_command& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const dysymtab_command& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, dysymtab_command& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const dyld_info_command& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, dyld_info_command& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const routines_command_64& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, routines_command_64& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const function_starts_command& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, function_starts_command& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const std::vector<section_64>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, std::vector<section_64>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const linkedit_data_command& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, linkedit_data_command& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const segment_command_64& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, segment_command_64& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const std::vector<segment_command_64>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, std::vector<segment_command_64>& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const build_version_command& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, build_version_command& b);
SHAREDCACHE_FFI_API void Serialize(SerializationContext&, std::string_view name, const std::vector<build_tool_version>& b);
SHAREDCACHE_FFI_API void Deserialize(DeserializationContext&, std::string_view name, std::vector<build_tool_version>& b);


} // namespace SharedCacheCore

#endif	// SHAREDCACHE_METADATASERIALIZABLE_HPP
