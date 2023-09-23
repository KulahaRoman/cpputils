#include <cpputils/logger.h>
#include <cpputils/serializable.h>
#include <cpputils/serializer.h>
#include <gtest/gtest.h>

using namespace CppUtils;

enum class Answer { NONE, YES, NO };

TEST(SerilizerTest, Enum) {
  auto out = Answer::YES;

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  auto in = Answer::NONE;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, String) {
  std::string out{"Hello, World!"};

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::string in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Wstring) {
  std::wstring out{L"Hello, World!"};

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::wstring in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Array) {
  std::array<int, 5> out{0, 1, 2, 3, 4};

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::array<int, 5> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Pair) {
  std::pair<int, std::string> out{5, "Machine"};

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::pair<int, std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Map) {
  std::map<int, std::string> out;
  out.emplace(0, "Roman");
  out.emplace(1, "Anton");
  out.emplace(2, "Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::map<int, std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, UnorderedMap) {
  std::unordered_map<int, std::string> out;
  out.emplace(0, "Roman");
  out.emplace(1, "Anton");
  out.emplace(2, "Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::unordered_map<int, std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Set) {
  std::set<std::string> out;
  out.emplace("Roman");
  out.emplace("Anton");
  out.emplace("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::set<std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, UnorderedSet) {
  std::unordered_set<std::string> out;
  out.emplace("Roman");
  out.emplace("Anton");
  out.emplace("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::unordered_set<std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Queue) {
  std::queue<std::string> out;
  out.emplace("Roman");
  out.emplace("Anton");
  out.emplace("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::queue<std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Deque) {
  std::deque<std::string> out;
  out.emplace_back("Roman");
  out.emplace_back("Anton");
  out.emplace_back("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::deque<std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, List) {
  std::list<std::string> out;
  out.emplace_back("Roman");
  out.emplace_back("Anton");
  out.emplace_back("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::list<std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Vector) {
  std::vector<std::string> out;
  out.emplace_back("Roman");
  out.emplace_back("Anton");
  out.emplace_back("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::vector<std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

//         Objects hierarchy
//
//         .->--Person-->-.
//         |              |
//         |              |
//         .-<--Person--<-.

class Person : public Serializable {
 public:
  Person() { Logger::Information("Class Person constructed."); }
  Person(const std::string& name,
         const std::shared_ptr<Person>& bestie = nullptr)
      : name(name), bestie(bestie) {
    Logger::Information("Class Person constructed with arguments ({}).", name);
  }
  ~Person() { Logger::Information("Class Person destructed."); }

  std::string GetName() const { return name; }
  void SetName(const std::string& name) { this->name = name; }

  std::shared_ptr<Person> GetBestie() const { return bestie.lock(); }
  void SetBestie(const std::shared_ptr<Person>& bestie) {
    this->bestie = bestie;
  }

  void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(name, archive);
    Serializer::Serialize(bestie, archive);
  }
  void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(name, archive);
    Serializer::Deserialize(bestie, archive);

    CYCLIC_WEAK_REFERENCE(bestie)
  }

 private:
  std::string name;
  std::weak_ptr<Person> bestie;
};

TEST(SerializerTest, TwoFriendsCyclicReferences) {
  auto first = std::make_shared<Person>("Roman");
  auto second = std::make_shared<Person>("Anton");

  first->SetBestie(second);
  second->SetBestie(first);

  BinaryArchive archive;
  Serializer::Serialize(first, archive);

  auto person = std::shared_ptr<Person>();
  Serializer::Deserialize(person, archive);

  ASSERT_STREQ(person->GetName().c_str(), first->GetName().c_str());
  ASSERT_STREQ(person->GetBestie()->GetName().c_str(),
               second->GetName().c_str());
}

//       Objects hierarchy
//
//          .->-A>----.
//          |   |     |
//          .---B     |
//             / \    |
//            C   D   |
//            |   |   |
//            E-<-F-<-.
//

class E : public Serializable {
 public:
  E() : num(0) { Logger::Information("Class E constructed."); }
  E(int num) : num(num) {
    Logger::Information("Class E constructed with arguments.");
  }
  ~E() { Logger::Information("Class E destructed."); }

  void SetNumber(int num) { this->num = num; }
  int GetNumber() const { return num; }

  virtual void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(num, archive);
  }
  virtual void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(num, archive);
  }

 private:
  int num;
};

class F : public Serializable {
 public:
  F() : num(0) { Logger::Information("Class F constructed."); }
  F(int num, const std::shared_ptr<E>& e) : num(num), e(e) {
    Logger::Information("Class F constructed with arguments.");
  }
  ~F() { Logger::Information("Class F destructed."); }

  void SetNumber(int num) { this->num = num; }
  int GetNumber() const { return num; }

  void SetE(const std::shared_ptr<E>& f) { this->e = e; }
  std::shared_ptr<E> GetE() const { return e; }

  virtual void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(num, archive);
    Serializer::Serialize(e, archive);
  }
  virtual void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(num, archive);
    Serializer::Deserialize(e, archive);
  }

 private:
  int num;
  std::shared_ptr<E> e;
};

class D : public Serializable {
 public:
  D() { Logger::Information("Class D constructed."); }
  D(const std::shared_ptr<F>& f) : f(f) {
    Logger::Information("Class D constructed with arguments.");
  }
  ~D() { Logger::Information("Class D destructed."); }

  void SetF(const std::shared_ptr<F>& f) { this->f = f; }
  std::shared_ptr<F> GetF() const { return f; }

  virtual void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(f, archive);
  }
  virtual void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(f, archive);
  }

 private:
  std::shared_ptr<F> f;
};

class C : public Serializable {
 public:
  C() { Logger::Information("Class C constructed."); }
  C(const std::shared_ptr<E>& e) : e(e) {
    Logger::Information("Class C constructed with arguments.");
  }
  ~C() { Logger::Information("Class C destructed."); }

  void SetE(const std::shared_ptr<E>& e) { this->e = e; }
  std::shared_ptr<E> GetE() const { return e; }

  virtual void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(e, archive);
  }
  virtual void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(e, archive);
  }

 private:
  std::shared_ptr<E> e;
};

