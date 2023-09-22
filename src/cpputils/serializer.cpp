#include "serializer.h"

namespace CppUtils {
const int Serializer::UNDEFINED_REFERENCE_INDEX = -1;
const int Serializer::UNDEFINED_OBJECT_UNIQUE_ID = -1;

thread_local int Serializer::referenceCount = 0;

thread_local long long Serializer::initialStackFrameMarker = 0;

thread_local std::map<std::shared_ptr<void>, int> Serializer::referenceMap;
thread_local std::map<int, std::shared_ptr<void>>
    Serializer::reverseReferenceMap;
}  // namespace CppUtils
