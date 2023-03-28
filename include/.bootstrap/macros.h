#pragma once


// String from arbitrary expression.
#define BLACK_STRING_MACRO( EXPRESSION )	#EXPRESSION
#define BLACK_STRINGIFICATION( EXPRESSION )	BLACK_STRING_MACRO( EXPRESSION )

// Concatenation of various arguments.
#define	BLACK_CONCATENATION( LEFT, RIGHT )	LEFT ## RIGHT
#define BLACK_CONCATENATE( A, B )			BLACK_CONCATENATION( A, B )
