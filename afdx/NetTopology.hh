#pragma once

#include <map>
#include <memory>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "BandwidthInfo.hh"
#include "NetHost.hh"
#include "NetInfo.hh"
#include "NetLink.hh"
#include "NetSwitch.hh"
#include "Vl.hh"
#include "VlState.hh"
#include "VlSwitch.hh"

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
	boost::no_property, boost::property<boost::edge_weight_t, double> > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::pair<int, int> Edge;
typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

class NetTopology {
public:
	NetTopology(const NetInfo &info);

	NetTopology &withSwitch(uint32_t id);
	NetTopology &withoutSwitch(uint32_t id);
	NetTopology &withHost(uint32_t id);
	NetTopology &withoutHost(uint32_t id);
	NetTopology &withLink(const NetLink &link);
	NetTopology &withoutLink(const NetLink &link);
	NetTopology &withHostLink(uint32_t hid, uint32_t sid);
	NetTopology &withoutHostLink(uint32_t hid, uint32_t sid);

	Graph graphForVl(const Vl &vl, const BandwidthInfo &bws) const;
	std::vector<VlSwitch> routeForVl(const std::vector<uint32_t> &route) const;
	std::vector<VlState> brokenVls(const VlSet &vls) const;

	void log() const;
	bool isFull() const;

private:
	uint32_t linksAmount() const;

	std::map<uint32_t, NetHost> hosts;
	std::map<uint32_t, NetSwitch> switches;
	NetInfo info;
};
