#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

#include <assert.h>
#include <stdlib.h>

namespace qh
{
	template<class T>
	class vector {
	public:
		//ctor
		vector()
			: data_(NULL), size_(0), finish(NULL), end_of_range(NULL)
		{
		}

		explicit vector( size_t n, const T& value = T())
		{
			data_ = new T[n];
			assert(data_);
			for (size_t i = 0; i < n; i++)
			{
				data_[i] = value;
			}
			finish = data_ + n;
			end_of_range = finish;
			size_ = n;
		}

		vector<T>& operator=(const vector<T>& rhs1)
		{
			vector<T>& rhs = const_cast<vector<T>&>(rhs1);
			if (this != &rhs)
			{
				if (NULL != this->data_)
				{
					destroy();
				}

				data_ = new T[rhs.capacity()];
				assert(data_);

				T* pBeginSorce = rhs.begin();
				T* pTemp = data_;
				while(pBeginSorce != rhs.end())
				{
					*pTemp++ = *pBeginSorce++;
				}
				pBeginSorce = NULL;
				pTemp = NULL;

				finish = data_ + rhs.size();
				end_of_range = data_ + rhs.capacity();
				this->size_ = rhs.size();
			}

			return *this;
		}

		//dtor
		~vector()
		{
			destroy();
		}

		//get
		size_t size() const
		{
			return size_;
		}

		// set & get
		T& operator[](size_t index){
			assert(index <= size_);
			return *(begin() + index);
		}

		// set
		inline T* begin() {return data_;}

		inline T* end() {return finish;}

		inline void push_back(const T& element){
			if (finish != end_of_range)
			{
				*finish = element;
				++finish;
			}
			else
			{
				size_t new_size = this->capacity() * 2;
				T* datatemp = new T[new_size];
				T* datatempflag = datatemp;
				T* dataflag = data_;
				while (data_ != this->end())
				{
					*datatemp++ = *data_++;
				}

				data_ = datatempflag;
				delete[] dataflag;
				dataflag = NULL;
				datatemp = NULL;
				datatempflag = NULL;

				finish = data_ + size_;
				*finish = element;
				++finish;

				end_of_range = data_ + new_size;
			}
			++size_;
		}

		inline void pop_back(){
			assert(!this->empty());
			--finish;
			*finish = 0;
			--size_;
		}

		inline void resize(size_t num){
			if (size_ <= num)
			{
				T* new_data = new T[num];
				T* new_data_flag = new_data;
				T* old_data_flag = data_;

				while (data_ != finish)
				{
					*new_data++ = *data_++;
				}

				data_ = new_data_flag;
				delete[] old_data_flag;
				new_data_flag = NULL;
				new_data = NULL;
				old_data_flag = NULL;

				finish = data_ + size_;
				end_of_range = data_ + num;
			}
			else
			{
				T* new_data = new T[num];
				T* new_data_flag = new_data;
				T* old_data_flag = data_;

				for (size_t i = 0; i < num; i++)
				{
					*new_data = *data_;
					new_data++;
					data_++;
				}

				data_ = new_data_flag;
				delete[] old_data_flag;
				new_data_flag = NULL;
				new_data = NULL;
				old_data_flag = NULL;

				finish = data_ + num;
				end_of_range = data_ + num;
				size_ = num;
			}
		}

		inline void reserve(){
			assert(!this->empty());
			T* new_data = new T[size_];
			T* new_data_flag = new_data;
			T* old_data_flag = data_;

			while (data_ != this->end())
			{
				*new_data++ = *data_++;
			}

			data_ = new_data_flag;
			delete[] old_data_flag;
			new_data_flag = NULL;
			new_data = NULL;
			old_data_flag = NULL;

			finish = data_ + size_;
			end_of_range = finish;
		}

		inline void clear(){
			assert(!this->empty());
			while (finish != data_)
			{
				*finish = 0;
				--finish;
				--size_;
			}
		}

		inline size_t capacity() const {
			return (end_of_range - data_);
		}

		inline bool empty(){
			return (begin() == end());
		}

	private:
		void destroy(){
			if (data_)
			{
				delete[] data_;
				data_ = NULL;
				finish = NULL;
				end_of_range = NULL;
				size_ = 0;
			}
		}
	private:
		T*      data_;
		size_t	size_;
		T*		finish;
		T*		end_of_range;
	};
}

#endif


