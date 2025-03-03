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



/************************************************
        ATTACKS
 ------------------------------------------------
 ------------------------------------------------
 
 *************************************************************************/
/*
 
 8  0 1 1 1 1 1 1 1
 7  0 1 1 1 1 1 1 1
 6  0 1 1 1 1 1 1 1
 5  0 1 1 1 1 1 1 1
 4  0 1 1 1 1 1 1 1
 3  0 1 1 1 1 1 1 1
 2  0 1 1 1 1 1 1 1
 1  0 1 1 1 1 1 1 1

    a b c d e f g h

 //not h file
 
 8  1 1 1 1 1 1 1 0
 7  1 1 1 1 1 1 1 0
 6  1 1 1 1 1 1 1 0
 5  1 1 1 1 1 1 1 0
 4  1 1 1 1 1 1 1 0
 3  1 1 1 1 1 1 1 0
 2  1 1 1 1 1 1 1 0
 1  1 1 1 1 1 1 1 0

    a b c d e f g h
 
 //not hg file
 
 8  1 1 1 1 1 1 0 0
 7  1 1 1 1 1 1 0 0
 6  1 1 1 1 1 1 0 0
 5  1 1 1 1 1 1 0 0
 4  1 1 1 1 1 1 0 0
 3  1 1 1 1 1 1 0 0
 2  1 1 1 1 1 1 0 0
 1  1 1 1 1 1 1 0 0

    a b c d e f g h

 //not ab file
 
 8  0 0 1 1 1 1 1 1
 7  0 0 1 1 1 1 1 1
 6  0 0 1 1 1 1 1 1
 5  0 0 1 1 1 1 1 1
 4  0 0 1 1 1 1 1 1
 3  0 0 1 1 1 1 1 1
 2  0 0 1 1 1 1 1 1
 1  0 0 1 1 1 1 1 1

    a b c d e f g h
 
 */
// not A file(A column) constant
const U64 not_a_file = 18374403900871474942ULL;
// not H file(H column) constant
const U64 not_h_file = 9187201950435737471ULL;
// not hg file constant
const U64 not_hg_file = 4557430888798830399ULL ;
//not ab file constant
const U64 not_ab_file =  18229723555195321596ULL ;


// pawn attacks table [side][square]

U64 pawn_attacks[2][64] ;

//knight attacks table [only square] both black and white knight have same attacks
U64 knight_attacks[64];

// king attack table [square]
U64 king_attacks[64];

//generate pawn attacks (sipahi )

U64 mask_pawn_attacks(int side,int square){
     //result attacks bitboard
    U64 attacks = 0ULL;
    
    //piece bitboard
    U64 bitboard = 0ULL ;
    
    //set bitboard
    set_bit(bitboard, square);
    
    //white pawn
    if(!side){
        //generate pawn attacks
        if((bitboard>>7) & not_a_file) attacks |= (bitboard>>7) ;
        if((bitboard>>9) & not_h_file) attacks |= (bitboard>>9) ;
    }
    
    
    //black pawn
    
    else{
        //generate pawn attacks
        if((bitboard<<7) & not_h_file) attacks |= (bitboard<<7) ;
        if((bitboard<<9) & not_a_file) attacks |= (bitboard<<9) ;
    }
    //return attack map
    return attacks;
};

//generate knight attacks (horse)

U64 mask_knight_attacks(int square){
    //result attacks bitboard
   U64 attacks = 0ULL;
   
   //piece bitboard
   U64 bitboard = 0ULL ;
    
    
    //set bitboard
    set_bit(bitboard, square);
    
     
    
    //generating knight attacks 17 15 10 6
    if((bitboard>>17) & not_h_file) attacks |= (bitboard>>17);
    if((bitboard>>15) & not_a_file) attacks |= (bitboard>>15);
    if((bitboard>>10) & not_hg_file) attacks |= (bitboard>>10);
    if((bitboard>>6) & not_ab_file) attacks |= (bitboard>>6);
    
    if((bitboard<<17) & not_a_file) attacks |= (bitboard<<17);
    if((bitboard<<15) & not_h_file) attacks |= (bitboard<<15);
    if((bitboard<<10) & not_ab_file) attacks |= (bitboard<<10);
    if((bitboard<<6) & not_hg_file) attacks |= (bitboard<<6);


    
    //return attacks map
    return attacks ;
}


//generate king attacks

U64 mask_king_attacks(int square){
    //result attacks bitboard
   U64 attacks = 0ULL;
   
   //piece bitboard
   U64 bitboard = 0ULL ;
    
    
    //set bitboard
    set_bit(bitboard, square);
    
     
    
    //generating king attacks 17 15 10 6
    if(bitboard >>8) attacks |= (bitboard>>8);
    if((bitboard>>7) & not_a_file) attacks |= (bitboard>>7);
    if((bitboard>>9) & not_h_file) attacks |= (bitboard>>9);
    if((bitboard>>1) & not_h_file) attacks |= (bitboard>>1);
    
    if(bitboard <<8) attacks |= (bitboard<<8);
    if((bitboard<<7) & not_h_file) attacks |= (bitboard<<7);
    if((bitboard<<9) & not_a_file) attacks |= (bitboard<<9);
    if((bitboard<<1) & not_a_file) attacks |= (bitboard<<1);

    
    //return attacks map
    return attacks ;
}
// mask bishop attacks  (Wajeer)
U64 mask_bishop_attacks(int square)
{
    // result attacks bitboard
    U64 attacks = 0ULL;
    
    // init ranks & files
    int r, f;
    
    // init target rank & files
    int tr = square / 8;
    int tf = square % 8;
    
    // mask relevant bishop occupancy bits
    for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));
    
    // return attack map
    return attacks;
}


// mask rook attacks
U64 mask_rook_attacks(int square)
{
    // result attacks bitboard
    U64 attacks = 0ULL;
    
    // init ranks & files
    int r, f;
    
    // init target rank & files
    int tr = square / 8;
    int tf = square % 8;
    
    // mask relevant bishop occupancy bits
    for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
    for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));
    
    // return attack map
    return attacks;
}

// init leaper piece attacks
void init_leaper_attacks(){
    //loop over all 64 squares
    for(int square = 0;square <64;square++){
        //init pawn attacks
        pawn_attacks[white][square]=mask_pawn_attacks(white,square);
        
        pawn_attacks[black][square]=mask_pawn_attacks(black,square);
        //intit knight atacks
        knight_attacks[square] = mask_knight_attacks(square);
        //init king attacks
        king_attacks[square] = mask_king_attacks(square);
    }
}


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
    print the bitboard with rank
    
    for(int rank = 8;rank>=1;rank--)
    printf("\"a%d\", \"b%d\", \"c%d\", \"d%d\", \"e%d\", \"f%d\", \"g%d\", \"h%d\",\n",rank,rank,rank,rank,rank,rank,rank,rank);
    */
    
    init_leaper_attacks();
    for(int i=0;i<64;i++){
        print_bitboard(king_attacks[i]);
    }
    //print_bitboard(mask_king_attacks(a1));
    return 0;
}
