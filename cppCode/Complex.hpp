#pragma once

template <typename T> 
struct Complex 
{ 
private: 
	T re; 
	T im; 
public: 

    Complex(){
    T inre{};
    re = inre;
	T inim{};
    im = inim;         
    };


    Complex(T in, T im){
        
    };
    //assignment Operators
	Complex & operator+=(Complex const & c) 
    { 
	re += c.re;
	im += c.im; 
	return *this; 
	} ;
    Complex & operator-=(Complex const & c) 
    { 
	re -= c.re;
	im -= c.im; 
	return *this; 
    };
    Complex & operator*=(Complex const & c) 
    { 
	re = re*c.re -(im*c.im);
	im = re*c.im-c.re*im; 
	return *this; 
	} ;

    Complex & operator/=(Complex const & c) 
    { 
	re = (re*c.re+im*c.im)/(im*im + c.im*c.im);
	im = (im*c.re-re*c.im)/(im*im+c.im*c.im); 
	return *this; 
	} ;

    Complex Complex::operator+(Complex c) const 
    { 
        return (c += *this);
    };

    Complex Complex::operator-(Complex c) const 
    { 
        return (c -= *this);
    };
    Complex Complex::operator*(Complex c) const 
    { 
        return (c *= *this);
    };
    Complex Complex::operator/(Complex c) const 
    { 
        return (c /= *this);
    };
    //comparison Operator
    bool Complex::operator==(Complex c)  const
    {
        return (re == c.re && im == c.im);
    };

    bool Complex::operator!=(Complex const & c) const { return !(*this == c); }
};