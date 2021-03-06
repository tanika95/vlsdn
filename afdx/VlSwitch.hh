#pragma once
#include <stdint.h>
#include "Common.hh"

struct VlSwitch {
	VlSwitch(uint32_t id, uint32_t sport, uint32_t rport)
		: id(id), sport(sport),  rport(rport)
	{}

	VlSwitch()
		: VlSwitch(0, 0, 0)
	{}

	bool operator !=(const VlSwitch &other) const
	{
		return id != other.id || sport != other.sport || rport != other.rport;
	}

	void log() const
	{
		LOG(INFO) << id << " s" << sport << " r" << rport;

	}

	uint32_t id;
	uint32_t sport;
	uint32_t rport;
};
