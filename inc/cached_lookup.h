#pragma once
#include <unordered_map>

#define M_PIl   3.141592653589793238462643383279502884L /* pi */

template<class U, class V> using Cache = std::unordered_map<U, V>;

struct LookUpCache
{
	Cache<float, float> cache_sin, cache_dBm2Watt, cache_Watt2dBm, cache_dB2lin, cache_lin2dB, cache_pow, cache_deg2rad;

	inline double deg2rad(const double& deg)
	{
		auto ite = cache_deg2rad.find(deg);
		if (ite == cache_deg2rad.end())
		{
			double answer = deg * M_PIl / 180.0;
			cache_deg2rad.emplace(deg, answer);
			return answer;
		}

		return ite->second;
	}

	inline std::vector<double> deg2rad(const std::vector<double>& deg_values)
	{
		std::vector<double> output(deg_values.size());

		for (size_t idx = 0; idx < output.size(); ++idx)
		{
			output[idx] = deg2rad(deg_values[idx]);
		}

		return output;
	}

	inline double pow_2(const double& base)
	{
		auto ite = cache_pow.find(base);
		if (ite == cache_pow.end())
		{
			double answer = pow(base, 2);
			cache_pow.emplace(base, answer);
			return answer;
		}

		return ite->second;
	}

	inline double lin2dB(const double& lin)
	{
		auto ite = cache_lin2dB.find(lin);
		if (ite == cache_lin2dB.end())
		{
			double answer = 10 * log10(lin);
			cache_lin2dB.emplace(lin, answer);
			return answer;
		}

		return ite->second;
	}

	inline double log2lin(double log)
	{
		auto ite = cache_dB2lin.find(log);
		if (ite == cache_dB2lin.end())
		{
			double answer = pow(10, log / 10);
			cache_dB2lin.emplace(log, answer);
			return answer;
		}

		return ite->second;
	}

	inline double watt2dBm(const float& watt)
	{
		auto ite = cache_Watt2dBm.find(watt);
		if (ite == cache_Watt2dBm.end())
		{
			double answer = lin2dB(watt) + 30;
			cache_Watt2dBm.emplace(watt, answer);
			return answer;
		}

		return ite->second;
	}

	inline double dBm2watt(double dBm)
	{
		auto ite = cache_dBm2Watt.find(dBm);
		if (ite == cache_dBm2Watt.end())
		{
			double answer = log2lin(dBm - 30);
			cache_dBm2Watt.emplace(dBm, answer);
			return answer;
		}

		return ite->second;
	}

	inline std::vector<double> dBm2watt(const std::vector<double>& dbm_values)
	{
		std::vector<double> output(dbm_values.size());

		for (size_t idx = 0; idx < output.size(); ++idx)
		{
			output[idx] = dBm2watt(dbm_values[idx]);
		}

		return output;
	}

	inline double sin(const double& rads)
	{
		auto ite = cache_sin.find(rads);
		if (ite != cache_sin.end())
		{
			return ite->second;
		}
		else
		{
			double val = std::sin(rads);
			cache_sin.emplace(rads, val);
			return val;
		}
	}

	inline double cos(const double& rads)
	{
		return this->sin((M_PIl / 2.0) - rads);
	}
};

namespace rf_math
{
	constexpr inline double rad2deg(const double& rad)
	{
		return rad * 180.0 / M_PIl;
	}

	constexpr inline double deg2rad(const double& deg)
	{
		return deg * M_PIl / 180.0;
	}

	inline std::vector<double> deg2rad(const std::vector<double>& deg_values)
	{
		std::vector<double> output(deg_values.size());

		for (size_t idx = 0; idx < output.size(); ++idx)
		{
			output[idx] = deg2rad(deg_values[idx]);
		}

		return output;
	}

	inline double pow_2(const double& base)
	{
		return pow(base, 2);
	}

	inline double log2lin(const double& log)
	{
		return pow(10, log / 10);
	}

	inline double lin2dB(const double& lin)
	{
		return 10 * log10(lin);
	}

	inline double dBm2watt(const double& dBm)
	{
		return log2lin(dBm - 30);
	}

	inline std::vector<double> dBm2watt(const std::vector<double>& dbm_values)
	{
		std::vector<double> output(dbm_values.size());

		for (size_t idx = 0; idx < output.size(); ++idx)
		{
			output[idx] = dBm2watt(dbm_values[idx]);
		}

		return output;
	}

	inline double watt2dBm(const double& lin)
	{
		return lin2dB(lin) + 30;
	}
}