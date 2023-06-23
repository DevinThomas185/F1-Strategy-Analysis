// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SprintRaceSessions.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_SprintRaceSessions_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_SprintRaceSessions_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "Practice.pb.h"
#include "Qualifying.pb.h"
#include "Race.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_SprintRaceSessions_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_SprintRaceSessions_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_SprintRaceSessions_2eproto;
class SprintRaceSessions;
struct SprintRaceSessionsDefaultTypeInternal;
extern SprintRaceSessionsDefaultTypeInternal _SprintRaceSessions_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::SprintRaceSessions* Arena::CreateMaybeMessage<::SprintRaceSessions>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class SprintRaceSessions final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:SprintRaceSessions) */ {
 public:
  inline SprintRaceSessions() : SprintRaceSessions(nullptr) {}
  ~SprintRaceSessions() override;
  explicit PROTOBUF_CONSTEXPR SprintRaceSessions(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SprintRaceSessions(const SprintRaceSessions& from);
  SprintRaceSessions(SprintRaceSessions&& from) noexcept
    : SprintRaceSessions() {
    *this = ::std::move(from);
  }

  inline SprintRaceSessions& operator=(const SprintRaceSessions& from) {
    CopyFrom(from);
    return *this;
  }
  inline SprintRaceSessions& operator=(SprintRaceSessions&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SprintRaceSessions& default_instance() {
    return *internal_default_instance();
  }
  static inline const SprintRaceSessions* internal_default_instance() {
    return reinterpret_cast<const SprintRaceSessions*>(
               &_SprintRaceSessions_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SprintRaceSessions& a, SprintRaceSessions& b) {
    a.Swap(&b);
  }
  inline void Swap(SprintRaceSessions* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SprintRaceSessions* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SprintRaceSessions* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SprintRaceSessions>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SprintRaceSessions& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const SprintRaceSessions& from) {
    SprintRaceSessions::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SprintRaceSessions* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "SprintRaceSessions";
  }
  protected:
  explicit SprintRaceSessions(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFp1FieldNumber = 1,
    kQualifyingFieldNumber = 2,
    kFp2FieldNumber = 3,
    kSprintRaceFieldNumber = 4,
    kRaceFieldNumber = 5,
  };
  // .Practice fp1 = 1;
  bool has_fp1() const;
  private:
  bool _internal_has_fp1() const;
  public:
  void clear_fp1();
  const ::Practice& fp1() const;
  PROTOBUF_NODISCARD ::Practice* release_fp1();
  ::Practice* mutable_fp1();
  void set_allocated_fp1(::Practice* fp1);
  private:
  const ::Practice& _internal_fp1() const;
  ::Practice* _internal_mutable_fp1();
  public:
  void unsafe_arena_set_allocated_fp1(
      ::Practice* fp1);
  ::Practice* unsafe_arena_release_fp1();

  // .Qualifying qualifying = 2;
  bool has_qualifying() const;
  private:
  bool _internal_has_qualifying() const;
  public:
  void clear_qualifying();
  const ::Qualifying& qualifying() const;
  PROTOBUF_NODISCARD ::Qualifying* release_qualifying();
  ::Qualifying* mutable_qualifying();
  void set_allocated_qualifying(::Qualifying* qualifying);
  private:
  const ::Qualifying& _internal_qualifying() const;
  ::Qualifying* _internal_mutable_qualifying();
  public:
  void unsafe_arena_set_allocated_qualifying(
      ::Qualifying* qualifying);
  ::Qualifying* unsafe_arena_release_qualifying();

  // .Practice fp2 = 3;
  bool has_fp2() const;
  private:
  bool _internal_has_fp2() const;
  public:
  void clear_fp2();
  const ::Practice& fp2() const;
  PROTOBUF_NODISCARD ::Practice* release_fp2();
  ::Practice* mutable_fp2();
  void set_allocated_fp2(::Practice* fp2);
  private:
  const ::Practice& _internal_fp2() const;
  ::Practice* _internal_mutable_fp2();
  public:
  void unsafe_arena_set_allocated_fp2(
      ::Practice* fp2);
  ::Practice* unsafe_arena_release_fp2();

  // .Race sprint_race = 4;
  bool has_sprint_race() const;
  private:
  bool _internal_has_sprint_race() const;
  public:
  void clear_sprint_race();
  const ::Race& sprint_race() const;
  PROTOBUF_NODISCARD ::Race* release_sprint_race();
  ::Race* mutable_sprint_race();
  void set_allocated_sprint_race(::Race* sprint_race);
  private:
  const ::Race& _internal_sprint_race() const;
  ::Race* _internal_mutable_sprint_race();
  public:
  void unsafe_arena_set_allocated_sprint_race(
      ::Race* sprint_race);
  ::Race* unsafe_arena_release_sprint_race();

  // .Race race = 5;
  bool has_race() const;
  private:
  bool _internal_has_race() const;
  public:
  void clear_race();
  const ::Race& race() const;
  PROTOBUF_NODISCARD ::Race* release_race();
  ::Race* mutable_race();
  void set_allocated_race(::Race* race);
  private:
  const ::Race& _internal_race() const;
  ::Race* _internal_mutable_race();
  public:
  void unsafe_arena_set_allocated_race(
      ::Race* race);
  ::Race* unsafe_arena_release_race();

  // @@protoc_insertion_point(class_scope:SprintRaceSessions)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::Practice* fp1_;
    ::Qualifying* qualifying_;
    ::Practice* fp2_;
    ::Race* sprint_race_;
    ::Race* race_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_SprintRaceSessions_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SprintRaceSessions

// .Practice fp1 = 1;
inline bool SprintRaceSessions::_internal_has_fp1() const {
  return this != internal_default_instance() && _impl_.fp1_ != nullptr;
}
inline bool SprintRaceSessions::has_fp1() const {
  return _internal_has_fp1();
}
inline const ::Practice& SprintRaceSessions::_internal_fp1() const {
  const ::Practice* p = _impl_.fp1_;
  return p != nullptr ? *p : reinterpret_cast<const ::Practice&>(
      ::_Practice_default_instance_);
}
inline const ::Practice& SprintRaceSessions::fp1() const {
  // @@protoc_insertion_point(field_get:SprintRaceSessions.fp1)
  return _internal_fp1();
}
inline void SprintRaceSessions::unsafe_arena_set_allocated_fp1(
    ::Practice* fp1) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.fp1_);
  }
  _impl_.fp1_ = fp1;
  if (fp1) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SprintRaceSessions.fp1)
}
inline ::Practice* SprintRaceSessions::release_fp1() {
  
  ::Practice* temp = _impl_.fp1_;
  _impl_.fp1_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::Practice* SprintRaceSessions::unsafe_arena_release_fp1() {
  // @@protoc_insertion_point(field_release:SprintRaceSessions.fp1)
  
  ::Practice* temp = _impl_.fp1_;
  _impl_.fp1_ = nullptr;
  return temp;
}
inline ::Practice* SprintRaceSessions::_internal_mutable_fp1() {
  
  if (_impl_.fp1_ == nullptr) {
    auto* p = CreateMaybeMessage<::Practice>(GetArenaForAllocation());
    _impl_.fp1_ = p;
  }
  return _impl_.fp1_;
}
inline ::Practice* SprintRaceSessions::mutable_fp1() {
  ::Practice* _msg = _internal_mutable_fp1();
  // @@protoc_insertion_point(field_mutable:SprintRaceSessions.fp1)
  return _msg;
}
inline void SprintRaceSessions::set_allocated_fp1(::Practice* fp1) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.fp1_);
  }
  if (fp1) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(fp1));
    if (message_arena != submessage_arena) {
      fp1 = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, fp1, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.fp1_ = fp1;
  // @@protoc_insertion_point(field_set_allocated:SprintRaceSessions.fp1)
}

