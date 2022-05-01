#ifndef CS540_ARRAY_H
#define CS540_ARRAY_H





#include <iostream>
#include <assert.h>
#include <type_traits>

namespace cs540 {

bool defCtor = false;
bool cpyCtor = false;
bool tempCpyCtor = false;
bool equ = false;
bool tempEqu = false;
bool brack = false;
bool fmbeg = false;
bool fmg = false;
bool fmit = false;
bool all = false;


// EXCEPTION CLASS -------------------------------------------------------------
class OutOfRange: public std::exception {
	public:
		virtual const char* what() const throw(){
			return "OutOfRange Exception - Attempted indexing outside array bounds";
		}
};



template<size_t... Ds> class IndexInfo;

template<size_t D, size_t... Ds>
class IndexInfo<D, Ds...> {
	public:
		static const size_t d = D;		
		static constexpr size_t idx_product = d * IndexInfo<Ds...>::idx_product;
		static constexpr size_t next = IndexInfo<Ds...>::idx_product;
};
	
template<size_t D>
class IndexInfo<D> {
	public:
		static const size_t d = D;	
		static constexpr size_t idx_product = d;
};



// GENERIC DECLARATION ---------------------------------------------------------

template <typename T, size_t... Dims> class Array;


// NON-BASE-CASE CLASS ---------------------------------------------------------

template <typename T, size_t Dim, size_t... Dims> class Array<T, Dim, Dims...> {
public:
	class FirstDimensionMajorIterator;	
		
	using ValueType = T;	
	using InnerType = Array<T, Dims...>;

	

	Array();
	Array(const Array& a);

	template <typename U>		
		Array(const Array<U, Dim, Dims...> & a);
	

	
	Array &operator=(const Array& a);
	template <typename U>
		Array &operator=(const Array<U, Dim, Dims...>& a);
	
	
	InnerType &operator[](size_t idx);	
	const InnerType &operator[](size_t idx) const;	

	FirstDimensionMajorIterator fmbegin();
	FirstDimensionMajorIterator fmend();
	

	ValueType &fmget(size_t idx);

	InnerType OuterArr[Dim];
	size_t dim;
	size_t max_idx;

	
};

// NON-BASE-CASE CLASS DEFINITIONS ---------------------------------------------

// default 1
template <typename T, size_t Dim, size_t... Dims>
Array<T, Dim, Dims...>::
Array() : dim(Dim), max_idx(Dim-1) {//: indexer(Indexer(OuterArr)){
	if(defCtor || all){	
		std::cout << "\t\tArray() 1" << std::endl;
		std::cout << "\tdim " << dim << std::endl;
		std::cout << "\tDIMs " << sizeof...(Dims) << std::endl;
		std::cout << std::endl;
	}
}

// copy 1
template <typename T, size_t Dim, size_t... Dims>
Array<T, Dim, Dims...>::
Array(const Array& a) : OuterArr(a.OuterArr), dim(Dim), max_idx(Dim-1) {
	if(cpyCtor || all){	
		std::cout << "\t\tArray(const Array& a) 1" << std::endl;
	}
	//if(this->dim != a.dim) throw InvalidCpyCtorCall();
}

// templated copy 1
template <typename T, size_t Dim, size_t... Dims>
template <typename U>
Array<T, Dim, Dims...>::	
Array(const Array<U, Dim, Dims...> & a) : dim(Dim), max_idx(Dim-1){
	if(tempCpyCtor || all){		
		std::cout << "\t\tArray(const Array<U, Dims...> & a)" << std::endl;
	}
	for(size_t i = 0; i < a.dim; i++){

		this->OuterArr[i] = a.OuterArr[i];
	}
	
}


// operator= 1
template <typename T, size_t Dim, size_t... Dims>
Array<T, Dim, Dims...> & Array<T, Dim, Dims...>::
operator=(const Array& a){
	if(equ || all){	
		std::cout << "\t\toperator=(const Array& a) 1" << std::endl;
	}
	for(size_t i =0; i < this->dim; i++){
		this->OuterArr[i] = a.OuterArr[i];
	}
	return *this;
}

// templated operator= 1
template <typename T, size_t Dim, size_t... Dims>
template <typename U>
Array<T, Dim, Dims...> & Array<T, Dim, Dims...>::
operator=(const Array<U, Dim, Dims...> & a){
	if(tempEqu || all){
		std::cout << "\t\toperator=(const Array<U, Dim, Dims...> & a) 1" << std::endl;
	}
	for(size_t i = 0; i < this->dim; i++){
		this->OuterArr[i] = a.OuterArr[i];
	}
	return *this;
}

// operator[] 1
template <typename T, size_t Dim, size_t... Dims>
typename Array<T, Dim, Dims...>::InnerType& Array<T, Dim, Dims...>::
operator[](size_t idx){
	if(brack || all){	
		std::cout << "\t\t[] 1" << "----- idx: " << idx << "---- dim: " << dim << std::endl;	
	}					
	if(idx > max_idx) throw OutOfRange(); // only need to check upper bound because size_t is unsigned
	InnerType& tmp = OuterArr[idx];
	return tmp;
}

// operator[] 1 const 
template <typename T, size_t Dim, size_t... Dims>
const typename Array<T, Dim, Dims...>::InnerType& Array<T, Dim, Dims...>::
operator[](size_t idx) const {
	if(brack || all){	
		std::cout << "\t\t[] 1" << "----- idx: " << idx << "---- dim: " << dim << std::endl;	
	}					
	if(idx > max_idx) throw OutOfRange(); // only need to check upper bound because size_t is unsigned
	const InnerType& tmp = OuterArr[idx];
	return tmp;
}

template <typename T, size_t Dim, size_t... Dims>
typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator 
Array<T, Dim, Dims...>::
fmbegin(){
	if(fmbeg || all){
		std::cout << "\t\tfmbegin() 1" << std::endl;
		//std::cout << "\tDim: " << Dim << std::endl;
		//std::cout << "\tthis->dim: " << this->dim << std::endl;
	}	
	
	auto tmp = typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
										FirstDimensionMajorIterator(this, 0);

	return tmp;
}


template <typename T, size_t Dim, size_t... Dims>
typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator 
Array<T, Dim, Dims...>:: 
fmend(){
	if(fmbeg || all){
		std::cout << "\t\tfmend() 1" << std::endl;
		//std::cout << "\tDim: " << Dim << std::endl;
		//std::cout << "\tthis->dim: " << this->dim << std::endl;
	}	
	
	auto tmp = typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
										FirstDimensionMajorIterator(this, IndexInfo<Dim, Dims...>::idx_product);

	return tmp;
}

template <typename T, size_t Dim, size_t... Dims>
typename Array<T, Dim, Dims...>::ValueType& Array<T, Dim, Dims...>::
fmget(size_t idx){
	if(fmg || all){
		std::cout << "\t\tfm(size_t idx) 1" << std::endl;
		std::cout << "\tidx: " << idx << std::endl;
		std::cout << "\tIndexInfo<Dim, Dims...>::next: " << IndexInfo<Dim, Dims...>::next << std::endl;
	}
	size_t idx_i = idx/ IndexInfo<Dim, Dims...>::next;
	if(fmg || all){
		std::cout << "\tidx_i: " << idx_i << std::endl;	
	}
	//size_t idx_j = idx - (idx_i * IndexInfo<Dim, Dims...>::next);
	size_t idx_j = idx % IndexInfo<Dim, Dims...>::next;
	if(fmg || all){
		std::cout << "\tidx_j: " << idx_j << std::endl;	
	}
	return this->OuterArr[idx_i].fmget(idx_j);
}

// NON-BASE FIRST_DIM_ITERS-----------------------------------------------------

template<typename T, size_t Dim, size_t... Dims>
class Array<T, Dim, Dims...>::FirstDimensionMajorIterator {
	friend class Array<T, Dim, Dims...>;	
		
