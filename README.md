# cpputils
CppUtils library consists of serialization, hashing, encryption, synchronization classes. There is also Logger, ThreadPool, Files singleton classes.

## Serialization
Serialization is implemented by following classes: Serializer, Serializable, BinaryArchive.

### CppUtils::Serialization::Serializable
`CppUtils::Serialization::Serializable` is a base class for entities that should be serialized/deserialzied.
Each derived class must override two virtual methods of base class: `void Serializable::Serialize(BinaryArchive&) const` and `void Serializable::Deserialize(BinaryArchive&)`.
Each method is responsible for serializing and deserializing the serializable entity's content respectively.

For example:

```cpp
class Person : public Serializable {
 public:
  Person() {}
  Person(const std::string& name)
      : name(name) {}

  std::string GetName() const { return name; }
  void SetName(const std::string& name) { this->name = name; }

  void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(name, archive);
  }
  void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(name, archive);
  }

 private:
  std::string name;
};
```
### CppUtils::Serialization::Serializer
`CppUtils::Serialization::Serializer` is a singleton class that actually provides binary serialization.
It supports integral types (int, long long, bool etc), enum classes, STL(C++17) strings, containers, smart pointers and custom serializable entities. 
It doesn't support raw pointers because there is no way to validate it.
It doesn't serialize any meta information about data types so you should be carefull what are you deserializing.

There are two overloaded method templates: `void Serializer::Serialize(value, BinaryArchive&)` and `void Serializer::Deserialize(value, BinaryArchive&)`.

For example:
```cpp
// Serialize integral type:
int a = 5;
BinaryArchive& archive;
Serializer::Serialize(a, archive);

// Deserialize integral type:
int b;
Serializer::Deserialize(b, archive);

// Serialize serializable entity:
auto person = Person("Roman");
Serializer::Serialize(person, archive);

// Deserialize serializable entity:
auto person = Person();
Serializer::Deserialize(person, archive);

// Serialize shared_ptr<Person>:
auto person = std::make_shared<Person>("Roman");
Serializer::Serialize(person, archive);

// Deserialize shared_ptr<Person>:
auto person = std::shared_ptr<Person>();
Serializer::Deserialize(person, archive);

// etc
```

Serializable entities must provide default constructor for deserialization.
`CppUtils::Serialization::Serializer` recursively serializes and deserializes data structures.
This class is thread-safe.

### CppUtils::Serialization::BinaryArchive
`CppUtils::Serialization::BinaryArchive` is a binary data buffer that is used for serialization and deserialization.
This class isn't thread-safe.

## Hashing
Hashing represents `CppUtils::Hashing::Hasher` interface and two implementations: `CppUtils::Hashing::MD5Hasher` and `CppUtils::Hashing::SHA256Hasher`.
This interface declares the only virtual method `std::vector<unsigned char> Hasher::Hash(const std::vector<unsigned char>& input)`. 

## Encryption
Encryption represents `CppUtils::Encryption::Encryptor` interface, `CppUtils::Encryption::AbstractEncryptor` base class and one implementation: `CppUtils::Encryption::AES256Encryptor` which uses ECB variant of AES encryption.
This interface declares two virtual methods `std::vector<unsigned char> Encryptor::Encrypt(const std::vector<unsigned char>& input)` and `std::vector<unsigned char> Encryptor::Decrypt(const std::vector<unsigned char>& input)`.

## Synchronization
Synchronization represents 'CppUtils::Synchronization::CountDownLatch' class which is similar to Java's latch implementation.

## Logging
Singleton class `CppUtils::Logger` provides 4 static methods depending on level of each log:

```cpp
  template <typename... Args>
  static void Information(fmt::format_string<Args...> fmt, Args&&... args);

  template <typename... Args>
  static void Warning(fmt::format_string<Args...> fmt, Args&&... args);

  template <typename... Args>
  static void Error(fmt::format_string<Args...> fmt, Args&&... args);

  template <typename... Args>
  static void Critical(fmt::format_string<Args...> fmt, Args&&... args);
```
Example:

```cpp
Logger::Warning("Something goes not as it should be: {}", reason);
```

In general, `CppUtils::Logger` methods' parameters are same as in `spdlog` library, because `CppUtils::Logger` actually uses `spdlog` lib. 

## Files
`CppUtils::Files` is a helper class that implements simple filesystem actions, such as directory creation, removing, existing check.

## Thread pool
`CppUtils::ThreadPool` is a singleton class that provides common primitive thread pool with the only `void ThreadPool::AcceptTask()` method.
Thread-safe class.
