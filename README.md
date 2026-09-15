# 3D Ring Network Clockwise Routing Simulator

A C++ simulation framework for directional routing algorithms in a 3D ring network topology. The application calculates primary and backup network paths across rows, columns, and layers, enforcing unidirectional clockwise traversal and verifying path disjointness.

## Features

* **3D Mesh-Ring Topology**: Maps 1D node IDs to 3D spatial coordinates across layers, rows, and columns.


* **Clockwise Ring Routing**: Enforces unidirectional clockwise movement across horizontal, vertical, and spatial dimensions.


* **Primary Route Generation**: Traverses horizontal columns first, then vertical rows, and finally spatial layers.


* **Backup Route Generation**: Traverses spatial layers first, then vertical rows, and finally horizontal columns.


* **Path Disjointness Verification**: Evaluates intermediate path nodes to determine if primary and backup routes overlap.


* **Interactive CLI**: Accepts source and destination node inputs to calculate hops, print path chains, and inspect node coordinates.



## Network Topology Parameters

| Parameter | Default Value | Description |
| --- | --- | --- |
| **Rows ($M$)** | 3 | Number of rows per surface layer
| **Columns ($N$)** | 4 | Number of columns per surface layer
| **Layers ($L$)** | 3 | Number of 2D grid surfaces
| **Total Nodes** | 36 | Total system node capacity ($M \times N \times L$)

## Building & Running

### 1. Compilation

Compile the source code using standard C++ flags:

```bash
g++ -O2 network_3d_routing.cpp -o 3d_router

```

### 2. Execution

Run the compiled binary in your terminal:

```bash
./3d_router

```
