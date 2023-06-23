// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RaceWeekend.proto

#include "RaceWeekend.pb.h"

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

PROTOBUF_CONSTEXPR RaceWeekend::RaceWeekend(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.track_id_)*/0
  , /*decltype(_impl_.race_type_)*/0
  , /*decltype(_impl_.sessions_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_._oneof_case_)*/{}} {}
struct RaceWeekendDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RaceWeekendDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~RaceWeekendDefaultTypeInternal() {}
  union {
    RaceWeekend _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RaceWeekendDefaultTypeInternal _RaceWeekend_default_instance_;
static ::_pb::Metadata file_level_metadata_RaceWeekend_2eproto[1];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_RaceWeekend_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_RaceWeekend_2eproto = nullptr;

const uint32_t TableStruct_RaceWeekend_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::RaceWeekend, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::RaceWeekend, _impl_._oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::RaceWeekend, _impl_.track_id_),
  PROTOBUF_FIELD_OFFSET(::RaceWeekend, _impl_.race_type_),
  ::_pbi::kInvalidFieldOffsetTag,
  ::_pbi::kInvalidFieldOffsetTag,
  ::_pbi::kInvalidFieldOffsetTag,
  PROTOBUF_FIELD_OFFSET(::RaceWeekend, _impl_.sessions_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::RaceWeekend)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_RaceWeekend_default_instance_._instance,
};

const char descriptor_table_protodef_RaceWeekend_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021RaceWeekend.proto\032\022RaceSessions.proto\032"
  "\030SprintRaceSessions.proto\032\034SprintRaceSes"
  "sions2023.proto\"\273\002\n\013RaceWeekend\022\020\n\010track"
  "_id\030\001 \001(\005\022(\n\trace_type\030\002 \001(\0162\025.RaceWeeke"
  "nd.RaceType\022&\n\rrace_sessions\030\003 \001(\0132\r.Rac"
  "eSessionsH\000\0223\n\024sprint_race_sessions\030\004 \001("
  "\0132\023.SprintRaceSessionsH\000\022<\n\031sprint_race_"
  "sessions_2023\030\005 \001(\0132\027.SprintRaceSessions"
  "2023H\000\"I\n\010RaceType\022\020\n\014RACE_WEEKEND\020\000\022\022\n\016"
  "SPRINT_WEEKEND\020\001\022\027\n\023SPRINT_WEEKEND_2023\020"
  "\002B\n\n\010sessionsb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_RaceWeekend_2eproto_deps[3] = {
  &::descriptor_table_RaceSessions_2eproto,
  &::descriptor_table_SprintRaceSessions_2eproto,
  &::descriptor_table_SprintRaceSessions2023_2eproto,
};
static ::_pbi::once_flag descriptor_table_RaceWeekend_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_RaceWeekend_2eproto = {
    false, false, 421, descriptor_table_protodef_RaceWeekend_2eproto,
    "RaceWeekend.proto",
    &descriptor_table_RaceWeekend_2eproto_once, descriptor_table_RaceWeekend_2eproto_deps, 3, 1,
    schemas, file_default_instances, TableStruct_RaceWeekend_2eproto::offsets,
    file_level_metadata_RaceWeekend_2eproto, file_level_enum_descriptors_RaceWeekend_2eproto,
    file_level_service_descriptors_RaceWeekend_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_RaceWeekend_2eproto_getter() {
  return &descriptor_table_RaceWeekend_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_RaceWeekend_2eproto(&descriptor_table_RaceWeekend_2eproto);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* RaceWeekend_RaceType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_RaceWeekend_2eproto);
  return file_level_enum_descriptors_RaceWeekend_2eproto[0];
}
bool RaceWeekend_RaceType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))
constexpr RaceWeekend_RaceType RaceWeekend::RACE_WEEKEND;
constexpr RaceWeekend_RaceType RaceWeekend::SPRINT_WEEKEND;
constexpr RaceWeekend_RaceType RaceWeekend::SPRINT_WEEKEND_2023;
constexpr RaceWeekend_RaceType RaceWeekend::RaceType_MIN;
constexpr RaceWeekend_RaceType RaceWeekend::RaceType_MAX;
constexpr int RaceWeekend::RaceType_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))

// ===================================================================

class RaceWeekend::_Internal {
 public:
  static const ::RaceSessions& race_sessions(const RaceWeekend* msg);
  static const ::SprintRaceSessions& sprint_race_sessions(const RaceWeekend* msg);
  static const ::SprintRaceSessions2023& sprint_race_sessions_2023(const RaceWeekend* msg);
};

