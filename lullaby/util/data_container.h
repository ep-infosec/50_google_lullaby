/*
Copyright 2017-2019 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef LULLABY_UTIL_DATA_CONTAINER_H_
#define LULLABY_UTIL_DATA_CONTAINER_H_

#include <cstring>
#include <functional>
#include <memory>

namespace lull {

// Stores bytes with access settings that determine whether or not read+write
// operations are permitted.
class DataContainer {
 public:
  using DataPtr =
      std::unique_ptr<uint8_t[], std::function<void(const uint8_t*)>>;

  enum AccessFlags {
    kNone = 0,
    kRead = 0x01 << 0,
    kWrite = 0x01 << 1,
    kAll = kRead | kWrite
  };

  DataContainer();

  // Creates an empty DataContainer that uses |data| as data storage, with
  // |capacity| bytes available for storage. Read-write access to the
  // DataContainer is set by |access|.
  DataContainer(DataPtr data, const size_t capacity, AccessFlags access);

  // Creates a DataContainer that initially has a size of |initial_size| bytes.
  DataContainer(DataPtr data, const size_t initial_size, const size_t capacity,
                AccessFlags access);

  // Returns a DataContainer of |capacity| allocated from the heap with
  // read+write access.
  static DataContainer CreateHeapDataContainer(size_t capacity) {
    return DataContainer(DataPtr(new uint8_t[capacity],
                                 [](const uint8_t* ptr) { delete[] ptr; }),
                         capacity, AccessFlags::kAll);
  }

  // Returns a DataContainer of |size| allocated from the heap with a copy of
  // the |data|.
  static DataContainer CreateDataCopy(const uint8_t* data, size_t size) {
    DataContainer container = CreateHeapDataContainer(size);
    container.Append(data, size);
    return container;
  }

  // Returns a DataContainer which points to |size| bytes at |ptr| with
  // read-only access. The DataContainer does not assume ownership of the data.
  template <typename T>
  static DataContainer WrapDataAsReadOnly(const T* ptr, size_t size) {
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(ptr);
    return DataContainer(DataContainer::DataPtr(const_cast<uint8_t*>(bytes),
                                                [](const uint8_t*) {}),
                         size, size, AccessFlags::kRead);
  }

  // Returns true if the data container has read access. Data containers with
  // a max size of 0 are considered unreadable.
  bool IsReadable() const {
    return capacity_ > 0 && access_ & AccessFlags::kRead;
  }

  // Returns true if the data container has write access. Data containers with
  // a max size of 0 are considered unwritable.
  bool IsWritable() const {
    return capacity_ > 0 && access_ & AccessFlags::kWrite;
  }

  // Returns const pointer to the beginning of the data, or nullptr if the
  // container does not have read access.
  const uint8_t* GetReadPtr() const;

  // Returns mutable pointer to the beginning of the data, or nullptr if the
  // container does not have read+write access.
  uint8_t* GetData();

  // Returns pointer to data to append |size| bytes at, or nullptr if
  // it can???t fit |size| bytes or no write access. Side effect of
  // increasing the current size of the container by |size|.
  // This is useful to use instead of Append if you want to write data directly
  // to the memory of the container instead of copying it over.
  // Be careful not to read using this pointer unless read access is granted,
  // otherwise results will be undefined.
  uint8_t* GetAppendPtr(size_t size);

  // Copies |size| bytes at |data| to the end of the container. Returns true
  // if the bytes were written at the end of the container, or false if |size|
  // bytes couldn???t fit or no write access. Does not append any bytes if there
  // is not enough room for all the bytes. This will overwrite data that is
  // written using the mutable pointer.
  bool Append(const uint8_t* data, size_t size);

  // Advances the write head of the data container by the specified number of
  // bytes, effectively increasing the size of the data container.
  bool Advance(size_t size);

  // Returns the total number of bytes that can fit into the container.
  size_t GetCapacity() const { return capacity_; }

  // Returns the current number of bytes appended to the container. Note that
  // this will not count bytes written directly using the mutable data pointer.
  size_t GetSize() const { return size_; }

  // Creates a copy allocated from the heap with read+write access. If *this
  // doesn't have read access, this function will DFATAL and the result will be
  // empty.
  DataContainer CreateHeapCopy() const;

 private:
  DataPtr data_;
  size_t size_ = 0;
  size_t capacity_ = 0;
  AccessFlags access_ = kNone;
};

}  // namespace lull

#endif  // LULLABY_UTIL_DATA_CONTAINER_H_
