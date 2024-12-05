function dijkstra(graph, start, end) {
    // Inicialização
    const distances = {}; // Menores distâncias
    const previous = {};  // Para rastrear o caminho
    const unvisited = new Set(Object.keys(graph)); // Nós ainda não visitados

    // Configurar distâncias iniciais
    for (const node in graph) {
        distances[node] = Infinity; // Define a distância como infinita inicialmente
        previous[node] = null; // Sem nós anteriores no começo
    }
    distances[start] = 0; // Distância inicial do nó de partida para ele mesmo é 0

    while (unvisited.size > 0) {
        // Selecionar o nó com a menor distância
        const current = [...unvisited].reduce((minNode, node) =>
            distances[node] < distances[minNode] ? node : minNode
        );

        // Se chegamos ao nó final, paramos
        if (current === end) break;

        // Atualizar distâncias para os vizinhos do nó atual
        for (const neighbor in graph[current]) {
            const newDistance = distances[current] + graph[current][neighbor];
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                previous[neighbor] = current;
            }
        }

        // Remover o nó atual dos não visitados
        unvisited.delete(current);
    }

    // Reconstruir o caminho mais curto
    const path = [];
    let currentNode = end;
    while (currentNode) {
        path.unshift(currentNode);
        currentNode = previous[currentNode];
    }

    return { distance: distances[end], path };
}

// Grafo de entrada
const graph = {
    A: { B: 4, C: 2, D: 7 },
    B: { A: 4, C: 1, E: 1 },
    C: { A: 2, B: 1, D: 3, E: 3 },
    D: { A: 7, C: 3, E: 2 },
    E: { B: 1, C: 3, D: 2 }
};

// Calcular de A até E
const resultAE = dijkstra(graph, "A", "E");
console.log(`Menor tempo de A até E: ${resultAE.distance}`);
console.log(`Caminho de A até E: ${resultAE.path.join(" → ")}`);

// Calcular de A até D
const resultAD = dijkstra(graph, "A", "D");
console.log(`Menor tempo de A até D: ${resultAD.distance}`);
console.log(`Caminho de A até D: ${resultAD.path.join(" → ")}`);
