// random_tools.cpp
// @date 2018-6-5
// @author Caizhili
// @brief


#include "random_tools.h"

namespace lib_tools {



std::mt19937 &Random::_engine = Random::GetEngine();
std::mutex &Random::_mutex = Random::GetMutex();



} //namespace lib_tools
