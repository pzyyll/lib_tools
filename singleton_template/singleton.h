//
// @ Create by CaiZhili on 2017/7/17
// @ Brief simple singleton template
//
#ifndef LIB_TOOLS_SIGNLETON_H
#define LIB_TOOLS_SIGNLETON_H

namespace lib_tools {


template <typename T>
class singleton {
public:
    static T& get_mutable_instance() {
        return get_instance();
    }

    static const T& get_const_instance() {
        return get_instance();
    }

private:
    singleton(const singleton&);
    singleton& operator=(const singleton&);

private:
    static T& instance;
    static void use(T const *) {}
    static T& get_instance() {
        static T t;
        use(&t);
        return t;
    };
};

template <typename T>
T& singleton<T>::instance = singleton<T>::get_instance();


} //namespace lib_tools

#endif //LIB_TOOLS_SIGNLETON_H
