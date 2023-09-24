#include <cpputils/logger.h>
#include <cpputils/serializable.h>
#include <cpputils/serializer.h>
#include <gtest/gtest.h>

using namespace CppUtils::Serialization;

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

TEST(SerilizerTest, MultiMap) {
  std::multimap<int, std::string> out;
  out.emplace(0, "Roman");
  out.emplace(0, "James");
  out.emplace(1, "Anton");
  out.emplace(1, "John");
  out.emplace(2, "Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::multimap<int, std::string> in;
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

TEST(SerilizerTest, UnorderedMultiMap) {
  std::unordered_multimap<int, std::string> out;
  out.emplace(0, "Roman");
  out.emplace(0, "James");
  out.emplace(1, "Anton");
  out.emplace(1, "John");
  out.emplace(2, "Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::unordered_multimap<int, std::string> in;
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

TEST(SerilizerTest, MultiSet) {
  std::multiset<std::string> out;
  out.emplace("Roman");
  out.emplace("Roman");
  out.emplace("Roman");
  out.emplace("James");
  out.emplace("Anton");
  out.emplace("Anton");
  out.emplace("Anton");
  out.emplace("John");
  out.emplace("John");
  out.emplace("John");
  out.emplace("Ivan");
  out.emplace("Ivan");
  out.emplace("Ivan");
  out.emplace("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::multiset<std::string> in;
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

TEST(SerilizerTest, UnorderedMultiSet) {
  std::unordered_multiset<std::string> out;
  out.emplace("Roman");
  out.emplace("Roman");
  out.emplace("Roman");
  out.emplace("James");
  out.emplace("Anton");
  out.emplace("Anton");
  out.emplace("Anton");
  out.emplace("John");
  out.emplace("John");
  out.emplace("John");
  out.emplace("Ivan");
  out.emplace("Ivan");
  out.emplace("Ivan");
  out.emplace("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::unordered_multiset<std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out == in);
}

TEST(SerilizerTest, Stack) {
  std::stack<std::string> out;
  out.emplace("Roman");
  out.emplace("Anton");
  out.emplace("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::stack<std::string> in;
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

TEST(SerilizerTest, PriorityQueue) {
  std::priority_queue<std::string> out;
  out.emplace("Roman");
  out.emplace("Anton");
  out.emplace("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::priority_queue<std::string> in;
  Serializer::Deserialize(in, archive);

  ASSERT_TRUE(out.size() == in.size());

  while (!in.empty()) {
    auto outElem = out.top();
    auto inElem = in.top();

    out.pop();
    in.pop();

    ASSERT_TRUE(outElem == inElem);
  }
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

TEST(SerilizerTest, ForwardList) {
  std::forward_list<std::string> out;
  out.emplace_front("Roman");
  out.emplace_front("Anton");
  out.emplace_front("Ivan");

  BinaryArchive archive;
  Serializer::Serialize(out, archive);

  std::forward_list<std::string> in;
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

unsigned int personConstructedCounter = 0;
unsigned int personDestructedCounter = 0;

class Person : public Serializable {
 public:
  Person() { personConstructedCounter++; }
  Person(const std::string& name,
         const std::shared_ptr<Person>& bestie = nullptr)
      : name(name), bestie(bestie) {
    personConstructedCounter++;
  }
  ~Person() { personDestructedCounter++; }

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
  {
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

  ASSERT_TRUE((personConstructedCounter == personDestructedCounter) &&
              personConstructedCounter > 1);
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
//            |
//            G

unsigned int gConstructedCounter = 0;
unsigned int gDestructedCounter = 0;

class G : public Serializable {
 public:
  G() : num(0) { gConstructedCounter++; }
  G(int num) : num(num) { gConstructedCounter++; }
  ~G() { gDestructedCounter++; }

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

unsigned int eConstructedCounter = 0;
unsigned int eDestructedCounter = 0;

class E : public Serializable {
 public:
  E() : num(0) { eConstructedCounter++; }
  E(int num, std::unique_ptr<G>&& g) : num(num), g(std::move(g)) {
    eConstructedCounter++;
  }
  ~E() { eDestructedCounter++; }

  void SetNumber(int num) { this->num = num; }
  int GetNumber() const { return num; }

  virtual void Serialize(BinaryArchive& archive) const override {
    Serializer::Serialize(num, archive);
    Serializer::Serialize(g, archive);
  }
  virtual void Deserialize(BinaryArchive& archive) override {
    Serializer::Deserialize(num, archive);
    Serializer::Deserialize(g, archive);
  }

 private:
  int num;
  std::unique_ptr<G> g;
};

unsigned int fConstructedCounter = 0;
unsigned int fDestructedCounter = 0;

class F : public Serializable {
 public:
  F() : num(0) { fConstructedCounter++; }
  F(int num, const std::shared_ptr<E>& e) : num(num), e(e) {
    fConstructedCounter++;
  }
  ~F() { fDestructedCounter++; }

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

unsigned int dConstructedCounter = 0;
unsigned int dDestructedCounter = 0;

class D : public Serializable {
 public:
  D() { dConstructedCounter++; }
  D(const std::shared_ptr<F>& f) : f(f) { dConstructedCounter++; }
  ~D() { dDestructedCounter++; }

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

unsigned int cConstructedCounter = 0;
unsigned int cDestructedCounter = 0;

class C : public Serializable {
 public:
  C() { cConstructedCounter++; }
  C(const std::shared_ptr<E>& e) : e(e) { cConstructedCounter++; }
  ~C() { cDestructedCounter++; }

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

unsigned int bConstructedCounter = 0;
unsigned int bDestructedCounter = 0;

class B : public Serializable {
 public:
  B() { bConstructedCounter++; }
  B(const std::shared_ptr<C>& c, const std::shared_ptr<D>& d) : c(c), d(d) {
    bConstructedCounter++;
  }
  ~B() { bDestructedCounter++; }

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

unsigned int aConstructedCounter = 0;
unsigned int aDestructedCounter = 0;

class A : public Serializable {
 public:
  A() { aConstructedCounter++; }
  A(const std::shared_ptr<B>& b, const std::shared_ptr<F>& f) : b(b), f(f) {
    aConstructedCounter++;
  }
  ~A() { aDestructedCounter++; }

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
  {
    auto&& gOut = std::make_unique<G>(5);
    auto eOut = std::make_shared<E>(2, std::move(gOut));
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

  ASSERT_TRUE((aConstructedCounter == aDestructedCounter) &&
              aConstructedCounter > 1);
  ASSERT_TRUE((bConstructedCounter == bDestructedCounter) &&
              bConstructedCounter > 1);
  ASSERT_TRUE((cConstructedCounter == cDestructedCounter) &&
              cConstructedCounter > 1);
  ASSERT_TRUE((dConstructedCounter == dDestructedCounter) &&
              dConstructedCounter > 1);
  ASSERT_TRUE((eConstructedCounter == eDestructedCounter) &&
              eConstructedCounter > 1);
  ASSERT_TRUE((fConstructedCounter == fDestructedCounter) &&
              fConstructedCounter > 1);
  ASSERT_TRUE((gConstructedCounter == gDestructedCounter) &&
              gConstructedCounter > 1);
}
