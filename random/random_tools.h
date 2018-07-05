// random_tools.h
// @date 2018-6-5
// @author Caizhili
// @brief
#ifndef LIB_TOOLS_RANDOM_TOOLS_H
#define LIB_TOOLS_RANDOM_TOOLS_H

#include <algorithm>
#include <random>
#include <vector>
#include <set>
#include <thread>
#include <mutex>
#include <cassert>

namespace lib_tools {


class Random
{
public:
	template <typename T = int>
	static T RandInt(const T min, const T max) {
		std::uniform_int_distribution<T> dist(min, max);
        std::unique_lock<std::mutex> lock(GetMutex());
		return dist(GetEngine());
	}

	template <typename T>
	static void Shuffle(T begin, T end) {
		std::shuffle(begin, end);
	}

	static bool BernoulliDist(double p) {
		std::bernoulli_distribution dist(p);
        std::unique_lock<std::mutex> lock(GetMutex());
		return dist(GetEngine());
	}

	template <typename InputIt>
	static unsigned DiscreteDist(InputIt begin, InputIt end) {
		std::discrete_distribution<unsigned> dist(begin, end);
        std::unique_lock<std::mutex> lock(GetMutex());
		return dist(GetEngine());
	}

	template <typename T>
	static T DiscreteDist(
		const std::vector<T> &vals,
		const std::vector<double> &weights
	) {
		std::vector<double> tmp_ws = weights;
		while (tmp_ws.size() < vals.size())
			tmp_ws.push_back(0);

		if (vals.size() < tmp_ws.size())
			tmp_ws.resize(vals.size());

		unsigned idx = DiscreteDist(tmp_ws.begin(), tmp_ws.end());

		return vals[idx];
	}

	//@brief 根据权重不放回随机抽样
	//@param population 提供的抽样数据
	//@param weights 对应抽样数据权重
	//@param count 从提供的抽样数据中抽取的个数
	//@return 抽样结果
	template <typename Set>
	static std::vector<typename Set::value_type> RandomSample(
		const Set &population,
		const std::vector<double> &weights,
		const unsigned count
	) {
		assert(population.size() == weights.size());
		assert(population.size() > 0);

		std::vector<typename Set::value_type> results;

		std::vector<typename Set::value_type> tmp_vals(population.begin(), population.end());
		std::vector<double> tmp_ws(weights.begin(), weights.end());

		for (unsigned i = 0;
			i < count &&
			tmp_vals.size() > 0 &&
			tmp_ws.size() > 0;
			++i) {

			unsigned idx = DiscreteDist(tmp_ws.begin(), tmp_ws.end());
			unsigned res_val = tmp_vals[idx];
			results.push_back(res_val);
			tmp_vals.erase(tmp_vals.begin() + idx);
			tmp_ws.erase(tmp_ws.begin() + idx);
		}

		return results;
	}

private:
	template <typename T>
	static void Use(const T &use) { (void)(use); }

	static std::mt19937 &GetEngine() {
		static std::mt19937 engine(static_cast<unsigned>(time(NULL)));
		Use(engine);
		return engine;
	}

	static std::mutex &GetMutex() {
		static std::mutex mutex;
		Use(mutex);
		return mutex;
	}

	static std::mt19937 &_engine;
	static std::mutex &_mutex;
};



} //namespace lib_tools

#endif //LIB_TOOLS_RANDOM_TOOLS_H
