#include <iostream>

using namespace std;

const int M = 3;
const int N = 4;
const int L = 3;
const int TOTAL_NODES = M * N * L;

void idToCoord(int id, int& surface, int& row, int& col) {
    surface = id / (M * N);
    int remainder = id % (M * N);
    row = remainder / N;
    col = remainder % N;
}

int coordToId(int surface, int row, int col) {
    return surface * (M * N) + row * N + col;
}

void horizontalPathClockwise(int srcId, int dstCol, int path[], int& pathSize) {
    int surface, row, col;
    idToCoord(srcId, surface, row, col);

    if (col == dstCol) {
        pathSize = 0;
        return;
    }

    int currentCol = col;
    pathSize = 0;

    while (currentCol != dstCol) {
        currentCol = (currentCol + 1) % N;
        path[pathSize] = coordToId(surface, row, currentCol);
        pathSize++;
    }
}

void verticalPathClockwise(int srcId, int dstRow, int path[], int& pathSize) {
    int surface, row, col;
    idToCoord(srcId, surface, row, col);

    if (row == dstRow) {
        pathSize = 0;
        return;
    }

    int currentRow = row;
    pathSize = 0;

    while (currentRow != dstRow) {
        currentRow = (currentRow + 1) % M;
        path[pathSize] = coordToId(surface, currentRow, col);
        pathSize++;
    }
}

void spatialPathClockwise(int srcId, int dstSurface, int path[], int& pathSize) {
    int surface, row, col;
    idToCoord(srcId, surface, row, col);

    if (surface == dstSurface) {
        pathSize = 0;
        return;
    }

    int currentSurface = surface;
    pathSize = 0;

    while (currentSurface != dstSurface) {
        currentSurface = (currentSurface + 1) % L;
        path[pathSize] = coordToId(currentSurface, row, col);
        pathSize++;
    }
}

void routePathClockwise(int srcId, int dstId, int path[], int& pathSize) {
    int srcSurface, srcRow, srcCol;
    int dstSurface, dstRow, dstCol;

    idToCoord(srcId, srcSurface, srcRow, srcCol);
    idToCoord(dstId, dstSurface, dstRow, dstCol);

    pathSize = 0;

    if (srcId == dstId) {
        return;
    }

    int tempPath[TOTAL_NODES];
    int tempSize;

    if (srcRow == dstRow && srcSurface == dstSurface) {
        horizontalPathClockwise(srcId, dstCol, path, pathSize);
    }

    else if (srcCol == dstCol && srcSurface == dstSurface) {
        verticalPathClockwise(srcId, dstRow, path, pathSize);
    }

    else if (srcSurface == dstSurface) {

        horizontalPathClockwise(srcId, dstCol, tempPath, tempSize);
        for (int i = 0; i < tempSize; i++) {
            path[pathSize] = tempPath[i];
            pathSize++;
        }

        int lastNode = srcId;
        if (tempSize > 0) {
            lastNode = tempPath[tempSize - 1];
        }

        int lastSurface, lastRow, lastCol;
        idToCoord(lastNode, lastSurface, lastRow, lastCol);
        int intermediateNode = coordToId(lastSurface, lastRow, dstCol);

        verticalPathClockwise(intermediateNode, dstRow, tempPath, tempSize);
        for (int i = 0; i < tempSize; i++) {
            path[pathSize] = tempPath[i];
            pathSize++;
        }
    }

    else {

        horizontalPathClockwise(srcId, dstCol, tempPath, tempSize);
        for (int i = 0; i < tempSize; i++) {
            path[pathSize] = tempPath[i];
            pathSize++;
        }

        int lastNode = srcId;
        if (tempSize > 0) {
            lastNode = tempPath[tempSize - 1];
        }

        int lastSurface, lastRow, lastCol;
        idToCoord(lastNode, lastSurface, lastRow, lastCol);
        int intermediateNode1 = coordToId(lastSurface, lastRow, dstCol);

        verticalPathClockwise(intermediateNode1, dstRow, tempPath, tempSize);
        for (int i = 0; i < tempSize; i++) {
            path[pathSize] = tempPath[i];
            pathSize++;
        }

        if (tempSize > 0) {
            lastNode = tempPath[tempSize - 1];
        }
        else {
            lastNode = intermediateNode1;
        }

        idToCoord(lastNode, lastSurface, lastRow, lastCol);
        int intermediateNode2 = coordToId(lastSurface, dstRow, lastCol);

        spatialPathClockwise(intermediateNode2, dstSurface, tempPath, tempSize);
        for (int i = 0; i < tempSize; i++) {
            path[pathSize] = tempPath[i];
            pathSize++;
        }
    }
}

