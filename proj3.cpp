//Preprocess.hpp is a file that is used to change values in an .arff to test the accuracy of facial values in WEKA
//after modifying the values a new .arff file is output It uses 3 primary functions, PreProcess, Translate, and Random
//Gericho Ball
//Affectibve Computing Spring 2018
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <time.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct data{
    vector<string> header;
    vector<string> information;
    vector<string> outputInfo;
};

int main(int argc, char *argv[])
{
    ifstream myFile;
    string line;
    data arff = data();
    int count = 0;
    myFile.open(argv[2]);

    //storing header info
    while(getline(myFile, line))
    {  
        if(count == 296)
            break;
        arff.header.push_back(line);
        count++;
    }
    arff.header.push_back("\n");

    //storing facial info
    count = 0;
    while(getline(myFile,line))
    {
        while(count < 295)
            count++;
        arff.information.push_back(line);
    }

    if(strcmp(argv[1], "translate_origin") == 0){
        //Making Origin File
        ofstream outputFile3(argv[3]);
        ostream_iterator<string> output_iterator3(outputFile3, "\n");
        copy(arff.header.begin(), arff.header.end(), output_iterator3);
        //string stream
        vector<double> orig(75000);
        string token, tokenC;
        string iden, idenC;
        string finClass = "T";
        char cla;
        int i = 0;
        //getting the average of the entire row
        for(i=0; i< 75000; i++){    
            istringstream tt(arff.information[i]);
            idenC = arff.information[i];
            while(getline(tt, tokenC, ',')){
                double val2 = atof(tokenC.c_str());
                orig[i] = orig[i] + val2;
            }
        }
        //changing values and writing to out file
        for(i=0; i< 75000; i++){
            finClass = 'T';
            istringstream ss(arff.information[i]);
            iden = arff.information[i];
            while(getline(ss, token, ',')){
                if(token.find('T') != 0){
                    double val = atof(token.c_str()); 
                    val = val - (orig[i] / 292);         
                    outputFile3 << val << ",";
                }
            }
            cla = iden[iden.length()-2];
            finClass = finClass + cla;
            outputFile3 << finClass << '\n';
        }
    }

    else if(strcmp(argv[1], "scale") == 0){
        //Making scale File
        ofstream outputFile3(argv[3]);
        ostream_iterator<string> output_iterator3(outputFile3, "\n");
        copy(arff.header.begin(), arff.header.end(), output_iterator3);
        //string stream
        vector<double> orig(75000);
        string token, tokenC;
        string iden, idenC;
        string finClass = "T";
        char cla;
        int i = 0;
        //getting the average of the entire row
        for(i=0; i< 75000; i++){    
            istringstream tt(arff.information[i]);
            idenC = arff.information[i];
            while(getline(tt, tokenC, ',')){
                double val2 = atof(tokenC.c_str());
                orig[i] = orig[i] + val2;
            }
        }
        //changing values and writing to out file
        for(i=0; i< 75000; i++){
            finClass = 'T';
            istringstream ss(arff.information[i]);
            iden = arff.information[i];
            while(getline(ss, token, ',')){
                if(token.find('T') != 0){
                    double val = atof(token.c_str()); 
                    val = val * .25;         
                    outputFile3 << val << ",";
                }
            }
            cla = iden[iden.length()-2];
            finClass = finClass + cla;
            outputFile3 << finClass << '\n';
        }
    }

        else if(strcmp(argv[1], "rotate_x") == 0){
        //Making rotate x file
        ofstream outputFile4(argv[3]);
        ostream_iterator<string> output_iterator4(outputFile4, "\n");
        copy(arff.header.begin(), arff.header.end(), output_iterator4);
        int i = 0;
        string tokenR;
        int state = 3;
        string idenR;
        string finR = "T";
        int valR;
        char claR;
        for(i=0; i< 75000; i++){
            if(state == 3)
                state = 1;
            else if(state == 2)
                state = 3;
            else if(state == 1)
                state = 2;
            finR = 'T';
            istringstream mm(arff.information[i]);
            string iden = arff.information[i];
            while(getline(mm, tokenR, ',')){
                if(tokenR.find('T') != 0){
                    double valR = atof(tokenR.c_str());
                    if(state == 1)
                        valR = valR;
                    else if(state == 2)
                        valR *= -1;
                    else if(state == 3)
                        valR *= -1;
                    outputFile4 << valR << ",";
                }
            }
        claR = iden[iden.length()-2];
        finR = finR + claR;
        outputFile4 << finR << '\n';
        }
    } 

    else if(strcmp(argv[1], "rotate_y") == 0){
        //Making rotate y file
        ofstream outputFile4(argv[3]);
        ostream_iterator<string> output_iterator4(outputFile4, "\n");
        copy(arff.header.begin(), arff.header.end(), output_iterator4);
        int i = 0;
        string tokenR;
        int state = 3;
        string idenR;
        string finR = "T";
        int valR;
        char claR;
        for(i=0; i< 75000; i++){
            if(state == 3)
                state = 1;
            else if(state == 2)
                state = 3;
            else if(state == 1)
                state = 2;
            finR = 'T';
            istringstream mm(arff.information[i]);
            string iden = arff.information[i];
            while(getline(mm, tokenR, ',')){
                if(tokenR.find('T') != 0){
                    double valR = atof(tokenR.c_str());
                    if(state == 1)
                        valR *= -1;
                    else if(state == 2)
                        valR = valR;
                    else if(state == 3)
                        valR *= -1;
                    outputFile4 << valR << ",";
                }
            }
        claR = iden[iden.length()-2];
        finR = finR + claR;
        outputFile4 << finR << '\n';
        }
    } 

    else if(strcmp(argv[1], "rotate_z") == 0){
        //Making rotate z file
        ofstream outputFile4(argv[3]);
        ostream_iterator<string> output_iterator4(outputFile4, "\n");
        copy(arff.header.begin(), arff.header.end(), output_iterator4);
        int i = 0;
        string tokenR;
        int state = 3;
        string idenR;
        string finR = "T";
        int valR;
        char claR;
        for(i=0; i< 75000; i++){
            if(state == 3)
                state = 1;
            else if(state == 2)
                state = 3;
            else if(state == 1)
                state = 2;
            finR = 'T';
            istringstream mm(arff.information[i]);
            string iden = arff.information[i];
            while(getline(mm, tokenR, ',')){
                if(tokenR.find('T') != 0){
                    double valR = atof(tokenR.c_str());
                    if(state == 1)
                        valR *= -1;
                    else if(state == 2)
                        valR *= -1;
                    else if(state == 3)
                        valR = valR;
                    outputFile4 << valR << ",";
                }
            }
        claR = iden[iden.length()-2];
        finR = finR + claR;
        outputFile4 << finR << '\n';
        }
    } 

    else if(strcmp(argv[1], "translate_random") == 0){
        //Making random file
        ofstream outputFile4(argv[3]);
        ostream_iterator<string> output_iterator4(outputFile4, "\n");
        copy(arff.header.begin(), arff.header.end(), output_iterator4);
        //random translation
        int randX, randY, randZ;
        int i = 0;
        srand(time(NULL));
        randX = rand()%100+1;
        randY = rand()%100+1;
        randZ = rand()%100+1;
        string tokenR;
        int state = 3;
        string idenR;
        string finR = "T";
        int valR;
        char claR;
        for(i=0; i< 75000; i++){
            //randomization at every line        
            randX = rand()%100+1;
            randY = rand()%100+1;
            randZ = rand()%100+1;
            if(state == 3)
                state = 1;
            else if(state == 2)
                state = 3;
            else if(state == 1)
                state = 2;
            finR = 'T';
            istringstream mm(arff.information[i]);
            string iden = arff.information[i];
            while(getline(mm, tokenR, ',')){
                if(tokenR.find('T') != 0){
                    double valR = atof(tokenR.c_str());
                    if(state == 1)
                        valR += randX;
                    else if(state == 2)
                        valR += randY;
                    else if(state == 3)
                        valR += randZ;
                    outputFile4 << valR << ",";
                }
            }
        claR = iden[iden.length()-2];
        finR = finR + claR;
        outputFile4 << finR << '\n';
        }
    } 
    
    if(strcmp(argv[1], "parse") == 0){
        //output of header
        ofstream outputFile("Project3Header.arff");
        ostream_iterator<string> output_iterator(outputFile, "\n");
        copy(arff.header.begin(), arff.header.end(), output_iterator);
        outputFile.close();
            
        //output of facial
        ofstream outputFile2("Project3Contents.arff");
        ostream_iterator<string> output_iter(outputFile2, "\n");
        copy(arff.information.begin(), arff.information.end(), output_iter);
        outputFile2.close(); 
    }
    return 0;

} 
