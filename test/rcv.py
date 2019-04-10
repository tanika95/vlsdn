from scapy.all import *
from datetime import *
import os
import sys
import time


import pcapy as pcap
conf.use_pcap=True

fname = sys.argv[1]
result = {}

def addEntry(p):
	timestamp = datetime.now()
	try:
		num = int(p.load[:8])
		result.setdefault(p.vlan, []).append((num, timestamp.strftime("%S.%f")))
	except:
		pass

sniff(prn=addEntry, count=100)

f = open(fname, 'w')
for flow in result:
	f.write(str(flow) + "\n")
	f.write('----------\n')
	for packet in result[flow]:
		num = str(packet[0])
		timestamp = packet[1]
		f.write(num + ' ' + timestamp + '\n')