const ::RaceSessions&
RaceWeekend::_Internal::race_sessions(const RaceWeekend* msg) {
  return *msg->_impl_.sessions_.race_sessions_;
}
const ::SprintRaceSessions&
RaceWeekend::_Internal::sprint_race_sessions(const RaceWeekend* msg) {
  return *msg->_impl_.sessions_.sprint_race_sessions_;
}
const ::SprintRaceSessions2023&
RaceWeekend::_Internal::sprint_race_sessions_2023(const RaceWeekend* msg) {
  return *msg->_impl_.sessions_.sprint_race_sessions_2023_;
}
void RaceWeekend::set_allocated_race_sessions(::RaceSessions* race_sessions) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  clear_sessions();
  if (race_sessions) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(race_sessions));
    if (message_arena != submessage_arena) {
      race_sessions = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, race_sessions, submessage_arena);
    }
    set_has_race_sessions();
    _impl_.sessions_.race_sessions_ = race_sessions;
  }
  // @@protoc_insertion_point(field_set_allocated:RaceWeekend.race_sessions)
}
void RaceWeekend::clear_race_sessions() {
  if (_internal_has_race_sessions()) {
    if (GetArenaForAllocation() == nullptr) {
      delete _impl_.sessions_.race_sessions_;
    }
    clear_has_sessions();
  }
}
void RaceWeekend::set_allocated_sprint_race_sessions(::SprintRaceSessions* sprint_race_sessions) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  clear_sessions();
  if (sprint_race_sessions) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(sprint_race_sessions));
    if (message_arena != submessage_arena) {
      sprint_race_sessions = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, sprint_race_sessions, submessage_arena);
    }
    set_has_sprint_race_sessions();
    _impl_.sessions_.sprint_race_sessions_ = sprint_race_sessions;
  }
  // @@protoc_insertion_point(field_set_allocated:RaceWeekend.sprint_race_sessions)
}
void RaceWeekend::clear_sprint_race_sessions() {
  if (_internal_has_sprint_race_sessions()) {
    if (GetArenaForAllocation() == nullptr) {
      delete _impl_.sessions_.sprint_race_sessions_;
    }
    clear_has_sessions();
  }
}
void RaceWeekend::set_allocated_sprint_race_sessions_2023(::SprintRaceSessions2023* sprint_race_sessions_2023) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  clear_sessions();
  if (sprint_race_sessions_2023) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(sprint_race_sessions_2023));
    if (message_arena != submessage_arena) {
      sprint_race_sessions_2023 = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, sprint_race_sessions_2023, submessage_arena);
    }
    set_has_sprint_race_sessions_2023();
    _impl_.sessions_.sprint_race_sessions_2023_ = sprint_race_sessions_2023;
  }
  // @@protoc_insertion_point(field_set_allocated:RaceWeekend.sprint_race_sessions_2023)
}
void RaceWeekend::clear_sprint_race_sessions_2023() {
  if (_internal_has_sprint_race_sessions_2023()) {
    if (GetArenaForAllocation() == nullptr) {
      delete _impl_.sessions_.sprint_race_sessions_2023_;
    }
    clear_has_sessions();
  }
}
RaceWeekend::RaceWeekend(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:RaceWeekend)
}
RaceWeekend::RaceWeekend(const RaceWeekend& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  RaceWeekend* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.track_id_){}
    , decltype(_impl_.race_type_){}
    , decltype(_impl_.sessions_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , /*decltype(_impl_._oneof_case_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.track_id_, &from._impl_.track_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.race_type_) -
    reinterpret_cast<char*>(&_impl_.track_id_)) + sizeof(_impl_.race_type_));
  clear_has_sessions();
  switch (from.sessions_case()) {
    case kRaceSessions: {
      _this->_internal_mutable_race_sessions()->::RaceSessions::MergeFrom(
          from._internal_race_sessions());
      break;
    }
    case kSprintRaceSessions: {
      _this->_internal_mutable_sprint_race_sessions()->::SprintRaceSessions::MergeFrom(
          from._internal_sprint_race_sessions());
      break;
    }
    case kSprintRaceSessions2023: {
      _this->_internal_mutable_sprint_race_sessions_2023()->::SprintRaceSessions2023::MergeFrom(
          from._internal_sprint_race_sessions_2023());
      break;
    }
    case SESSIONS_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:RaceWeekend)
}

inline void RaceWeekend::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.track_id_){0}
    , decltype(_impl_.race_type_){0}
    , decltype(_impl_.sessions_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , /*decltype(_impl_._oneof_case_)*/{}
  };
  clear_has_sessions();
}

RaceWeekend::~RaceWeekend() {
  // @@protoc_insertion_point(destructor:RaceWeekend)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void RaceWeekend::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (has_sessions()) {
    clear_sessions();
  }
}

void RaceWeekend::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void RaceWeekend::clear_sessions() {
// @@protoc_insertion_point(one_of_clear_start:RaceWeekend)
  switch (sessions_case()) {
    case kRaceSessions: {
      if (GetArenaForAllocation() == nullptr) {
        delete _impl_.sessions_.race_sessions_;
      }
      break;
    }
    case kSprintRaceSessions: {
      if (GetArenaForAllocation() == nullptr) {
        delete _impl_.sessions_.sprint_race_sessions_;
      }
      break;
    }
    case kSprintRaceSessions2023: {
      if (GetArenaForAllocation() == nullptr) {
        delete _impl_.sessions_.sprint_race_sessions_2023_;
      }
      break;
    }
    case SESSIONS_NOT_SET: {
      break;
    }
  }
  _impl_._oneof_case_[0] = SESSIONS_NOT_SET;
}


