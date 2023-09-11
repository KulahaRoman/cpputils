#include <cpputils/logger.h>
#include <cpputils/serializable.h>
#include <cpputils/serializer.h>
#include <gtest/gtest.h>

//              A>----.
//              |     |
//              B     |
//             / \    |
//            C   D   |
//            |   |   |
//            E-<-F-<-.
//

class E : public CppUtils::Serializable {
 public:
  E() : num(0) {}
  E(int num) : num(num) {}

  void SetNumber(int num) { this->num = num; }
  int GetNumber() const { return num; }

  virtual void Serialize(CppUtils::BinaryArchive& archive) const override {
    CppUtils::Serializer::Serialize(num, archive);
  }

  virtual void Deserialize(CppUtils::BinaryArchive& archive) override {
    CppUtils::Serializer::Deserialize(num, archive);
  }

  virtual int GetSerialUID() const override { return 412; }

  Serializable& operator=(const Serializable& other) override {
    auto& ref = static_cast<const E&>(other);
    num = ref.num;
    return *this;
  }

 private:
  int num;
};

class F : public CppUtils::Serializable {
 public:
  F() : num(0) {}
  F(int num, const std::shared_ptr<E>& e) : num(num), e(e) {}

  void SetNumber(int num) { this->num = num; }
  int GetNumber() const { return num; }

  void SetE(const std::shared_ptr<E>& f) { this->e = e; }
  std::shared_ptr<E> GetE() const { return e; }

  virtual void Serialize(CppUtils::BinaryArchive& archive) const override {
    CppUtils::Serializer::Serialize(num, archive);
    CppUtils::Serializer::Serialize(e, archive);
  }

  virtual void Deserialize(CppUtils::BinaryArchive& archive) override {
    CppUtils::Serializer::Deserialize(num, archive);
    CppUtils::Serializer::Deserialize(e, archive);
  }

  virtual int GetSerialUID() const override { return 21412; }

  F& operator=(const F& other) {
    num = other.num;
    e = other.e;
    return *this;
  }

  Serializable& operator=(const Serializable& other) override {
    auto& ref = static_cast<const F&>(other);
    num = ref.num;
    e = ref.e;
    return *this;
  }

 private:
  int num;
  std::shared_ptr<E> e;
};

class D : public CppUtils::Serializable {
 public:
  D() {}
  D(const std::shared_ptr<F>& f) : f(f) {}

  void SetF(const std::shared_ptr<F>& f) { this->f = f; }
  std::shared_ptr<F> GetF() const { return f; }

  virtual void Serialize(CppUtils::BinaryArchive& archive) const override {
    CppUtils::Serializer::Serialize(f, archive);
  }

  virtual void Deserialize(CppUtils::BinaryArchive& archive) override {
    CppUtils::Serializer::Deserialize(f, archive);
  }

  virtual int GetSerialUID() const override { return 214; }

  Serializable& operator=(const Serializable& other) override {
    auto& ref = static_cast<const D&>(other);
    f = ref.f;
    return *this;
  }

 private:
  std::shared_ptr<F> f;
};

class C : public CppUtils::Serializable {
 public:
  C() {}
  C(const std::shared_ptr<E>& e) : e(e) {}

  void SetE(const std::shared_ptr<E>& e) { this->e = e; }
  std::shared_ptr<E> GetE() const { return e; }

  virtual void Serialize(CppUtils::BinaryArchive& archive) const override {
    CppUtils::Serializer::Serialize(e, archive);
  }

  virtual void Deserialize(CppUtils::BinaryArchive& archive) override {
    CppUtils::Serializer::Deserialize(e, archive);
  }

  virtual int GetSerialUID() const override { return 14; }

  Serializable& operator=(const Serializable& other) override {
    auto& ref = static_cast<const C&>(other);
    e = ref.e;
    return *this;
  }

 private:
  std::shared_ptr<E> e;
};

class B : public CppUtils::Serializable {
 public:
  B() {}
  B(const std::shared_ptr<C>& c, const std::shared_ptr<D>& d) : c(c), d(d) {}

  void SetC(const std::shared_ptr<C>& c) { this->c = c; }
  std::shared_ptr<C> GetC() const { return c; }

  void SetD(const std::shared_ptr<D>& d) { this->d = d; }
  std::shared_ptr<D> GetD() const { return d; }

  virtual void Serialize(CppUtils::BinaryArchive& archive) const override {
    CppUtils::Serializer::Serialize(c, archive);
    CppUtils::Serializer::Serialize(d, archive);
  }

  virtual void Deserialize(CppUtils::BinaryArchive& archive) override {
    CppUtils::Serializer::Deserialize(c, archive);
    CppUtils::Serializer::Deserialize(d, archive);
  }

  virtual int GetSerialUID() const override { return 2547; }

  Serializable& operator=(const Serializable& other) override {
    auto& ref = static_cast<const B&>(other);
    c = ref.c;
    d = ref.d;
    return *this;
  }

 private:
  std::shared_ptr<C> c;
  std::shared_ptr<D> d;
};

class A : public CppUtils::Serializable {
 public:
  A() {}
  A(const std::shared_ptr<B>& b, const std::shared_ptr<F>& f) : b(b), f(f) {}

  void SetB(const std::shared_ptr<B>& b) { this->b = b; }
  std::shared_ptr<B> GetB() const { return b; }

  void SetF(const std::shared_ptr<F>& f) { this->f = f; }
  std::shared_ptr<F> GetF() const { return f; }

  virtual void Serialize(CppUtils::BinaryArchive& archive) const override {
    CppUtils::Serializer::Serialize(b, archive);
    CppUtils::Serializer::Serialize(f, archive);
  }
  virtual void Deserialize(CppUtils::BinaryArchive& archive) override {
    CppUtils::Serializer::Deserialize(b, archive);
    CppUtils::Serializer::Deserialize(f, archive);
  }

  virtual int GetSerialUID() const override { return 7; }

  Serializable& operator=(const Serializable& other) override {
    auto& ref = static_cast<const A&>(other);
    b = ref.b;
    f = ref.f;
    return *this;
  }

 private:
  std::shared_ptr<B> b;
  std::shared_ptr<F> f;
};

TEST(SerializerTest, Test) {
  auto e = std::make_shared<E>(2);
  auto f = std::make_shared<F>(1, e);

  auto c = std::make_shared<C>(e);
  auto d = std::make_shared<D>(f);

  auto b = std::make_shared<B>(c, d);

  auto aOut = std::make_shared<A>(b, f);

  CppUtils::BinaryArchive archive;
  CppUtils::Serializer::Serialize(aOut, archive);

  auto aIn = std::shared_ptr<A>();
  CppUtils::Serializer::Deserialize(aIn, archive);

  ASSERT_EQ(aIn->GetB()->GetC()->GetE()->GetNumber(), e->GetNumber());
  ASSERT_EQ(aIn->GetB()->GetD()->GetF()->GetNumber(), f->GetNumber());
  ASSERT_EQ(aIn->GetB()->GetD()->GetF()->GetE()->GetNumber(), e->GetNumber());
}
