// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Lap.proto

#include "Lap.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR Lap::Lap(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.telemetry_)*/{}
  , /*decltype(_impl_.lap_time_)*/0u
  , /*decltype(_impl_.sector_1_)*/0u
  , /*decltype(_impl_.sector_2_)*/0u
  , /*decltype(_impl_.sector_3_)*/0u
  , /*decltype(_impl_.valid_lap_)*/false
  , /*decltype(_impl_.valid_sector_1_)*/false
  , /*decltype(_impl_.valid_sector_2_)*/false
  , /*decltype(_impl_.valid_sector_3_)*/false
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct LapDefaultTypeInternal {
  PROTOBUF_CONSTEXPR LapDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~LapDefaultTypeInternal() {}
  union {
    Lap _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 LapDefaultTypeInternal _Lap_default_instance_;
static ::_pb::Metadata file_level_metadata_Lap_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_Lap_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Lap_2eproto = nullptr;

const uint32_t TableStruct_Lap_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Lap, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.lap_time_),
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.sector_1_),
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.sector_2_),
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.sector_3_),
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.valid_lap_),
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.valid_sector_1_),
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.valid_sector_2_),
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.valid_sector_3_),
  PROTOBUF_FIELD_OFFSET(::Lap, _impl_.telemetry_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Lap)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_Lap_default_instance_._instance,
};

const char descriptor_table_protodef_Lap_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\tLap.proto\032\017Telemetry.proto\"\307\001\n\003Lap\022\020\n\010"
  "lap_time\030\001 \001(\r\022\020\n\010sector_1\030\002 \001(\r\022\020\n\010sect"
  "or_2\030\003 \001(\r\022\020\n\010sector_3\030\004 \001(\r\022\021\n\tvalid_la"
  "p\030\005 \001(\010\022\026\n\016valid_sector_1\030\006 \001(\010\022\026\n\016valid"
  "_sector_2\030\007 \001(\010\022\026\n\016valid_sector_3\030\010 \001(\010\022"
  "\035\n\ttelemetry\030\t \003(\0132\n.Telemetryb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_Lap_2eproto_deps[1] = {
  &::descriptor_table_Telemetry_2eproto,
};
static ::_pbi::once_flag descriptor_table_Lap_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Lap_2eproto = {
    false, false, 238, descriptor_table_protodef_Lap_2eproto,
    "Lap.proto",
    &descriptor_table_Lap_2eproto_once, descriptor_table_Lap_2eproto_deps, 1, 1,
    schemas, file_default_instances, TableStruct_Lap_2eproto::offsets,
    file_level_metadata_Lap_2eproto, file_level_enum_descriptors_Lap_2eproto,
    file_level_service_descriptors_Lap_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Lap_2eproto_getter() {
  return &descriptor_table_Lap_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Lap_2eproto(&descriptor_table_Lap_2eproto);

// ===================================================================

class Lap::_Internal {
 public:
};

void Lap::clear_telemetry() {
  _impl_.telemetry_.Clear();
}
Lap::Lap(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Lap)
}
Lap::Lap(const Lap& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Lap* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.telemetry_){from._impl_.telemetry_}
    , decltype(_impl_.lap_time_){}
    , decltype(_impl_.sector_1_){}
    , decltype(_impl_.sector_2_){}
    , decltype(_impl_.sector_3_){}
    , decltype(_impl_.valid_lap_){}
    , decltype(_impl_.valid_sector_1_){}
    , decltype(_impl_.valid_sector_2_){}
    , decltype(_impl_.valid_sector_3_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.lap_time_, &from._impl_.lap_time_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.valid_sector_3_) -
    reinterpret_cast<char*>(&_impl_.lap_time_)) + sizeof(_impl_.valid_sector_3_));
  // @@protoc_insertion_point(copy_constructor:Lap)
}

inline void Lap::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.telemetry_){arena}
    , decltype(_impl_.lap_time_){0u}
    , decltype(_impl_.sector_1_){0u}
    , decltype(_impl_.sector_2_){0u}
    , decltype(_impl_.sector_3_){0u}
    , decltype(_impl_.valid_lap_){false}
    , decltype(_impl_.valid_sector_1_){false}
    , decltype(_impl_.valid_sector_2_){false}
    , decltype(_impl_.valid_sector_3_){false}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

Lap::~Lap() {
  // @@protoc_insertion_point(destructor:Lap)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Lap::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.telemetry_.~RepeatedPtrField();
}

