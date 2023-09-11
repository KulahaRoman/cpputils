#include "serializer.h"

namespace CppUtils {
const int Serializer::UNDEFINED_REFERENCE_INDEX = -1;
const int Serializer::UNDEFINED_OBJECT_UNIQUE_ID = -1;

thread_local int Serializer::objectCount = 0;
thread_local std::map<const void*, int> Serializer::referenceMap;
thread_local std::map<int, const void*> Serializer::reverseReferenceMap;
}  // namespace CppUtils
