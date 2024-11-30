#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <functional>

/**
 * @brief percolate down operation of binary heap
 * 
 * @param seqence a vector referrence
 * @param i the location of the node where the operation is performed
 * @param n the scope of operation
 */
template <typename Comparable>
void percolateDown( std::vector<Comparable> & sequence, int i, int n )
{
    int child;
    Comparable tmp = std::move( sequence[i] );

    for( ; (2*i+1) < n; i = child )
    {
        child = 2 * i + 1;
        if( (child != n - 1) && (sequence[child] < sequence[child + 1]))
            ++child;
        if( tmp < sequence[child] )
            sequence[i] = std::move( sequence[child] );
        else
            break;
    }
    sequence[i] = std::move(tmp);
}; 

/**
 * @brief heap sort algorithm
 * 
 * @param seqence a vector referrence
 */
template <typename Comparable>
void heapsort( std::vector<Comparable> & sequence )
{
    int i, j; 

    // build the heap
    for( i = sequence.size()/2 - 1; i >= 0; --i ) 
        percolateDown( sequence, i, sequence.size() );
    
    // deleteMax (N-1) times
    for( j = sequence.size() - 1; j > 0; --j )
    {
        std::swap( sequence[0], sequence[j] ); 
        percolateDown( sequence, 0, j );
    }
}; 

#endif