void Lap::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Lap::Clear() {
// @@protoc_insertion_point(message_clear_start:Lap)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.telemetry_.Clear();
  ::memset(&_impl_.lap_time_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.valid_sector_3_) -
      reinterpret_cast<char*>(&_impl_.lap_time_)) + sizeof(_impl_.valid_sector_3_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Lap::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 lap_time = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.lap_time_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 sector_1 = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.sector_1_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 sector_2 = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.sector_2_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 sector_3 = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.sector_3_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bool valid_lap = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _impl_.valid_lap_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bool valid_sector_1 = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          _impl_.valid_sector_1_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bool valid_sector_2 = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 56)) {
          _impl_.valid_sector_2_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bool valid_sector_3 = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 64)) {
          _impl_.valid_sector_3_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated .Telemetry telemetry = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 74)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_telemetry(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<74>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Lap::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Lap)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 lap_time = 1;
  if (this->_internal_lap_time() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(1, this->_internal_lap_time(), target);
  }

  // uint32 sector_1 = 2;
  if (this->_internal_sector_1() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(2, this->_internal_sector_1(), target);
  }

  // uint32 sector_2 = 3;
  if (this->_internal_sector_2() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(3, this->_internal_sector_2(), target);
  }

  // uint32 sector_3 = 4;
  if (this->_internal_sector_3() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(4, this->_internal_sector_3(), target);
  }

  // bool valid_lap = 5;
  if (this->_internal_valid_lap() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(5, this->_internal_valid_lap(), target);
  }

  // bool valid_sector_1 = 6;
  if (this->_internal_valid_sector_1() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(6, this->_internal_valid_sector_1(), target);
  }

  // bool valid_sector_2 = 7;
  if (this->_internal_valid_sector_2() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(7, this->_internal_valid_sector_2(), target);
  }

  // bool valid_sector_3 = 8;
  if (this->_internal_valid_sector_3() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(8, this->_internal_valid_sector_3(), target);
  }

  // repeated .Telemetry telemetry = 9;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_telemetry_size()); i < n; i++) {
    const auto& repfield = this->_internal_telemetry(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(9, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Lap)
  return target;
}

size_t Lap::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Lap)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Telemetry telemetry = 9;
  total_size += 1UL * this->_internal_telemetry_size();
  for (const auto& msg : this->_impl_.telemetry_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // uint32 lap_time = 1;
  if (this->_internal_lap_time() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_lap_time());
  }

  // uint32 sector_1 = 2;
  if (this->_internal_sector_1() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_sector_1());
  }

  // uint32 sector_2 = 3;
  if (this->_internal_sector_2() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_sector_2());
  }

  // uint32 sector_3 = 4;
  if (this->_internal_sector_3() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_sector_3());
  }

  // bool valid_lap = 5;
  if (this->_internal_valid_lap() != 0) {
    total_size += 1 + 1;
  }

  // bool valid_sector_1 = 6;
  if (this->_internal_valid_sector_1() != 0) {
    total_size += 1 + 1;
  }

  // bool valid_sector_2 = 7;
  if (this->_internal_valid_sector_2() != 0) {
    total_size += 1 + 1;
  }

  // bool valid_sector_3 = 8;
  if (this->_internal_valid_sector_3() != 0) {
    total_size += 1 + 1;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Lap::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Lap::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Lap::GetClassData() const { return &_class_data_; }


void Lap::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Lap*>(&to_msg);
  auto& from = static_cast<const Lap&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Lap)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.telemetry_.MergeFrom(from._impl_.telemetry_);
  if (from._internal_lap_time() != 0) {
    _this->_internal_set_lap_time(from._internal_lap_time());
  }
  if (from._internal_sector_1() != 0) {
    _this->_internal_set_sector_1(from._internal_sector_1());
  }
  if (from._internal_sector_2() != 0) {
    _this->_internal_set_sector_2(from._internal_sector_2());
  }
  if (from._internal_sector_3() != 0) {
    _this->_internal_set_sector_3(from._internal_sector_3());
  }
  if (from._internal_valid_lap() != 0) {
    _this->_internal_set_valid_lap(from._internal_valid_lap());
  }
  if (from._internal_valid_sector_1() != 0) {
    _this->_internal_set_valid_sector_1(from._internal_valid_sector_1());
  }
  if (from._internal_valid_sector_2() != 0) {
    _this->_internal_set_valid_sector_2(from._internal_valid_sector_2());
  }
  if (from._internal_valid_sector_3() != 0) {
    _this->_internal_set_valid_sector_3(from._internal_valid_sector_3());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Lap::CopyFrom(const Lap& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Lap)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Lap::IsInitialized() const {
  return true;
}

void Lap::InternalSwap(Lap* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.telemetry_.InternalSwap(&other->_impl_.telemetry_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Lap, _impl_.valid_sector_3_)
      + sizeof(Lap::_impl_.valid_sector_3_)
      - PROTOBUF_FIELD_OFFSET(Lap, _impl_.lap_time_)>(
          reinterpret_cast<char*>(&_impl_.lap_time_),
          reinterpret_cast<char*>(&other->_impl_.lap_time_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Lap::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Lap_2eproto_getter, &descriptor_table_Lap_2eproto_once,
      file_level_metadata_Lap_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Lap*
Arena::CreateMaybeMessage< ::Lap >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Lap >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
