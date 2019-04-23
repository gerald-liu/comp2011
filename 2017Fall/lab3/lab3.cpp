/*
 * lab3.cpp
 *
 * Created on: Sep 22, 2017
 *     Author: Weiyang Liu
 */


#include <iostream>
using namespace std;

int candleHeight, candleWidth, bottomHeight, bottomWidth, layers;
char crust, filling;

void printLine(int leadingSpaces, int lineWidth, char endChar, char middleChar);
void drawCandle(int leadingSpaces, int candleWidth, int candleHeight);
void drawCake(int layers, int bottomHeight, int bottomWidth, char crust, char filling);
void candleSpec();
void cakeSpec(bool hasCandle);

int main(){
        int toRun;
        do {
                cout << "Please choose a program to run:" << endl;
                cout << "1: Draw candles.\n2: Draw cakes with rectangle shape.\n3: Draw birthday cake with candles on it.\n0: Exit.\nPlease input your selection:";
                cin >> toRun;
                switch (toRun) {
                case 1: candleSpec();
                        drawCandle(0, candleHeight, candleWidth);
                        break;
                case 2: cakeSpec(false);
                        drawCake(layers, bottomHeight, bottomWidth, crust, filling);
                        break;
                case 3: candleSpec();
                        cakeSpec(true);
                        drawCandle(2*(layers-1)+(bottomWidth-4*(layers-1)-2*candleWidth)/2, candleWidth, candleHeight);
                        drawCake(layers, bottomHeight, bottomWidth, crust, filling);
                        break;
                }
        } while (toRun!=0);
        return 0;
}



void printLine(int leadingSpaces, int lineWidth, char endChar, char middleChar){
        for (int i=0; i<leadingSpaces; i++) {
                cout << " ";
        }
        for (int i=0; i<lineWidth; i++) {
                cout << ((i==0 || i==lineWidth-1) ? endChar : middleChar);
        }
        cout << endl;
        return;
}


void drawCandle(int leadingSpaces, int candleWidth, int candleHeight){
        for (int i=0; i<leadingSpaces+candleWidth; i++) {
                cout << ((i<leadingSpaces) ? " " : " )");
        }
        cout << endl;
        for (int i=0; i<candleHeight-1; i++) {
                for (int i=0; i<leadingSpaces+candleWidth; i++) {
                        cout << ((i<leadingSpaces) ? " " : "()");
                }
                cout << endl;
        }
        return;
}


void drawCake(int layers, int bottomHeight, int bottomWidth, char crust, char filling){
        int leadingSpaces;
        for (int layerHeight=bottomHeight - (layers-1), layerWidth=bottomWidth - 4*(layers-1); // topHeight, topWidth
             layerHeight <= bottomHeight;
             layerHeight++, layerWidth+=4)
        {
                leadingSpaces = (bottomWidth - layerWidth)/2;
                for (int i=0; i<layerHeight; i++) {
                        printLine(leadingSpaces, layerWidth, crust, ((i==0 || i==layerHeight-1) ? crust : filling));
                }
        }
        return;
}



void candleSpec(){
        cout << "Please input the height of the candles:";
        cin >> candleHeight;
        cout << "Please input the number of the candles:";
        cin >> candleWidth;
        return;
}


void cakeSpec(bool hasCandle){
        cout << "Please input the layers of the cake:";
        cin >> layers;

        do {
                cout << "Please input the height of the bottom layer of the cake:";
                cin >> bottomHeight;
                if (bottomHeight - (layers-1) <= 3) {
                        cout << "Height is not large enough. Please try again." << endl;
                }
        } while (bottomHeight - (layers-1) <= 3); // topHeight

        do {
                cout << "Please input the width of the bottom layer of the cake (which should be even):";
                cin >> bottomWidth;
                if (bottomWidth % 2 !=0) {
                        cout << "Invalid input, please input an even integer." << endl;
                        continue;
                }
                if (bottomWidth - 4*(layers-1) <= 4 || (hasCandle && bottomWidth - 4*(layers-1) <= candleWidth*2)) { // topWidth
                        cout << "Width is not large enough. Please try again." << endl;
                }
        } while (bottomWidth % 2 !=0 || bottomWidth - 4*(layers-1) <= 4 || (hasCandle && bottomWidth - 4*(layers-1) <= candleWidth*2));

        cout << "Please input the symbol for the crust of the cake:";
        cin >> crust;
        cout << "Please input the symbol for the filling of the cake:";
        cin >> filling;
        return;
}