// .Qualifying qualifying = 2;
inline bool SprintRaceSessions::_internal_has_qualifying() const {
  return this != internal_default_instance() && _impl_.qualifying_ != nullptr;
}
inline bool SprintRaceSessions::has_qualifying() const {
  return _internal_has_qualifying();
}
inline const ::Qualifying& SprintRaceSessions::_internal_qualifying() const {
  const ::Qualifying* p = _impl_.qualifying_;
  return p != nullptr ? *p : reinterpret_cast<const ::Qualifying&>(
      ::_Qualifying_default_instance_);
}
inline const ::Qualifying& SprintRaceSessions::qualifying() const {
  // @@protoc_insertion_point(field_get:SprintRaceSessions.qualifying)
  return _internal_qualifying();
}
inline void SprintRaceSessions::unsafe_arena_set_allocated_qualifying(
    ::Qualifying* qualifying) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.qualifying_);
  }
  _impl_.qualifying_ = qualifying;
  if (qualifying) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SprintRaceSessions.qualifying)
}
inline ::Qualifying* SprintRaceSessions::release_qualifying() {
  
  ::Qualifying* temp = _impl_.qualifying_;
  _impl_.qualifying_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::Qualifying* SprintRaceSessions::unsafe_arena_release_qualifying() {
  // @@protoc_insertion_point(field_release:SprintRaceSessions.qualifying)
  
  ::Qualifying* temp = _impl_.qualifying_;
  _impl_.qualifying_ = nullptr;
  return temp;
}
inline ::Qualifying* SprintRaceSessions::_internal_mutable_qualifying() {
  
  if (_impl_.qualifying_ == nullptr) {
    auto* p = CreateMaybeMessage<::Qualifying>(GetArenaForAllocation());
    _impl_.qualifying_ = p;
  }
  return _impl_.qualifying_;
}
inline ::Qualifying* SprintRaceSessions::mutable_qualifying() {
  ::Qualifying* _msg = _internal_mutable_qualifying();
  // @@protoc_insertion_point(field_mutable:SprintRaceSessions.qualifying)
  return _msg;
}
inline void SprintRaceSessions::set_allocated_qualifying(::Qualifying* qualifying) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.qualifying_);
  }
  if (qualifying) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(qualifying));
    if (message_arena != submessage_arena) {
      qualifying = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, qualifying, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.qualifying_ = qualifying;
  // @@protoc_insertion_point(field_set_allocated:SprintRaceSessions.qualifying)
}

