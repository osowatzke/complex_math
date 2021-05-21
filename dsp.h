// function determines the bit reversed indices for radix 2 FFT
unsigned int bit_reverse(unsigned int index_in, unsigned int fft_size){
	
	// declare and initialize variable to hold the number of bits required to encode the FFT size
	unsigned int num = 0;
	
	// loop determines the number of bits required to encode the FFT size
	while (fft_size > 0){
		fft_size = fft_size/2;
		++num;
	}
	
	// dynamically allocate array of bits
	unsigned int* bits = (unsigned int*)malloc((num-1)*sizeof(unsigned int));
	
	// declare local variable to be used in for loops
	int i;
	
	// loop initialize bits array in bit-reversed order
	for (i=num-2; i>=0; --i){
		bits[i] = index_in % 2;
		index_in = index_in/2;
	}
	
	// declare and initialize variable to hold output index
	unsigned int index_out = 0;
	
	// base variable to be used in for loop
	unsigned int base = 1;
	
	// for loop determines the resulting bit ordered index
	for (i=0; i<num-1; ++i){
		if (bits[i] == 1){
			index_out += base;
		}
		base *= 2;
	}
	
	// free dynamically allocated array
	free(bits);
	
	// return resulting index
	return index_out;
}

// function takes the fft of an input sequence
complex* fft(complex* in, unsigned int fft_size){
	
	// dynamically allocate output array
	complex* out = (complex*)malloc(fft_size*sizeof(complex));
	
	// assign fft_size to temporary variable
	unsigned int temp = fft_size;
	
	// empty variable holds num of fft stages
	unsigned int num_stages = 0;
	
	// declare variable to be used in for loops
	unsigned int i;
	
	// for loop initializes output array with input in bit reversed order
	for (i=0; i<fft_size; ++i){
		out[i] = in[bit_reverse(i,fft_size)];
	}
	
	// dist determines the distance between any radix-2 butterfly branches
	unsigned int dist = 1;
	
	// step size when incrementing W_N^k = exp(2*pi*k/N)
	unsigned int step = fft_size/2;
	
	// variable k in W_N^k
	unsigned int k;
	
	// variable determines if branch inputs should be scaled
	unsigned int scale_on;
	
	// used in for loop to hold first index in radix-2 FFT butterfly 
	unsigned int index;
	
	// complex variables used when performing FFT
	complex scale, temp1, temp2;
	
	// loop until FFT is complete (i.e. can increase butterfly width no more)
	while (dist<fft_size){
		
		// for loop scales branches inputs by W_N^k when applicable
		for (i=0; i<fft_size; ++i){
			if (i % (2*dist) == 0){
				scale_on = 0;
				scale = exp_c(1,0);
			}	
			else if (i % dist == 0){
				k = 0;
				scale_on = 1;
			}
			if (scale_on == 1){
				scale = exp_c(1,-2*M_PI*k/fft_size);
				k += step;
			}
			out[i] = mult_c(scale,out[i]);
		}
		
		// starting upper butterfly index is always 0
		index = 0;
		
		// for loop determines output of FFT stage
		for (i = 0; i < fft_size/2; ++i){
			
			// temporary complex variables are used to ensure 2nd calculation is unaffected by 1st
			temp1 = add_c(out[index],out[index+dist]);
			temp2 = add_c(out[index], scale_c(-1,out[index+dist]));
			out[index] = temp1;
			out[index+dist] = temp2;
			
			// determine next upper butterfly index
			// if statement skips lower butterfly indices
			++index;
			if ((index % dist == 0) &&  (index % (2*dist) != 0)){
				index = index + dist;
			}
		}
		
		// change distance and step variables for next FFT stage
		dist *= 2;
		step /= 2;
	}	
	
	// return FFT result
	return out;
}
