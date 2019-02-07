#pragma once
#include <map>
#include <tuple>
#include <stdint.h>
#include "VlConfig.hh"

typedef std::pair<uint32_t, uint32_t> LinkInfo;

class BandwidthInfo {
public:
	BandwidthInfo(const std::map<LinkInfo, double> &banwidth);

	double getBanwidth(uint32_t sender, uint32_t receiver) const;
private:
	std::map<LinkInfo, double> banwidth;
};
