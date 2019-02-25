// Maze.hpp is a file that handles solving the Apollo and Diana Maze
// It takes a file, separates it into usable chunks, builds a graph from it
// then traverses the said graph using DFS. It output the path to the end of the
// maze on an output file for easy reading
// Gericho Ball Proj 3 U5224655 

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Maze{
private:
    //struct to store values of vertexes
    struct Vert{
        int id;
        string direction;
        string color;
        bool visited;
    };
    
    int x;
    int y;
    vector<string> val;
    vector<Vert> data;

public:
    Maze(string inputFile){
        ifstream infile(inputFile.c_str());
        string line;

        infile >> x >> y;

        while (infile >> line)
		{
			val.push_back(line);
		}

		infile.close();
		Parse();
    }

    int getX(){return x;}
    int getY(){return y;}

    void Parse(){
        int sNum = 0;
        vector<string>::iterator iter = val.begin();

        for(; iter != val.end(); ++iter, sNum++){
            Vert newVert;
            istringstream iss(*iter);

            if(*iter == "O"){
                newVert.id = sNum;
                newVert.color = "";
                newVert.direction = "O";
                newVert.visited = false;
                data.push_back(newVert);
                break;
            }

            newVert.id = sNum;
            getline(iss, newVert.color, '-');
            getline(iss, newVert.direction);
            newVert.visited = false;
            data.push_back(newVert);
        }
    }

    //DFS function to traverse the graph
    void DFS(){
        stack<Vert> path;
        stack<int> num;
        Vert temp;
        Vert current;
        vector<Vert>::iterator iter = data.begin();
        vector<Vert>::iterator endIter = data.end();

        current = *iter;
        iter->visited = true;
        path.push(current);
        num.push(0);

        while(current.color != (endIter-1)->color && current.direction != (endIter-1)->direction){

            int moves = 0;

            current = path.top();
            iter = current.id + data.begin();
            //handling N direction. All other directions function similarly
            //a conditional is present for every direction that is possible on the graph
            if(current.direction == "N"){
                if(iter - data.begin() <= x){
                    num.pop();
                    path.pop();
                    continue;
                }
                do{
                    iter -= x;
                    moves++;
                    if (iter >= data.begin())
                        temp = *iter;
                } while((temp.color == current.color || temp.visited) && iter >= data.begin());


                if(iter < data.begin()){
                    num.pop();
                    path.pop();
                    continue;
                }
                iter->visited = true;
                num.push(moves);
                path.push(temp);
            }
            //handling S direction
            if(current.direction == "S"){
                if((data.end() - iter) <= x){
                    num.pop();
                    path.pop();
                    continue;
                }

                do{
                    iter += x;
                    moves++;
                    if(iter <= data.end())
                        temp = *iter;
                } while((temp.color == current.color || temp.visited) && iter <= data.end());

                if(iter > data.end()){
                    num.pop();
                    path.pop();
                    continue;
                }
                iter->visited = true;
                num.push(moves);
                path.push(temp);
            }
            //handling E direction
            if(current.direction == "E"){
                if((iter - data.begin()) % x == x - 1){
                    num.pop();
                    path.pop();
                    continue;
                }

                do{
                    iter++;
                    moves++;
                    if((iter - data.begin()) % x != 0)
                        temp = *iter;
                } while((temp.color == current.color || temp.visited) && (iter - data.begin()) % x != 0);

                if((iter - data.begin()) % x == 0){
                    num.pop();
                    path.pop();
                    continue;
                }
                iter->visited = true;
                num.push(moves);
                path.push(temp);
            }
            //Handling W direction
            if(current.direction == "W"){
                if((iter - data.begin())%x == 0){
                    num.pop();
                    path.pop();
                    continue;
                }

                do{
                    iter--;
                    moves++;
                    if((iter - data.begin()) % x != x-1)
                        temp = *iter;
                } while((temp.color == current.color || temp.visited) && (iter - data.begin()) % x != x-1);

                if((iter - data.begin()) % x == x-1){
                    num.pop();
                    path.pop();
                    continue;
                }
                iter->visited = true;
                num.push(moves);
                path.push(temp);
            }
            //Handling NE direction
            if(current.direction == "NE"){
                if(iter - data.begin() < x || (iter - data.begin()) % x == x - 1){
                    num.pop();
                    path.pop();
                    continue;
                }

                do{
                    iter -= x - 1;
                    moves++;
                    if(iter >= data.begin() && (iter - data.begin()) % x != 0)
                        temp = *iter;
                } while((temp.color == current.color || temp.visited) && iter >= data.begin() && (iter - data.begin()) % x != 0);

                if(iter < data.begin() || (iter - data.begin()) % x == 0){
                    num.pop();
                    path.pop();
                    continue;
                }
                iter->visited = true;
                num.push(moves);
                path.push(temp);
            }
            //handling NW direction
            if(current.direction == "NW"){
                if((iter - data.begin())/x < 1 || (iter - data.begin())%x == 0){
                    num.pop();
                    path.pop();
                    continue;
                }

                do{
                    iter -= x + 1;
                    moves++;
                    if((iter-data.begin()) >= 0 && (iter - data.begin()) % x != x-1)
                        temp = *iter;
                } while((temp.color == current.color || temp.visited) && (iter-data.begin()) >= 0 && (iter - data.begin()) % x != x-1);

                if((iter-data.begin()) < 0 || (iter - data.begin()) % x == x-1){
                    num.pop();
                    path.pop();
                    continue;
                }
                iter->visited = true;
                num.push(moves);
                path.push(temp);
            }
            //handling SE direction
            if(current.direction == "SE"){
                if((data.end() - iter) <= x || (iter - data.begin()) % x == x - 1){
                    num.pop();
                    path.pop();
                    continue;
                }
                do{
                    iter += x + 1;
                    moves++;
                    if((iter < data.end() && (iter - data.begin()) % x != 0))
                        temp = *iter;
                } while((temp.color == current.color || temp.visited) && (iter < data.end() && (iter - data.begin()) % x != 0));

                if(iter >= data.end() || (iter - data.begin()) % x == 0){
                    num.pop();
                    path.pop();
                    continue;
                }
                iter->visited = true;
                num.push(moves);
                path.push(temp);
            }
            //handling SW direction
            if(current.direction == "SW"){
                if((data.end() - iter)/x < 1 || (iter - data.begin())%x == 0){
                    num.pop();
                    path.pop();
                    continue;
                }
                do{
                    iter += x - 1;
                    moves++;
                    if((data.end()-iter) >= 0 && (iter - data.begin()) % x != x-1)
                        temp = *iter;
                } while((temp.color == current.color || temp.visited) && (data.end()-iter) >= 0 && (iter - data.begin()) % x != x-1);

                if((data.end()-iter) < 0 || (iter - data.begin()) % x == x-1){
                    num.pop();
                    path.pop();
                    continue;
                }
                iter->visited = true;
                num.push(moves);
                path.push(temp);
            }
        }
        num.push(0);

        //swaps the order of the stacks so they are printed in the correct order
        stack<string> finPath;
        stack<int> finNum;

        while(!path.empty()){
            finPath.push(path.top().direction);
            finNum.push(num.top());
            num.pop();
            path.pop();
        }
    
        //opening file to write output to
        ofstream outFile;
        outFile.open("output.txt");
        //writing to output file
        while(finPath.size() > 1){
            outFile << finNum.top();
            outFile << finPath.top() << ' ';
            finNum.pop();
            finPath.pop();
        }
    
        outFile.close();
    }
};
