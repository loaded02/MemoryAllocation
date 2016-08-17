# MemoryAllocation
Example on custom StaticMemoryManagement and loss due to Alignment in dynamic allocation

## DynamicAlloc
This Program shows how 3 different threads allocate memory from heap
and where they allocate it from (adresses)
Result: One Integer takes more space than 4 Byte. My system: 32 Byte

## StaticAlloc
Program illustrates how Memory allocation can be handled in an own class.
Allocation from static heap section. Pro: no fragmentation (or better: handle fragmentation on your own!)
This is a simple static Memory management demo which only allocates memory and shows addresses of 
allocated memory by 3 different threads.