	public:
		using ValueType = T;
		using InnerType = Array<T, Dims...>;
	
		FirstDimensionMajorIterator();
	private:		
		FirstDimensionMajorIterator(Array<T, Dim, Dims...> * a, size_t abs_idx);		
	public:
		FirstDimensionMajorIterator(const FirstDimensionMajorIterator & it);
 		FirstDimensionMajorIterator &operator=(const FirstDimensionMajorIterator & it);
		friend bool operator==(const FirstDimensionMajorIterator &first,
                const FirstDimensionMajorIterator &second){
			return ((first.a == second.a) && (first.absolute_idx == second.absolute_idx));
		}
	
		friend bool operator!=(const FirstDimensionMajorIterator &first,
                const FirstDimensionMajorIterator &second){
			return !(first == second);
		}
	
		FirstDimensionMajorIterator &operator++();
		FirstDimensionMajorIterator operator++(int);
		//T &operator*() const;
		ValueType &operator*() const;

		Array<T, Dim, Dims...> * a;		
		size_t absolute_idx;	
		static const size_t end = IndexInfo<Dim, Dims...>::idx_product;
};

template<typename T, size_t Dim, size_t... Dims>
Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
FirstDimensionMajorIterator() : a(nullptr), absolute_idx(-2){
	if(fmit || all){
		std::cout << "\t\tFirstDimensionMajorIterator() 1" << std::endl;
	}
}

template<typename T, size_t Dim, size_t... Dims>
Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
FirstDimensionMajorIterator(Array<T, Dim, Dims...> * a, size_t abs_idx) : 	a(a), absolute_idx(abs_idx){
	if(fmit || all){
		std::cout << "\t\tFirstDimensionMajorIterator(Array<T, Dim, Dims...> * a, size_t abs_idx) 1" << std::endl;
	}
}

template<typename T, size_t Dim, size_t... Dims>
Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
FirstDimensionMajorIterator(const FirstDimensionMajorIterator & it) : a(it.a), absolute_idx(it.absolute_idx){
	if(fmit || all){
		std::cout << "\t\tFirstDimensionMajorIterator(const FirstDimensionMajorIterator & it) 1" << std::endl;
	}
}

template<typename T, size_t Dim, size_t... Dims>
typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator &
Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
operator=(const FirstDimensionMajorIterator & it) {
	if(fmit || all){
		std::cout << "\t\toperator=(const FirstDimensionMajorIterator & it) 1" << std::endl;
	}	
	this->a = it.a;
	this->absolute_idx = it.absolute_idx;
	return *this;
}

template<typename T, size_t Dim, size_t... Dims>
typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator &
Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
operator++(){
	if(fmit || all){
		std::cout << "\t\tfm& operator++() 1" << std::endl;
	}
	this->absolute_idx++;
	return *this;
}

template<typename T, size_t Dim, size_t... Dims>
typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator 
Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
operator++(int){
	if(fmit || all){
		std::cout << "\t\tfm operator++(int i) 1" << std::endl;
	}
	auto tmp = typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
										FirstDimensionMajorIterator(*this);
	this->absolute_idx++;
	return tmp;
}

template<typename T, size_t Dim, size_t... Dims>
typename Array<T, Dim, Dims...>::FirstDimensionMajorIterator::ValueType& 
Array<T, Dim, Dims...>::FirstDimensionMajorIterator::
operator*() const{
	if(fmit || all){
		std::cout << "\t\toperator*() const 1" << std::endl;
		std::cout << "\tthis->a->dim: " << this->a->dim << std::endl;
	}
	return this->a->fmget(this->absolute_idx);
}


// BASE-CASE CLASS -------------------------------------------------------------

template <typename T, size_t Dim> class Array<T, Dim> {
public:
	
	class FirstDimensionMajorIterator;

	using ValueType = T;	
	
	Array();
	Array(const Array& a);
	template <typename U>
		Array(const Array<U, Dim> & a);

	
	Array &operator=(const Array& a);
	template<typename U>
		Array &operator=(const Array<U, Dim> & a);
	T &operator[](size_t idx);
	const T &operator[](size_t idx) const;

	FirstDimensionMajorIterator fmbegin();
	FirstDimensionMajorIterator fmend();	

	T &fmget(size_t idx);

	ValueType LastArr[Dim];
	size_t dim;
	size_t max_idx;


};

// BASE-CASE CLASS DEFINITIONS--------------------------------------------------

// default 2
template <typename T, size_t Dim> 
Array<T, Dim>::
Array() : dim(Dim), max_idx(Dim-1) { 
	if(defCtor || all){			
		std::cout << "\t\tArray() 2" << std::endl;
		std::cout << "\tdim " << dim << std::endl;
		std::cout << std::endl;
	}

}

// copy 2
template <typename T, size_t Dim> 
Array<T, Dim>::
Array(const Array& a) : dim(Dim), max_idx(Dim-1){
	if(cpyCtor || all){	
		std::cout << "\t\tArray(const Array& a) 2" << std::endl;
	}

	for(size_t i = 0; i < this->dim; i++){
		this->LastArr[i] = a.LastArr[i];
	} 
}

// templated copy 2

template <typename T, size_t Dim>
template <typename U>
Array<T, Dim>::	
Array(const Array<U, Dim> & a) : dim(Dim), max_idx(Dim-1){
	if(tempCpyCtor || all){			
		std::cout << "\t\tArray(const Array<U, Dim> & a) 2" << std::endl;
	}
	for(size_t i = 0; i < this->dim; i++){
		this->LastArr[i] = a.LastArr[i];
	} 
}



// operator= 2
template <typename T, size_t Dim>
Array<T, Dim> & Array<T, Dim>::
operator=(const Array& a){
	if(equ || all){		
		std::cout << "\t\toperator=const Array& a) 2" << std::endl;
	}
	for(size_t i =0; i < this->dim; i++){
		this->LastArr[i] = a.LastArr[i];
	}
	return *this;
}

// templated operator= 2
template <typename T, size_t Dim>
template <typename U>
Array<T, Dim> & Array<T, Dim>::
operator=(const Array<U, Dim> & a){
	if(tempEqu || all){		
		std::cout << "\t\toperator=(const Array<U, Dim> & a) 2" << std::endl;
	}
	for(size_t i =0; i < this->dim; i++){
		this->LastArr[i] = a.LastArr[i];
	}
	return *this;
}

// operator[] 2
template <typename T, size_t Dim>
typename Array<T, Dim>::ValueType & Array<T, Dim>::
operator[](size_t idx){
	if(brack || all){	
		std::cout << "\t\t[] 2" << "----- idx: " << idx << "---- dim: " << dim << std::endl;
	}		
	if(idx > max_idx) throw OutOfRange(); // only need to check upper bound because size_t is unsigned		
	T& tmp = LastArr[idx];		
	return tmp;
}

// operator[] 2 
template <typename T, size_t Dim>
const typename Array<T, Dim>::ValueType & Array<T, Dim>::
operator[](size_t idx) const {
	if(brack || all){	
		std::cout << "\t\t[] 2" << "----- idx: " << idx << "---- dim: " << dim << std::endl;
	}		
	if(idx > max_idx) throw OutOfRange(); // only need to check upper bound because size_t is unsigned		
	const T& tmp = LastArr[idx];		
	return tmp;
}


template <typename T, size_t Dim>
typename Array<T, Dim>::FirstDimensionMajorIterator 
Array<T, Dim>::
fmbegin(){
	if(fmbeg || all){
		std::cout << "\t\tfmbegin() 2" << std::endl;
		//std::cout << "\tDim: " << Dim << std::endl;
		//std::cout << "\tthis->dim: " << this->dim << std::endl;
	}	
	
	auto tmp = typename Array<T, Dim>::FirstDimensionMajorIterator::
										FirstDimensionMajorIterator(this, 0);
	return tmp;
}


template <typename T, size_t Dim>
typename Array<T, Dim>::FirstDimensionMajorIterator 
Array<T, Dim>:: 
fmend(){
	if(fmbeg || all){
		std::cout << "\t\tfmend() 2" << std::endl;
		//std::cout << "\tDim: " << Dim << std::endl;
		//std::cout << "\tthis->dim: " << this->dim << std::endl;
	}	
	
	auto tmp = typename Array<T, Dim>::FirstDimensionMajorIterator::
										FirstDimensionMajorIterator(this, Dim);

	return tmp;
}

template <typename T, size_t Dim>
typename Array<T, Dim>::ValueType & Array<T, Dim>::
fmget(size_t idx){
	if(fmg || all){
		std::cout << "\t\tfm(size_t idx) 2" << std::endl;
	}
	return LastArr[idx];
}

// BASE FIRST_DIM_ITERS-----------------------------------------------------

template<typename T, size_t Dim>
class Array<T, Dim>::FirstDimensionMajorIterator {
	friend class Array<T, Dim>;	
		
