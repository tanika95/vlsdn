#include "Netcontrol.hh"
#include "Common.hh"
#include "Controller.hh"

REGISTER_APPLICATION(Netcontrol, {"controller", "switch-manager", "link-discovery", ""})

using namespace runos;
using namespace std;

void Netcontrol::init(Loader *loader, const Config &config)
{
    	Controller* ctrl = Controller::get(loader);
    	cout << "Netcontrol init";
    	auto table = ctrl->getTable("netcontrol");

	auto vlconf = VlConfig("path");
	topo = NetTopology(vlconf->info());

    	auto swmanager = SwitchManager::get(loader);
    	connect(
            	swmanager, &SwitchManager::switchDiscovered,
            	this, &Netcontrol::switchDiscovered
    	);
    	connect(
            	swmanager, &SwitchManager::switchDown,
            	this, &Netcontrol::switchBroken
    	);

        auto lmanager = ILinkDiscovery::get(loader);
        connect(
                lmanager, SIGNAL(linkDiscovered(switch_and_port, switch_and_port)),
                this, SLOT(linkDiscovered(switch_and_port, switch_and_port))
        );
}

void Netcontrol::switchDiscovered(Switch *sw)
{
        cout << "Switch " << sw->id() << " up";
        topo = topo.withSwitch(sw->id());
        topo.log();
}

void Netcontrol::switchBroken(Switch *sw)
{
        cout << "Switch " << sw->id() << " down";
        topo = topo.withoutSwitch(sw->id());
        topo.log();
}

void Netcontrol::linkDiscovered(switch_and_port from, switch_and_port to)
{
        cout << "Link discovered";
        topo = topo->withLink(NetLink(from.dpid, from.port, to.dpid, to.port));
}