// .Practice fp2 = 3;
inline bool SprintRaceSessions::_internal_has_fp2() const {
  return this != internal_default_instance() && _impl_.fp2_ != nullptr;
}
inline bool SprintRaceSessions::has_fp2() const {
  return _internal_has_fp2();
}
inline const ::Practice& SprintRaceSessions::_internal_fp2() const {
  const ::Practice* p = _impl_.fp2_;
  return p != nullptr ? *p : reinterpret_cast<const ::Practice&>(
      ::_Practice_default_instance_);
}
inline const ::Practice& SprintRaceSessions::fp2() const {
  // @@protoc_insertion_point(field_get:SprintRaceSessions.fp2)
  return _internal_fp2();
}
inline void SprintRaceSessions::unsafe_arena_set_allocated_fp2(
    ::Practice* fp2) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.fp2_);
  }
  _impl_.fp2_ = fp2;
  if (fp2) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SprintRaceSessions.fp2)
}
inline ::Practice* SprintRaceSessions::release_fp2() {
  
  ::Practice* temp = _impl_.fp2_;
  _impl_.fp2_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::Practice* SprintRaceSessions::unsafe_arena_release_fp2() {
  // @@protoc_insertion_point(field_release:SprintRaceSessions.fp2)
  
  ::Practice* temp = _impl_.fp2_;
  _impl_.fp2_ = nullptr;
  return temp;
}
inline ::Practice* SprintRaceSessions::_internal_mutable_fp2() {
  
  if (_impl_.fp2_ == nullptr) {
    auto* p = CreateMaybeMessage<::Practice>(GetArenaForAllocation());
    _impl_.fp2_ = p;
  }
  return _impl_.fp2_;
}
inline ::Practice* SprintRaceSessions::mutable_fp2() {
  ::Practice* _msg = _internal_mutable_fp2();
  // @@protoc_insertion_point(field_mutable:SprintRaceSessions.fp2)
  return _msg;
}
inline void SprintRaceSessions::set_allocated_fp2(::Practice* fp2) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.fp2_);
  }
  if (fp2) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(fp2));
    if (message_arena != submessage_arena) {
      fp2 = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, fp2, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.fp2_ = fp2;
  // @@protoc_insertion_point(field_set_allocated:SprintRaceSessions.fp2)
}

