// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Stint.proto

#include "Stint.pb.h"

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

PROTOBUF_CONSTEXPR Stint::Stint(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.lap_)*/{}
  , /*decltype(_impl_.setup_)*/nullptr
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct StintDefaultTypeInternal {
  PROTOBUF_CONSTEXPR StintDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~StintDefaultTypeInternal() {}
  union {
    Stint _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 StintDefaultTypeInternal _Stint_default_instance_;
static ::_pb::Metadata file_level_metadata_Stint_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_Stint_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Stint_2eproto = nullptr;

const uint32_t TableStruct_Stint_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Stint, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Stint, _impl_.lap_),
  PROTOBUF_FIELD_OFFSET(::Stint, _impl_.setup_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Stint)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_Stint_default_instance_._instance,
};

const char descriptor_table_protodef_Stint_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013Stint.proto\032\tLap.proto\032\013Setup.proto\"1\n"
  "\005Stint\022\021\n\003lap\030\001 \003(\0132\004.Lap\022\025\n\005setup\030\002 \001(\013"
  "2\006.Setupb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_Stint_2eproto_deps[2] = {
  &::descriptor_table_Lap_2eproto,
  &::descriptor_table_Setup_2eproto,
};
static ::_pbi::once_flag descriptor_table_Stint_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Stint_2eproto = {
    false, false, 96, descriptor_table_protodef_Stint_2eproto,
    "Stint.proto",
    &descriptor_table_Stint_2eproto_once, descriptor_table_Stint_2eproto_deps, 2, 1,
    schemas, file_default_instances, TableStruct_Stint_2eproto::offsets,
    file_level_metadata_Stint_2eproto, file_level_enum_descriptors_Stint_2eproto,
    file_level_service_descriptors_Stint_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Stint_2eproto_getter() {
  return &descriptor_table_Stint_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Stint_2eproto(&descriptor_table_Stint_2eproto);

// ===================================================================

class Stint::_Internal {
 public:
  static const ::Setup& setup(const Stint* msg);
};

const ::Setup&
Stint::_Internal::setup(const Stint* msg) {
  return *msg->_impl_.setup_;
}
void Stint::clear_lap() {
  _impl_.lap_.Clear();
}
void Stint::clear_setup() {
  if (GetArenaForAllocation() == nullptr && _impl_.setup_ != nullptr) {
    delete _impl_.setup_;
  }
  _impl_.setup_ = nullptr;
}
Stint::Stint(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Stint)
}
Stint::Stint(const Stint& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Stint* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.lap_){from._impl_.lap_}
    , decltype(_impl_.setup_){nullptr}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_setup()) {
    _this->_impl_.setup_ = new ::Setup(*from._impl_.setup_);
  }
  // @@protoc_insertion_point(copy_constructor:Stint)
}

inline void Stint::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.lap_){arena}
    , decltype(_impl_.setup_){nullptr}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

Stint::~Stint() {
  // @@protoc_insertion_point(destructor:Stint)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Stint::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.lap_.~RepeatedPtrField();
  if (this != internal_default_instance()) delete _impl_.setup_;
}

void Stint::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Stint::Clear() {
// @@protoc_insertion_point(message_clear_start:Stint)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.lap_.Clear();
  if (GetArenaForAllocation() == nullptr && _impl_.setup_ != nullptr) {
    delete _impl_.setup_;
  }
  _impl_.setup_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Stint::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .Lap lap = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_lap(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else
          goto handle_unusual;
        continue;
      // .Setup setup = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_setup(), ptr);
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

uint8_t* Stint::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Stint)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .Lap lap = 1;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_lap_size()); i < n; i++) {
    const auto& repfield = this->_internal_lap(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(1, repfield, repfield.GetCachedSize(), target, stream);
  }

  // .Setup setup = 2;
  if (this->_internal_has_setup()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(2, _Internal::setup(this),
        _Internal::setup(this).GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Stint)
  return target;
}

size_t Stint::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Stint)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Lap lap = 1;
  total_size += 1UL * this->_internal_lap_size();
  for (const auto& msg : this->_impl_.lap_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // .Setup setup = 2;
  if (this->_internal_has_setup()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.setup_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Stint::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Stint::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Stint::GetClassData() const { return &_class_data_; }


void Stint::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Stint*>(&to_msg);
  auto& from = static_cast<const Stint&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Stint)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.lap_.MergeFrom(from._impl_.lap_);
  if (from._internal_has_setup()) {
    _this->_internal_mutable_setup()->::Setup::MergeFrom(
        from._internal_setup());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Stint::CopyFrom(const Stint& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Stint)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Stint::IsInitialized() const {
  return true;
}

void Stint::InternalSwap(Stint* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.lap_.InternalSwap(&other->_impl_.lap_);
  swap(_impl_.setup_, other->_impl_.setup_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Stint::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Stint_2eproto_getter, &descriptor_table_Stint_2eproto_once,
      file_level_metadata_Stint_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Stint*
Arena::CreateMaybeMessage< ::Stint >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Stint >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
