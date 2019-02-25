#include <stack>
#include <queue>
#include "bfsMazeEscape.h"
#include <cassert>

void bfsFindExit(Maze &M)
{
	queue<Position> Q;
	direction d;
	vector<vector<Position> > pred;
	init_table(pred, M.size-1, NULLPOS);
	Position current, nbr;

	//initially marks start as visited & pushes it onto the queue
	M.visit(M.start);
	Q.push(M.start);

	while (!Q.empty()) {
		//Dequeue and element from queue into current
		current = Q.front();
		Q.pop();
		//check is current is the exit position
		if (current == M.exitpos) {
			//print path to current
			printPath(pred, current);
			return;
		}

		//Examining DOWN neighbor of current
		if (M.isOpen(current.Neighbor(DOWN))) {
			//if the neighbor is open, mark it as VISITED
			nbr = current.Neighbor(DOWN);
			M.visit(nbr);
			//make current the predecessor of the neighbor
			setEntry(pred, nbr, current);
			//if nbr == exitpos print and return
			if (nbr == M.exitpos) {
				//print path
				printPath(pred, nbr);
				return;
			}
			//otherwise add to the queue
			Q.push(nbr);
		}

		//Examining LEFT neighbor of current
		if (M.isOpen(current.Neighbor(LEFT))) {
			//if the neighbor is open, mark it as VISITED
			nbr = current.Neighbor(LEFT);
			M.visit(nbr);
			//make current the predecessor of the neighbor
			setEntry(pred, nbr, current);
			//if nbr == exitpos print and return
			if (nbr == M.exitpos) {
				//print path
				printPath(pred, nbr);
				return;
			}
			//otherwise add to the queue
			Q.push(nbr);
		}

		//Examining UP neighbor of current
		if (M.isOpen(current.Neighbor(UP))) {
			//if the neighbor is open, mark it as VISITED
			nbr = current.Neighbor(UP);
			M.visit(nbr);
			//make current the predecessor of the neighbor
			setEntry(pred, nbr, current);
			//if nbr == exitpos print and return
			if (nbr == M.exitpos) {
				//print path
				printPath(pred, nbr);
				return;
			}
			//otherwise add to the queue
			Q.push(nbr);
		}

		//Examining RIGHT neighbor of current
		if (M.isOpen(current.Neighbor(RIGHT))) {
			//if the neighbor is open, mark it as VISITED
			nbr = current.Neighbor(RIGHT);
			M.visit(nbr);
			//make current the predecessor of the neighbor
			setEntry(pred, nbr, current);
			//if nbr == exitpos print and return
			if (nbr == M.exitpos) {
				//print path
				printPath(pred, nbr);
				return;
			}
			//otherwise add to the queue
			Q.push(nbr);
		}
	}

	//if the loop has been broken because the queue is now empty
	cout << endl << "No Way Out!" << endl;
}
