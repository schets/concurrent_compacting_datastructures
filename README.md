# concurrent_compacting_datastructures
Eventually, this repository will contain a set of single-writer datastructures backed by a concurrent pauseless GC.

This GC will be designed so that it doesn't have to scan the stack or registers, at a marignally increased cost of swapping and occasionaly 'pauses' if the mutator writes to a page that is currently being collected.