void reverseRoutePathClockwise(int srcId, int dstId, int path[], int& pathSize) {
    int srcSurface, srcRow, srcCol;
    int dstSurface, dstRow, dstCol;

    idToCoord(srcId, srcSurface, srcRow, srcCol);
    idToCoord(dstId, dstSurface, dstRow, dstCol);

    pathSize = 0;

    if (srcId == dstId) {
        return;
    }

    int tempPath[TOTAL_NODES];
    int tempSize;

    spatialPathClockwise(srcId, dstSurface, tempPath, tempSize);
    for (int i = 0; i < tempSize; i++) {
        path[pathSize] = tempPath[i];
        pathSize++;
    }

    int lastNode = srcId;
    if (tempSize > 0) {
        lastNode = tempPath[tempSize - 1];
    }

    int lastSurface, lastRow, lastCol;
    idToCoord(lastNode, lastSurface, lastRow, lastCol);
    int intermediateNode1 = coordToId(dstSurface, lastRow, lastCol);

    verticalPathClockwise(intermediateNode1, dstRow, tempPath, tempSize);
    for (int i = 0; i < tempSize; i++) {
        path[pathSize] = tempPath[i];
        pathSize++;
    }

    if (tempSize > 0) {
        lastNode = tempPath[tempSize - 1];
    }
    else {
        lastNode = intermediateNode1;
    }

    idToCoord(lastNode, lastSurface, lastRow, lastCol);
    int intermediateNode2 = coordToId(lastSurface, dstRow, lastCol);

    horizontalPathClockwise(intermediateNode2, dstCol, tempPath, tempSize);
    for (int i = 0; i < tempSize; i++) {
        path[pathSize] = tempPath[i];
        pathSize++;
    }
}

void alternativeRoutePath(int srcId, int dstId, int path[], int& pathSize) {
    int srcSurface, srcRow, srcCol;
    int dstSurface, dstRow, dstCol;

    idToCoord(srcId, srcSurface, srcRow, srcCol);
    idToCoord(dstId, dstSurface, dstRow, dstCol);

    pathSize = 0;

    if (srcId == dstId) {
        return;
    }

    int tempPath[TOTAL_NODES];
    int tempSize;

    horizontalPathClockwise(srcId, srcCol, tempPath, tempSize);
    for (int i = 0; i < tempSize; i++) {
        path[pathSize] = tempPath[i];
        pathSize++;
    }

    int lastNode = srcId;
    if (tempSize > 0) {
        lastNode = tempPath[tempSize - 1];
    }

    verticalPathClockwise(lastNode, srcRow, tempPath, tempSize);
    for (int i = 0; i < tempSize; i++) {
        path[pathSize] = tempPath[i];
        pathSize++;
    }

    if (tempSize > 0) {
        lastNode = tempPath[tempSize - 1];
    }

    spatialPathClockwise(lastNode, srcSurface, tempPath, tempSize);
    for (int i = 0; i < tempSize; i++) {
        path[pathSize] = tempPath[i];
        pathSize++;
    }

    if (tempSize > 0) {
        lastNode = tempPath[tempSize - 1];
    }

    int finalPath[TOTAL_NODES];
    int finalSize;
    routePathClockwise(lastNode, dstId, finalPath, finalSize);

    for (int i = 0; i < finalSize; i++) {
        path[pathSize] = finalPath[i];
        pathSize++;
    }
}