class A;

class B : public Serializable {
 public:
  B() { Logger::Information("Class B constructed."); }
  B(const std::shared_ptr<C>& c, const std::shared_ptr<D>& d) : c(c), d(d) {
    Logger::Information("Class B constructed with arguments.");
  }
  ~B() { Logger::Information("Class B destructed."); }

  void SetA(const std::shared_ptr<A>& a) { this->a = a; }
  std::shared_ptr<A> GetA() const { return a.lock(); }

  void SetC(const std::shared_ptr<C>& c) { this->c = c; }
  std::shared_ptr<C> GetC() const { return c; }

  void SetD(const std::shared_ptr<D>& d) { this->d = d; }
  std::shared_ptr<D> GetD() const { return d; }

  virtual void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(a, archive);
    Serializer::Serialize(c, archive);
    Serializer::Serialize(d, archive);
  }
  virtual void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(a, archive);
    Serializer::Deserialize(c, archive);
    Serializer::Deserialize(d, archive);
  }

 private:
  std::weak_ptr<A> a;
  std::shared_ptr<C> c;
  std::shared_ptr<D> d;
};

class A : public Serializable {
 public:
  A() { Logger::Information("Class A constructed."); }
  A(const std::shared_ptr<B>& b, const std::shared_ptr<F>& f) : b(b), f(f) {
    Logger::Information("Class A constructed with arguments.");
  }
  ~A() { Logger::Information("Class A destructed."); }

  void SetB(const std::shared_ptr<B>& b) { this->b = b; }
  std::shared_ptr<B> GetB() const { return b; }

  void SetF(const std::shared_ptr<F>& f) { this->f = f; }
  std::shared_ptr<F> GetF() const { return f; }

  virtual void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(b, archive);
    Serializer::Serialize(f, archive);
  }
  virtual void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(b, archive);
    Serializer::Deserialize(f, archive);
  }

 private:
  std::shared_ptr<B> b;
  std::shared_ptr<F> f;
};

TEST(SerializerTest, ComplicatedCyclicReferences) {
  auto eOut = std::make_shared<E>(2);
  auto fOut = std::make_shared<F>(1, eOut);

  auto cOut = std::make_shared<C>(eOut);
  auto dOut = std::make_shared<D>(fOut);

  auto bOut = std::make_shared<B>(cOut, dOut);

  auto aOut = std::make_shared<A>(bOut, fOut);

  bOut->SetA(aOut);

  BinaryArchive archive;
  Serializer::Serialize(aOut, archive);

  auto aIn = std::shared_ptr<A>();
  Serializer::Deserialize(aIn, archive);

  ASSERT_EQ(aIn->GetB()->GetC()->GetE()->GetNumber(), eOut->GetNumber());
  ASSERT_EQ(aIn->GetB()->GetD()->GetF()->GetNumber(), fOut->GetNumber());
  ASSERT_EQ(aIn->GetB()->GetD()->GetF()->GetE()->GetNumber(),
            eOut->GetNumber());
}
