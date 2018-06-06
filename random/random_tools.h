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

namespace lib_tools {


class Random
{
public:
	template <typename T = int>
	static T RandInt(const T min, const T max) {
		std::uniform_int_distribution<T> dist(min, max);
		return dist(engine);
	}

	template <typename T>
	static void Shuffle(T begin, T end) {
		std::shuffle(begin, end);
	}

	static bool BernoulliDist(double p) {
		std::bernoulli_distribution dist(p);
		return dist(engine);
	}

	template <typename InputIt>
	static unsigned DiscreteDist(InputIt begin, InputIt end) {
		std::discrete_distribution<unsigned> dist(begin, end);
		return dist(engine);
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
	//@param vals 提供的抽样数据
	//@param weights 对应抽样数据权重
	//@param count 从提供的抽样数据中抽取的个数
	//@return 抽样结果
	template <typename T>
	static std::vector<T> RandomSample(
		const std::vector<T> &vals,
		const std::vector<double> &weights,
		const unsigned count
	) {
		std::vector<T> results;

		if (vals.size() <= 0) {
			return results;
		}

		std::vector<T> tmp_vals = vals;
		std::vector<double> tmp_ws = weights;

		while (tmp_ws.size() < vals.size())
			tmp_ws.push_back(0);

		if (vals.size() < tmp_ws.size())
			tmp_ws.resize(vals.size());

        std::set<unsigned> check;
		for (unsigned i = tmp_ws.size() - count + 1; i <= tmp_ws.size();++i) {
			unsigned idx = DiscreteDist(tmp_ws.begin(), tmp_ws.begin() + i);
			if (check.find(idx) != check.end()) {
                results.push_back(tmp_vals[i - 1]);
            } else {
                results.push_back(tmp_vals[idx]);
                check.insert(idx);
            }
		}

		return results;
	}

    template <typename T>
	static std::vector<T> RandomSample2(
		const std::vector<T> &vals,
		const std::vector<double> &weights,
		const unsigned count
	) {
		std::vector<T> results;

		if (vals.size() <= 0) {
			return results;
		}

		std::vector<T> tmp_vals = vals;
		std::vector<double> tmp_ws = weights;

		while (tmp_ws.size() < vals.size())
			tmp_ws.push_back(0);

		if (vals.size() < tmp_ws.size())
			tmp_ws.resize(vals.size());

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

	static std::mt19937 engine;
};

std::mt19937 Random::engine(static_cast<unsigned>(time(NULL)));


} //namespace lib_tools

#endif //LIB_TOOLS_RANDOM_TOOLS_H