void printPath(int path[], int pathSize, const char* name) {
    cout << name << " (" << pathSize << " hops): ";
    if (pathSize == 0) {
        cout << "direct connection";
    }
    else {
        for (int i = 0; i < pathSize; i++) {
            cout << path[i];
            if (i != pathSize - 1) {
                cout << " -> ";
            }
        }
    }
    cout << endl;
}

void printNodeInfo(int id) {
    int surface, row, col;
    idToCoord(id, surface, row, col);
    cout << "Node " << id << " (L=" << surface
        << ", R=" << row << ", C=" << col << ")";
}

void printNetwork() {
    cout << "3D RING NETWORK (CLOCKWISE ONLY)" << endl;
    cout << "=================================" << endl;
    cout << "Rows (M): " << M << ", Columns (N): " << N << ", Layers (L): " << L << endl;
    cout << "Total nodes: " << TOTAL_NODES << endl << endl;

    for (int l = 0; l < L; l++) {
        cout << "LAYER " << l << ":" << endl;
        for (int m = 0; m < M; m++) {
            cout << "  Row " << m << ": ";
            for (int n = 0; n < N; n++) {
                int id = coordToId(l, m, n);
                cout << id;
                if (id < 10) cout << " ";
                cout << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

bool arePathsDifferent(int path1[], int size1, int path2[], int size2, int srcId, int dstId) {
    for (int i = 0; i < size1; i++) {
        if (path1[i] == srcId || path1[i] == dstId) continue;

        for (int j = 0; j < size2; j++) {
            if (path2[j] == srcId || path2[j] == dstId) continue;

            if (path1[i] == path2[j]) {
                return false;
            }
        }
    }
    return true;
}


int main() {

    printNetwork();

    cout << "==================================\n" << endl;

    int primaryPath[TOTAL_NODES];
    int backupPath[TOTAL_NODES];
    int alternativePath[TOTAL_NODES];
    int primarySize, backupSize, alternativeSize;
    bool different;

    int src, dst;
    char choice;

    do {
        cout << "\nEnter source node ID (0-" << TOTAL_NODES - 1 << "): ";
        cin >> src;

        if (src < 0 || src >= TOTAL_NODES) {
            cout << "Invalid source node!" << endl;
            continue;
        }

        cout << "Enter destination node ID (0-" << TOTAL_NODES - 1 << "): ";
        cin >> dst;

        if (dst < 0 || dst >= TOTAL_NODES) {
            cout << "Invalid destination node!" << endl;
            continue;
        }

        cout << "\nRouting from ";
        printNodeInfo(src);
        cout << " to ";
        printNodeInfo(dst);
        cout << endl;

        routePathClockwise(src, dst, primaryPath, primarySize);
        reverseRoutePathClockwise(src, dst, backupPath, backupSize);
        //alternativeRoutePath(src, dst, alternativePath, alternativeSize);

        printPath(primaryPath, primarySize, "Primary path");
        printPath(backupPath, backupSize, "Backup path");
        //printPath(alternativePath, alternativeSize, "Alternative path");

        different = arePathsDifferent(primaryPath, primarySize, backupPath, backupSize, src, dst);
        cout << "\nPrimary and Backup paths are " << (different ? "DIFFERENT" : "SAME/OVERLAPPING") << endl;

        cout << "\nCoordinates:" << endl;
        int sSurface, sRow, sCol, dSurface, dRow, dCol;
        idToCoord(src, sSurface, sRow, sCol);
        idToCoord(dst, dSurface, dRow, dCol);
        cout << "Source: Layer=" << sSurface << ", Row=" << sRow << ", Col=" << sCol << endl;
        cout << "Dest:   Layer=" << dSurface << ", Row=" << dRow << ", Col=" << dCol << endl;

        cout << "\nTest another route? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\nProgram completed." << endl;

    return 0;
}
