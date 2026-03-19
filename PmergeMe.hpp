#pragma once

#include <iostream>
#include <ostream>
#include <vector>
#include <deque>

struct Pair
{
    int small;
    int large;
	Pair(int s, int l) : small(s), large(l) {}
};

class PmergeMe {
	private:
		std::vector<int>	_vec;
		std::deque<int>		_deque;
	public:
		PmergeMe(void);
		PmergeMe(const std::string& s);
		PmergeMe(const std::vector<int>& v);
		PmergeMe(const std::deque<int>& d);
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe(void);

		static size_t	jacobsthal(size_t n);
		//	std::vector<int>
		static void		binaryInsert(std::vector<int> &arr, int value, std::vector<int>::iterator end);
		static void		jacobsthalInsert(std::vector<Pair>& pairs, std::vector<int>& large);
		static void		mergeInsertionSort(std::vector<int> &arr);
		//	std::deque<int>
		static void		binaryInsert(std::deque<int> &arr, int value, std::deque<int>::iterator end);
		static void		jacobsthalInsert(std::deque<Pair>& pairs, std::deque<int>& large);
		static void		mergeInsertionSort(std::deque<int> &arr);

		const std::vector<int>&	getVector() const;
		const std::deque<int>&	getDeque() const;

		class InvalidExpression : public std::exception {
            public:
			virtual const char* what() const throw();
        };
};

std::ostream& operator<<(std::ostream& out, const PmergeMe& obj);