void RaceWeekend::Clear() {
// @@protoc_insertion_point(message_clear_start:RaceWeekend)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.track_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.race_type_) -
      reinterpret_cast<char*>(&_impl_.track_id_)) + sizeof(_impl_.race_type_));
  clear_sessions();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* RaceWeekend::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 track_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.track_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .RaceWeekend.RaceType race_type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_race_type(static_cast<::RaceWeekend_RaceType>(val));
        } else
          goto handle_unusual;
        continue;
      // .RaceSessions race_sessions = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_race_sessions(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .SprintRaceSessions sprint_race_sessions = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          ptr = ctx->ParseMessage(_internal_mutable_sprint_race_sessions(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .SprintRaceSessions2023 sprint_race_sessions_2023 = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          ptr = ctx->ParseMessage(_internal_mutable_sprint_race_sessions_2023(), ptr);
          CHK_(ptr);
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

uint8_t* RaceWeekend::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:RaceWeekend)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 track_id = 1;
  if (this->_internal_track_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_track_id(), target);
  }

  // .RaceWeekend.RaceType race_type = 2;
  if (this->_internal_race_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      2, this->_internal_race_type(), target);
  }

  // .RaceSessions race_sessions = 3;
  if (_internal_has_race_sessions()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(3, _Internal::race_sessions(this),
        _Internal::race_sessions(this).GetCachedSize(), target, stream);
  }

  // .SprintRaceSessions sprint_race_sessions = 4;
  if (_internal_has_sprint_race_sessions()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(4, _Internal::sprint_race_sessions(this),
        _Internal::sprint_race_sessions(this).GetCachedSize(), target, stream);
  }

  // .SprintRaceSessions2023 sprint_race_sessions_2023 = 5;
  if (_internal_has_sprint_race_sessions_2023()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(5, _Internal::sprint_race_sessions_2023(this),
        _Internal::sprint_race_sessions_2023(this).GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:RaceWeekend)
  return target;
}

size_t RaceWeekend::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:RaceWeekend)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 track_id = 1;
  if (this->_internal_track_id() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_track_id());
  }

  // .RaceWeekend.RaceType race_type = 2;
  if (this->_internal_race_type() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_race_type());
  }

  switch (sessions_case()) {
    // .RaceSessions race_sessions = 3;
    case kRaceSessions: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *_impl_.sessions_.race_sessions_);
      break;
    }
    // .SprintRaceSessions sprint_race_sessions = 4;
    case kSprintRaceSessions: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *_impl_.sessions_.sprint_race_sessions_);
      break;
    }
    // .SprintRaceSessions2023 sprint_race_sessions_2023 = 5;
    case kSprintRaceSessions2023: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *_impl_.sessions_.sprint_race_sessions_2023_);
      break;
    }
    case SESSIONS_NOT_SET: {
      break;
    }
  }
  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData RaceWeekend::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    RaceWeekend::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*RaceWeekend::GetClassData() const { return &_class_data_; }


void RaceWeekend::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<RaceWeekend*>(&to_msg);
  auto& from = static_cast<const RaceWeekend&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:RaceWeekend)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_track_id() != 0) {
    _this->_internal_set_track_id(from._internal_track_id());
  }
  if (from._internal_race_type() != 0) {
    _this->_internal_set_race_type(from._internal_race_type());
  }
  switch (from.sessions_case()) {
    case kRaceSessions: {
      _this->_internal_mutable_race_sessions()->::RaceSessions::MergeFrom(
          from._internal_race_sessions());
      break;
    }
    case kSprintRaceSessions: {
      _this->_internal_mutable_sprint_race_sessions()->::SprintRaceSessions::MergeFrom(
          from._internal_sprint_race_sessions());
      break;
    }
    case kSprintRaceSessions2023: {
      _this->_internal_mutable_sprint_race_sessions_2023()->::SprintRaceSessions2023::MergeFrom(
          from._internal_sprint_race_sessions_2023());
      break;
    }
    case SESSIONS_NOT_SET: {
      break;
    }
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void RaceWeekend::CopyFrom(const RaceWeekend& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:RaceWeekend)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RaceWeekend::IsInitialized() const {
  return true;
}

void RaceWeekend::InternalSwap(RaceWeekend* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(RaceWeekend, _impl_.race_type_)
      + sizeof(RaceWeekend::_impl_.race_type_)
      - PROTOBUF_FIELD_OFFSET(RaceWeekend, _impl_.track_id_)>(
          reinterpret_cast<char*>(&_impl_.track_id_),
          reinterpret_cast<char*>(&other->_impl_.track_id_));
  swap(_impl_.sessions_, other->_impl_.sessions_);
  swap(_impl_._oneof_case_[0], other->_impl_._oneof_case_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata RaceWeekend::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_RaceWeekend_2eproto_getter, &descriptor_table_RaceWeekend_2eproto_once,
      file_level_metadata_RaceWeekend_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::RaceWeekend*
Arena::CreateMaybeMessage< ::RaceWeekend >(Arena* arena) {
  return Arena::CreateMessageInternal< ::RaceWeekend >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
