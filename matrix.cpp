//
//  matrix.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 16/01/2019.
//

#include "matrix.hpp"

void MatrixTests()
{
	{
		std::cout << "\n=== Test #1 ===\n";
		Matrix mtxA;
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod == Matrix());
	}
	
	{
		std::cout << "\n=== Test #2 ===\n";
		Matrix mtxA;
		mtxA.AddUniformScale(3);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod == Matrix());
	}
	
	{
		std::cout << "\n=== Test #3 ===\n";
		Matrix mtxA;
		mtxA.AddNonUniformScale(2, 3, 4);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod == Matrix());
	}
	
	{
		std::cout << "\n=== Test #4 ===\n";
		Matrix mtxA;
		mtxA.SetElements(16, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		assert (mtxA.Determinant() == 0);
	}
	
	{
		std::cout << "\n=== Test #5 ===\n";
		Matrix mtxA;
		mtxA.AddRotationX(45);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod.Compare(Matrix(), 1e-15));
	}
	
	{
		std::cout << "\n=== Test #6 ===\n";
		Matrix mtxA;
		mtxA.AddRotationY(45);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod.Compare(Matrix(), 1e-15));
	}
	
	{
		std::cout << "\n=== Test #7 ===\n";
		Matrix mtxA;
		mtxA.AddRotationZ(45);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod.Compare(Matrix(), 1e-15));
	}
	
	{
		std::cout << "\n=== Test #8 ===\n";
		Matrix mtxA;
		mtxA.AddRotationX(45);
		mtxA.AddRotationY(45);
		mtxA.AddRotationZ(45);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod.Compare(Matrix(), 1e-15));
	}
	
	{
		std::cout << "\n=== Test #9 ===\n";
		Matrix mtxA;
		mtxA.AddRotationX(60);
		mtxA.AddRotationY(45);
		mtxA.AddRotationZ(30);
		mtxA.AddOffset(0.5, 0.7, 0.9);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod.Compare(Matrix(), 1e-15));
	}
	
	{
		std::cout << "\n=== Test #10 ===\n";
		Matrix mtxA;
		mtxA.AddRotationX(60);
		mtxA.AddRotationY(45);
		mtxA.AddRotationZ(30);
		mtxA.AddOffset(0.5, 0.7, 0.9);
		mtxA.AddNonUniformScale(0.5, 0.25, 0.125);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod.Compare(Matrix(), 1e-15));
	}
	
	{
		std::cout << "\n=== Test #11 ===\n";
		Matrix mtxA;
		mtxA.AddRotationX(60);
		mtxA.AddRotationY(45);
		mtxA.AddRotationZ(30);
		mtxA.AddOffset(0.5, 0.7, 0.9);
		std::cout << "mtxA: \n" << mtxA;
		Matrix mtxB = mtxA.GetInverse();
		std::cout << "mtxB: \n" << mtxB;
		Matrix prod = mtxA * mtxB;
		assert(prod.Compare(Matrix(), 1e-15));
	}
}
