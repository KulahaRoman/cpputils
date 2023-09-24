# cpputils
CppUtils library consists of serialization, hashing, encryption, synchronization classes. There is also Logger, ThreadPool, Files singleton classes.

## Serialization
Serialization is implemented by following classes: Serializer, Serializable, BinaryArchive.

### CppUtils::Serialization::Serializable
`CppUtils::Serialization::Serializable` is a base class for entities that should be serialized/deserialzied.
Each derived class must override two virtual methods of base class: `Serializable::Serialize(BinaryArchive&) const` and `Serializable::Deserialize(BinaryArchive&)`.
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

There are two overloaded method templates: `Serializer::Serialize(value, BinaryArchive&)` and `Serializer::Deserialize(value, BinaryArchive&)`.

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

### CppUtils::Serialization::BinaryArchive
`CppUtils::Serialization::BinaryArchive` is a binary data buffer that is used for serialization and deserialization.