	public:
		using ValueType = T;

	
		FirstDimensionMajorIterator();
	private:		
		FirstDimensionMajorIterator(Array<T, Dim> * a, size_t abs_idx);		
	public:
		FirstDimensionMajorIterator(const FirstDimensionMajorIterator & it);
 		FirstDimensionMajorIterator &operator=(const FirstDimensionMajorIterator & it);
		friend bool operator==(const FirstDimensionMajorIterator &first,
                const FirstDimensionMajorIterator &second){
			return ((first.a == second.a) && (first.absolute_idx == second.absolute_idx));
		}
	
		friend bool operator!=(const FirstDimensionMajorIterator &first,
                const FirstDimensionMajorIterator &second){
			return !(first == second);
		}
	
		FirstDimensionMajorIterator &operator++();
		FirstDimensionMajorIterator operator++(int);

		ValueType &operator*() const;

		Array<T, Dim> * a;		
		size_t absolute_idx;	
		static const size_t end = Dim;
};


template<typename T, size_t Dim>
Array<T, Dim>::FirstDimensionMajorIterator::
FirstDimensionMajorIterator() : a(nullptr), absolute_idx(-2){
	if(fmit || all){
		std::cout << "\t\tFirstDimensionMajorIterator() 2" << std::endl;
	}
}

template<typename T, size_t Dim>
Array<T, Dim>::FirstDimensionMajorIterator::
FirstDimensionMajorIterator(Array<T, Dim> * a, size_t abs_idx) : 	a(a), absolute_idx(abs_idx){
	if(fmit || all){
		std::cout << "\t\tFirstDimensionMajorIterator(Array<T, Dim> * a, size_t abs_idx) 2" << std::endl;
	}
}

template<typename T, size_t Dim>
Array<T, Dim>::FirstDimensionMajorIterator::
FirstDimensionMajorIterator(const FirstDimensionMajorIterator & it) : a(it.a), absolute_idx(it.absolute_idx){
	if(fmit || all){
		std::cout << "\t\tFirstDimensionMajorIterator(const FirstDimensionMajorIterator & it) 2" << std::endl;
	}
}

template<typename T, size_t Dim>
typename Array<T, Dim>::FirstDimensionMajorIterator &
Array<T, Dim>::FirstDimensionMajorIterator::
operator=(const FirstDimensionMajorIterator & it) {
	if(fmit || all){
		std::cout << "\t\toperator=(const FirstDimensionMajorIterator & it) 2" << std::endl;
	}	
	this->a = it.a;
	this->absolute_idx = it.absolute_idx;
	return *this;
}

template<typename T, size_t Dim>
typename Array<T, Dim>::FirstDimensionMajorIterator &
Array<T, Dim>::FirstDimensionMajorIterator::
operator++(){
	if(fmit || all){
		std::cout << "\t\tfm& operator++() 2" << std::endl;
	}
	this->absolute_idx++;
	return *this;
}

template<typename T, size_t Dim>
typename Array<T, Dim>::FirstDimensionMajorIterator 
Array<T, Dim>::FirstDimensionMajorIterator::
operator++(int){
	if(fmit || all){
		std::cout << "\t\tfm operator++(int i) 2" << std::endl;
	}
	auto tmp = typename Array<T, Dim>::FirstDimensionMajorIterator::
										FirstDimensionMajorIterator(*this);
	this->absolute_idx++;
	return tmp;
}

template<typename T, size_t Dim>
typename Array<T, Dim>::FirstDimensionMajorIterator::ValueType& 
Array<T, Dim>::FirstDimensionMajorIterator::
operator*() const{
	if(fmit || all){
		std::cout << "\t\toperator*() const 2" << std::endl;
		std::cout << "\tthis->a->dim: " << this->a->dim << std::endl;
	}
	return this->a->fmget(this->absolute_idx);
}



} // end of namespace cs540
#endif
