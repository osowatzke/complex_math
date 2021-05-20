// struct defines complex type
typedef struct
{
	double real;
	double imag;
} complex;

// function finds the absolute value of a complex number
double abs_c(complex num){
	return sqrt(num.real*num.real + num.imag*num.imag);
}

// function finds the angle of a complex number in radians
double angle_c(complex num){
	return atan2(num.imag, num.real);
}

// function determines real and imaginary parts of complex exponential
complex exp_c(double mag, double angle){
	complex result;
	result.real = mag*cos(angle);
	result.imag = mag*sin(angle);
	return result;
}

// function scale a complex number
complex scale_c(double scalar, complex num){
	complex result;
	result.real = scalar*num.real;
	result.imag = scalar*num.imag;
	return result;
}

// function prints complex number
void print_c(complex num){
	if (num.imag >= 0){
		printf("%.4f + j%.4f", num.real, num.imag);
	}
	else {
		printf("%.4f - j%.4f", num.real, abs(num.imag));
	}
}

// function adds two complex numbers
complex add_c(complex num1, complex num2){
	complex result;
	result.real = num1.real + num2.real;
	result.imag = num1.imag + num2.imag;
	return result;
}

// function subtracts one complex number from another complex number
complex sub_c(complex num1, complex num2){
	complex result;
	result.real = num1.real - num2.real;
	result.imag = num1.imag - num2.imag;
	return result;
}

// function multiplies two complex numbers
complex mult_c(complex num1, complex num2){
	double mag = abs_c(num1) * abs_c(num2);
	double angle = angle_c(num1) + angle_c(num2);
	complex result;
	result = exp_c(mag,angle);
	return result;
}

// function divides two complex numbers
complex div_c(complex num1, complex num2){
	double mag = abs_c(num1) / abs_c(num2);
	double angle = angle_c(num1) - angle_c(num2);
	complex result;
	result = exp_c(mag,angle);
	return result;
}

