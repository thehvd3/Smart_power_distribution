<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
<!--   <title>Power Network Vulnerability Simulation and Optimization</title> -->
</head>
<body>
  <h1>Power Network Vulnerability Simulation and Optimization</h1>
  <p>This project simulates a real-world scenario where a power network of multiple cities (stations) and transmission lines is vulnerable to selective line tripping. The goal is to simulate an adversarial model for understanding vulnerabilities in power systems and optimize the initial cost of wiring through graph algorithms.</p>

  <h2>Project Overview</h2>
  <h3>Objective</h3>
  <p>This project combines Dynamic Programming (DP) and Graph Algorithms (Kruskal's Minimum Spanning Tree) to efficiently simulate and optimize the operations of a power network. The simulation helps identify system vulnerabilities by modeling a controlled, constrained attack on power lines and finds an optimal method to wire cities with minimal cost and redundancy.</p>

  <ul>
    <li><strong>Part 1:</strong> <em>Dynamic Programming Model — Lines Tripping System</em>
      <ul>
        <li>Simulate the potential behavior of an attacker trying to disrupt a power system by tripping specific lines.</li>
        <li>Maximize power disbalance while respecting various constraints, such as not being able to trip all lines of a station or all selected lines at once.</li>
        <li>Identify system weaknesses and areas that need improvement.</li>
      </ul>
    </li>
    <li><strong>Part 2:</strong> <em>N-City Electricity Optimization — Minimum Cost Wiring</em>
      <ul>
        <li>Using Kruskal's Minimum Spanning Tree (MST) algorithm, optimize the cost of connecting cities.</li>
        <li>Ensure that all cities are connected, with no redundant wiring, and that the total wiring cost is minimized.</li>
      </ul>
    </li>
  </ul>

  <h2>Motivation</h2>
  <p>This project simulates potential attacks on power systems to better understand vulnerabilities and work proactively to mitigate them. The use of dynamic programming helps identify the optimal way to cause maximum disbalance with minimal line tripping, while Kruskal's MST algorithm is used to simulate the initial cost-efficient wiring of a power network.</p>
  <p>The goal is to help planners and utility companies design resilient and efficient grids by visualizing and testing their vulnerabilities.</p>

  <h2>Part 1: Dynamic Programming Model — Lines Tripping System</h2>
  <h3>Problem Context:</h3>
  <ul>
    <li><strong>n power stations</strong>, each with <strong>m transmission lines</strong>.</li>
    <li>A 3D matrix <code>g[i][j][t]</code> defines the disbalance caused by tripping the j-th line of station i at time t.</li>
    <li>We can trip up to <strong>pos</strong> lines, but:
      <ul>
        <li>Can't trip all lines of any station.</li>
        <li>Can't trip all <strong>pos</strong> lines at once.</li>
      </ul>
    </li>
    <li>Forbidden pairs <code>(station, line)</code> must be skipped.</li>
  </ul>

  <h3>DP State Definition:</h3>
  <p><code>dp[i][j][t]</code> = max disbalance after considering the first <strong>i</strong> stations, tripping <strong>j</strong> lines in total, and currently at time <strong>t</strong>.</p>

  <h3>Transition Logic:</h3>
  <p>Loop over each station <strong>i</strong>, each line <strong>k</strong>, and time step <strong>t</strong>:</p>
  <pre><code>if ((i, k) not forbidden and a[i] not exceeded): 
    dp[i][j+1][t+1] = max(dp[i][j+1][t+1], dp[i-1][j][t] + g[i][k][t+1]);</code></pre>

  <h3>Complexity:</h3>
  <ul>
    <li><strong>Time:</strong> O(n × pos × T × m)</li>
    <li><strong>Space:</strong> O(n × pos × T) — can be optimized via state compression.</li>
  </ul>

  <h2>Part 2: N-City Electricity Optimization — Minimum Cost Wiring</h2>
  <h3>Problem:</h3>
  <p>Given <strong>n</strong> cities and <strong>e</strong> edges (potential wires) with weights (costs), connect all cities:
    <ul>
      <li>With minimal total cost.</li>
      <li>Without cycles (i.e., forming a tree).</li>
    </ul>
  </p>

  <h3>Algorithm Used: Kruskal's MST</h3>
  <ul>
    <li>Sort edges by cost.</li>
    <li>Use Disjoint Set Union (DSU) to avoid cycles.</li>
    <li>Add edges if their endpoints belong to different sets.</li>
  </ul>

  <h3>Complexity:</h3>
  <ul>
    <li><strong>Time:</strong> O(E log E) — using sorted edges and DSU.</li>
  </ul>

  <h3>Approach:</h3>
  <p>Assume a new node <strong>node-0</strong> as the main power station. Connect each new power station to <strong>node-0</strong> with a cost of installing that station (<strong>city[i]</strong>). Treat the problem as a Minimum Spanning Tree (MST) execution on a graph with <strong>n+1</strong> nodes.</p>

 </body>
</html>