// .Race sprint_race = 4;
inline bool SprintRaceSessions::_internal_has_sprint_race() const {
  return this != internal_default_instance() && _impl_.sprint_race_ != nullptr;
}
inline bool SprintRaceSessions::has_sprint_race() const {
  return _internal_has_sprint_race();
}
inline const ::Race& SprintRaceSessions::_internal_sprint_race() const {
  const ::Race* p = _impl_.sprint_race_;
  return p != nullptr ? *p : reinterpret_cast<const ::Race&>(
      ::_Race_default_instance_);
}
inline const ::Race& SprintRaceSessions::sprint_race() const {
  // @@protoc_insertion_point(field_get:SprintRaceSessions.sprint_race)
  return _internal_sprint_race();
}
inline void SprintRaceSessions::unsafe_arena_set_allocated_sprint_race(
    ::Race* sprint_race) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.sprint_race_);
  }
  _impl_.sprint_race_ = sprint_race;
  if (sprint_race) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SprintRaceSessions.sprint_race)
}
inline ::Race* SprintRaceSessions::release_sprint_race() {
  
  ::Race* temp = _impl_.sprint_race_;
  _impl_.sprint_race_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::Race* SprintRaceSessions::unsafe_arena_release_sprint_race() {
  // @@protoc_insertion_point(field_release:SprintRaceSessions.sprint_race)
  
  ::Race* temp = _impl_.sprint_race_;
  _impl_.sprint_race_ = nullptr;
  return temp;
}
inline ::Race* SprintRaceSessions::_internal_mutable_sprint_race() {
  
  if (_impl_.sprint_race_ == nullptr) {
    auto* p = CreateMaybeMessage<::Race>(GetArenaForAllocation());
    _impl_.sprint_race_ = p;
  }
  return _impl_.sprint_race_;
}
inline ::Race* SprintRaceSessions::mutable_sprint_race() {
  ::Race* _msg = _internal_mutable_sprint_race();
  // @@protoc_insertion_point(field_mutable:SprintRaceSessions.sprint_race)
  return _msg;
}
inline void SprintRaceSessions::set_allocated_sprint_race(::Race* sprint_race) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.sprint_race_);
  }
  if (sprint_race) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(sprint_race));
    if (message_arena != submessage_arena) {
      sprint_race = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, sprint_race, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.sprint_race_ = sprint_race;
  // @@protoc_insertion_point(field_set_allocated:SprintRaceSessions.sprint_race)
}

// .Race race = 5;
inline bool SprintRaceSessions::_internal_has_race() const {
  return this != internal_default_instance() && _impl_.race_ != nullptr;
}
inline bool SprintRaceSessions::has_race() const {
  return _internal_has_race();
}
inline const ::Race& SprintRaceSessions::_internal_race() const {
  const ::Race* p = _impl_.race_;
  return p != nullptr ? *p : reinterpret_cast<const ::Race&>(
      ::_Race_default_instance_);
}
inline const ::Race& SprintRaceSessions::race() const {
  // @@protoc_insertion_point(field_get:SprintRaceSessions.race)
  return _internal_race();
}
inline void SprintRaceSessions::unsafe_arena_set_allocated_race(
    ::Race* race) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.race_);
  }
  _impl_.race_ = race;
  if (race) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SprintRaceSessions.race)
}
inline ::Race* SprintRaceSessions::release_race() {
  
  ::Race* temp = _impl_.race_;
  _impl_.race_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::Race* SprintRaceSessions::unsafe_arena_release_race() {
  // @@protoc_insertion_point(field_release:SprintRaceSessions.race)
  
  ::Race* temp = _impl_.race_;
  _impl_.race_ = nullptr;
  return temp;
}
inline ::Race* SprintRaceSessions::_internal_mutable_race() {
  
  if (_impl_.race_ == nullptr) {
    auto* p = CreateMaybeMessage<::Race>(GetArenaForAllocation());
    _impl_.race_ = p;
  }
  return _impl_.race_;
}
inline ::Race* SprintRaceSessions::mutable_race() {
  ::Race* _msg = _internal_mutable_race();
  // @@protoc_insertion_point(field_mutable:SprintRaceSessions.race)
  return _msg;
}
inline void SprintRaceSessions::set_allocated_race(::Race* race) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.race_);
  }
  if (race) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(race));
    if (message_arena != submessage_arena) {
      race = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, race, submessage_arena);
    }
    
  } else {
    
  }
  _impl_.race_ = race;
  // @@protoc_insertion_point(field_set_allocated:SprintRaceSessions.race)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_SprintRaceSessions_2eproto
