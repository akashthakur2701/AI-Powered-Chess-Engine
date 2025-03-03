//
//  main.cpp
//  AI_POWERED_CHESS
//
//  Created by AKASH THAKUR on 02/03/25.
//
#include <iostream>
//#include<GL/glew.h>
//#include<SFML/Window.hpp>
//#include<SFML/Graphics.hpp>
using namespace std ;

//defining bitboard datatype
#define U64 unsigned long long

//board chess
enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};
//sides to move (colors) (white = 0, black = 1)
enum {
    white,black
};

//for future
/*
8-> 0  1  2  3  4  5  6  7
7-> 8  9  10 11 12 13 14 15
6-> 16 17 18 19 20 21 22 23
5-> 24 25 26 27 28 29 30 31
4-> 32 33 34 35 36 37 38 39
3-> 40 41 42 43 44 45 46 47
2-> 48 49 50 51 52 53 54 55
1-> 56 57 58 59 60 61 62 63
     a  b  c  d  e  f  g   h
 
 
"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
*/
//set/get.pop macro
#define get_bit(bitboard,square) (bitboard & (1ULL)<<square)
#define set_bit(bitboard,square) (bitboard |= (1ULL)<<square)
#define pop_bit(bitboard,square) (get_bit(bitboard,square) ? bitboard ^= (1ULL) << square:0)




//function to print bitboard
void print_bitboard(U64 bitboard){
    cout<<endl;
    for(int rank = 0 ; rank < 8 ; rank++){
        for(int file = 0 ; file < 8 ; file++){
            //print rank which means row in a chess
            if(!file) cout<<8-rank<<" ";
            
            int square = rank*8 + file ;
            printf(" %d",get_bit(bitboard, square)?1:0);
        }
        cout<<endl;
    }
    //print files which means column in a chess
    printf("\n   a b c d e f g h\n");
    //print the bitboard in decimal form
    printf("   Bitboard: %llud \n",bitboard);
    
}

int main() {
   /* define bitboard
    U64 bitboard = 0ULL;
    setting some bit
    set_bit(bitboard, h2);
    set_bit(bitboard, c4);
    set_bit(bitboard, e6);
    printing bitboard
    print_bitboard(bitboard);
    resetting bit
    pop_bit(bitboard,c4);
    pop_bit(bitboard,c4);
    get_bit(bitboard, c4) ?  pop_bit(bitboard, c4) : 0 ; //so that xor opertor don't toggle 0 bit to 1
    print_bitboard(bitboard);
  */
    return 0;
}
