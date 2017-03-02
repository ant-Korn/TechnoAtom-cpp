//!@file stk_as_mass_realization.h
//!\brief Реализация класса стека на основе массива в отдельном файле.
//! 
//!@author Корнилов Антон, 2017
//!@date 24.02.2017

#ifndef STK_AS_MASS_REALIZATION_H
#define STK_AS_MASS_REALIZATION_H

	template<class T>
	StackAsMass<T>::StackAsMass() : capacity_(0), num_items_(0), data_(nullptr) {}

	template<class T>
	StackAsMass<T>::StackAsMass(size_t capacity) : capacity_(capacity), num_items_(0), data_(new T [capacity]) {}

	template<class T>
	void StackAsMass<T>::swap(StackAsMass & other_stack){
		std::swap(capacity_, other_stack.capacity_);
		std::swap(num_items_, other_stack.num_items_);
		std::swap(data_, other_stack.data_);
	}

	template<class T>
	StackAsMass<T>::StackAsMass(const StackAsMass & other_stack) : capacity_(other_stack.capacity_), num_items_(other_stack.num_items_), data_(new T [other_stack.capacity_]){
		for(size_t i=0; i<num_items_; ++i){
			data_[i] = other_stack.data_[i];
		}
	}

	template<class T>
	StackAsMass<T> & StackAsMass<T>::operator=(StackAsMass other_stack){
		swap(other_stack);
		return *this;
	}

	template<class T>
	StackAsMass<T>::~StackAsMass(){
		delete [] data_;
	}

	template<class T>
	void StackAsMass<T>::dump() const{
		const unsigned num_dashes = 50, num_chars1 = 11, num_chars2 = 7, num_chars3 = 21;
		std::cout << std::setfill('-') << std::setw(num_dashes) << "" << std::setfill(' ') << std::endl;
		std::cout << "   StackAsMass:\n\tnum. of items:" << std::setw(num_chars1) << num_items_ << " capacity:" << std::setw(num_chars2) \
			<< capacity_ << "\n\tdata pointer:" << std::setw(num_chars3);
		if (data_==nullptr){
			std::cout << "nullptr" << std::endl;
		}
		else {
			std::cout << std::hex << data_ << std::dec << " top value: ";
			if(num_items_){
				std::cout << data_[num_items_-1] << std::endl;
			}
			else {
				std::cout << "no item" << std::endl;
			}
		}
		std::cout << "    All nodes:" << std::endl;
		for(size_t i=0; i<num_items_; ++i){
			std::cout << "\t[" << i << "] " << std::hex << (data_+i) << " value: " << std::dec << data_[i] << std::endl;
		}
		std::cout << std::setfill('-') << std::setw(num_dashes) << "" << std::setfill(' ') << std::endl;
	}

	template<class T>
	bool StackAsMass<T>::empty() const{
		return num_items_ == 0;
	}

	template<class T>
	size_t StackAsMass<T>::size() const{
		return num_items_;
	}

	template<class T>
	void StackAsMass<T>::push(const T& element){
		if (num_items_ == capacity_){
			const unsigned capacity_multiplier = 2;
			if (capacity_ == 0){
				++capacity_;
			}
			else{
				capacity_ *= capacity_multiplier;
			}
			T * new_data = new T [capacity_];
			for(size_t i=0; i<num_items_; ++i){
				new_data[i] = data_[i];
			}
			delete [] data_;
			data_ = new_data;
		}
		data_[num_items_++] = element;
	}

	template<class T>
	void StackAsMass<T>::pop(){
		ASSERT_NOT_EMPTY();
		--num_items_;
	}

	template<class T>
	T& StackAsMass<T>::top(){
		ASSERT_NOT_EMPTY();
		return data_[num_items_-1];
	}

;
#endif //STK_AS_MASS_REALIZATION_H