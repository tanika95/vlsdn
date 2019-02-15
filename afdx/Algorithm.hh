#pragma once

#include <boost/property_map/property_map.hpp>
#include "NetTopology.hh"
#include "Vl.hh"

class Algorithm {
public:
	Algorithm(const VlSet &vls, const NetTopology &topo);
	VlSet run();
	VlSet initial();

private:
	VlSet links;
	NetTopology map;

	VlSet baseStep(VlSet links);
	VlSet additionalStep();
	Vl searchPath(const Vl &vl, uint32_t from, uint32_t to);
};
