// function adds two matrices
complex* add_m(complex* A, unsigned int size_A[2], complex* B, unsigned int size_B[2]){
	
	// confirm that array sizes match
	if (size_A[0] != size_B[0] || size_A[1] != size_B[1]){
		printf("Array Sizes do not match.");
		exit(-1);
	}
	
	// if array sizes match add elements in matrix (element-by-element)
	else{
		
		// dynamically allocate resulting array
		complex* result = (complex*)malloc(size_A[0]*size_A[1]*sizeof(complex));
		
		// declare variables to be use in for loops
		unsigned int i, j;
		
		// loop to add matrix elements (element-by-element)
		for (i=0; i<size_A[0]; ++i){
			for(j=0; j<size_A[1]; ++j){
				result[i*size_A[1]+j] = add_c(A[i*size_A[1]+j], B[i*size_A[1]+j]);
			}
		}
		
		// return resulting matrix
		return result;
	}
}

// function subtracts two matrices
complex* sub_m(complex* A, unsigned int size_A[2], complex* B, unsigned int size_B[2]){
	
	// confirm that array sizes match
	if (size_A[0] != size_B[0] || size_A[1] != size_B[1]){
		printf("Array Sizes do not match.");
		exit(-1);
	}
	
	// if array sizes match subtract elements in matrix (element-by-element)
	else{
		
		// dynamically allocate resulting array
		complex* result = (complex*)malloc(size_A[0]*size_A[1]*sizeof(complex));
		
		// declare variables to be use in for loops
		unsigned int i, j;
		
		// loop to add matrix elements (element-by-element)
		for (i=0; i<size_A[0]; ++i){
			for(j=0; j<size_A[1]; ++j){
				result[i*size_A[1]+j] = sub_c(A[i*size_A[1]+j], B[i*size_A[1]+j]);
			}
		}
		
		// return resulting matrix
		return result;
	}
}

// function multiplies two matrices
complex* mult_m(complex* A, unsigned int size_A[2], complex* B, unsigned int size_B[2]){
	
	// confirm that array sizes are consistent for multiplication
	if (size_A[1] != size_B[0]){
		printf("Cannot mutliply. Inner matrix dimensions do not match.");
		exit(-1);
	}
	
	// if array sizes match perform matrix multiplication
	else{
		
		// dynamically allocate resulting matrix
		complex* result = (complex*)malloc(size_A[0]*size_B[1]*sizeof(complex));
		
		// declare variables to be use in for loops
		unsigned int i, j, k;
		
		// loop to add matrix elements (element-by-element)
		for (i=0; i<size_A[0]; ++i){
			for(j=0; j<size_B[1]; ++j){
				
				// initialize real and imaginary parts as zero
				result[i*size_B[1]+j].real = 0;
				result[i*size_B[1]+j].imag = 0;
				
				// loop multiplies row with column
				for(k=0; k<size_A[1]; ++k){
					result[i*size_B[1]+j] = add_c(result[i*size_B[1]+j], mult_c(A[i*size_A[1]+k], B[k*size_B[1] +j]));
				}
			}
		}
		
		// return resulting matrix
		return result;
	}
}

// function outputs prints a formatted matrix
void print_m(complex* A, unsigned int size_A[2]){
	
	// declare variables to be use in for loops
	unsigned int i,j;
	
	// loop to output each matrix element
	for (i=0; i<size_A[0]; ++i){
		for(j=0; j<size_A[1]; ++j){
			print_c(A[i*size_A[1]+j]);
			printf("\t");
		}
		printf("\n");
	}
}

