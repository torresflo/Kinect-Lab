#ifndef UTILS_NONCOPYABLE_HPP
#define UTILS_NONCOPYABLE_HPP

namespace Utils
{

class NonCopyable
{
protected:
    NonCopyable() {}

private:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator= (const NonCopyable&) = delete;
};

} //namespace Utils

#endif //UTILS_NONCOPYABLE_HPP
