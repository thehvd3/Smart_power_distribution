# Smart_power_distribution

Overview:
This project simulates a real-world scenario where a power network of multiple cities (stations) and transmission lines is vulnerable to selective line tripping. The aim is to:

(1). Maximize power disbalance by tripping selected lines under strict constraints.
(2). Ensure minimal wiring cost when initially connecting the network (via MST).

This project combines Dynamic Programming and Graph Algorithms (Kruskal's MST) for an efficient and realistic simulation of grid operations.

Motivation: Why This Project?
This project aims to simulate the potential behavior of an attacker trying to disrupt a power system by tripping a strategic subset of lines. By thinking from the attacker’s perspective — much like how police try to think like a thief — we can better understand vulnerabilities in our grid and work on strengthening it proactively.
The dynamic programming problem models a controlled, constrained attack on power lines to cause maximum disbalance, helping us identify which system weaknesses need mitigation. The long-term goal is to create smarter, more resilient power systems that are harder to exploit.
This simulation can serve as a blueprint for planning resilient smart grids or testing vulnerability in critical infrastructure systems.

While the first part of the project focused on identifying vulnerabilities through adversarial modeling, the second part addresses a more fundamental engineering problem:How do we initially build a power distribution network that connects all cities with minimum cost and redundancy?

In large-scale infrastructure projects (like rural electrification or smart grid expansion), planners must choose how to wire cities or substations so that:

(a) All regions get power,
(b) Costs are minimized, and
(c) There’s no unnecessary duplication of connections.

This is a classic case for applying the Minimum Spanning Tree (MST) algorithm. It ensures that every node (city/station) is connected at the lowest total wiring cost, with no cycles — exactly what real-world grid designers aim for during initial rollout or expansion phases.
This simulation can help utility companies or city planners visualize wiring plans, budget for connection costs, and create a baseline before integrating additional layers like redundancy or fault-tolerance.


1.) Part 1: Dynamic Programming Model — Lines Tripping System

Problem Context:

n power stations, each with m transmission lines

A 3D matrix g[i][j][t] defines the disbalance caused by tripping the j-th line of station i at time t

We can trip up to pos lines, but:

Can't trip all lines of any station

Can't trip all pos lines at once

Forbidden pairs (station, line) must be skipped

Each station i has a maximum trippable lines a[i]

DP State Definition

dp[i][j][t] = max disbalance after considering first i stations,
              tripping j lines in total,
              and currently at time t

Transition Logic

Loop over each station i, each line k, and time step t:

if ((i, k) not forbidden and a[i] not exceeded):
    dp[i][j+1][t+1] = max(dp[i][j+1][t+1], dp[i-1][j][t] + g[i][k][t+1]);

Complexity
Time: O(n × pos × T × m)
Space: O(n × pos × T) — can be optimized via state compression

⚡ Part 2: N-City Electricity Optimization — Minimum Cost Wiring

Problem:

Given n cities and e edges (potential wires) with weights (costs), connect all cities:

With minimal total cost

Without cycles (i.e., a tree)

Algorithm Used: Kruskal's MST

Sort edges by cost

Use Disjoint Set Union (DSU) to avoid cycles

Add edges if endpoints are in different sets

⏱️ Complexity
Time: O(E log E) using sorted edges and DSU

Logic:
We look at the cities as node and the main idea was to assume a new node and call it node-0.
This node acts as Main power station and if add a new power station in a city we basically connect that city to this node-0 and this connection cost = cost of making a power station in that particular city( = city[i])
Overall the whole graph have n+1 nodes and all nodes have edges connecting one another from here on its a Minimum Spamming Tree execution on this graph.
