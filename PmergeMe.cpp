#include <exception>
#include <algorithm>	// std::find
#include <iomanip>		// std::setprecision
#include <sstream>		// std::stringstream
#include <sys/time.h>	// gettimeofday

#include "PmergeMe.hpp"

const char* PmergeMe::InvalidExpression::what() const throw() { return ("Error: Invalid sequence."); }

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(const std::string& s) {
	if (s.empty())
		throw InvalidExpression();
	std::stringstream	ss(s);
	int					value;
	while (ss >> value) {
		if (value < 0)
			throw InvalidExpression();
		_vec.push_back(value);
		_deque.push_back(value);
	}
	if (!ss.eof())
        throw InvalidExpression();
}

PmergeMe::PmergeMe(const std::vector<int>& v) : _vec(v) {
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
		_deque.push_back(*it);
	}
}

PmergeMe::PmergeMe(const std::deque<int>& d) : _deque(d) {
	for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); ++it) {
		_vec.push_back(*it);
	}
}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vec = other._vec;
		_deque = other._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe(void) {}

size_t PmergeMe::jacobsthal(size_t n) {
    if (n == 0)
		return (0);
    if (n == 1)
		return (1);
    size_t a = 0;
	size_t b = 1;
	size_t c;
    for (size_t i = 2; i <= n; ++i) {
        c = b + 2 * a;
        a = b;
        b = c;
    }
    return (b);
}

// using std::vector<int>

void	PmergeMe::binaryInsert(std::vector<int> &arr, int value, std::vector<int>::iterator end) {
    std::vector<int>::iterator pos = std::lower_bound(arr.begin(), end, value);
    arr.insert(pos, value);
}

void	PmergeMe::jacobsthalInsert(std::vector<Pair>& pairs, std::vector<int>& large) {
    size_t inserted = 0;
    size_t j = 1;
    while (inserted < pairs.size()) {
        size_t limit = jacobsthal(j);
        size_t next = std::min(limit, pairs.size());
        for (size_t i = next; i > inserted; --i) {
            int smallValue = pairs[i - 1].small;
            int largeValue = pairs[i - 1].large;
            std::vector<int>::iterator bound = std::find(large.begin(), large.end(), largeValue);
            binaryInsert(large, smallValue, bound);
        }
        inserted = next;
        ++j;
    }
}

void	PmergeMe::mergeInsertionSort(std::vector<int>& arr) {
    if (arr.size() <= 1)
        return;
    std::vector<Pair> pairs;
    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] < arr[i + 1]) 
            pairs.push_back(Pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(Pair(arr[i + 1], arr[i]));
    }
    std::vector<int> large;
    for (size_t i = 0; i < pairs.size(); ++i)
        large.push_back(pairs[i].large);
    if (arr.size() % 2)
        large.push_back(arr.back());
    mergeInsertionSort(large);
    jacobsthalInsert(pairs, large);
    arr.swap(large);
}

// using std::deque<int>

void	PmergeMe::binaryInsert(std::deque<int> &arr, int value, std::deque<int>::iterator end) {
    std::deque<int>::iterator pos = std::lower_bound(arr.begin(), end, value);
    arr.insert(pos, value);
}

void	PmergeMe::jacobsthalInsert(std::deque<Pair>& pairs, std::deque<int>& large) {
    size_t inserted = 0;
    size_t j = 1;
    while (inserted < pairs.size()) {
        size_t limit = jacobsthal(j);
        size_t next = std::min(limit, pairs.size());
        for (size_t i = next; i > inserted; --i) {
            int smallValue = pairs[i - 1].small;
            int largeValue = pairs[i - 1].large;
            std::deque<int>::iterator bound = std::find(large.begin(), large.end(), largeValue);
            binaryInsert(large, smallValue, bound);
        }
        inserted = next;
        ++j;
    }
}

void	PmergeMe::mergeInsertionSort(std::deque<int>& arr) {
    if (arr.size() <= 1)
        return;
    std::deque<Pair> pairs;
    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] < arr[i + 1]) 
            pairs.push_back(Pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(Pair(arr[i + 1], arr[i]));
    }
    std::deque<int> large;
    for (size_t i = 0; i < pairs.size(); ++i)
        large.push_back(pairs[i].large);
    if (arr.size() % 2)
        large.push_back(arr.back());
    mergeInsertionSort(large);
    jacobsthalInsert(pairs, large);
    arr.swap(large);
}

const std::vector<int>&	PmergeMe::getVector() const { return (_vec); }
const std::deque<int>&	PmergeMe::getDeque() const { return (_deque); }

std::ostream& operator<<(std::ostream& out, const PmergeMe& obj) {
	std::vector<int>	vec = obj.getVector();
	std::deque<int>		deq = obj.getDeque();
	if (vec.empty()) {
		out << "Invalid sequence.";
		return (out);
	}
	out << "Before: ";
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		if (it != vec.begin()) {
			out << " ";
		}
		out << *it;
	}
	out << "\nAfter: ";
	timeval	start, end;
	gettimeofday(&start, NULL);
	PmergeMe::mergeInsertionSort(vec);
	gettimeofday(&end, NULL);
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		if (it != vec.begin()) {
			out << " ";
		}
		out << *it;
	}
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
	out << std::fixed << std::setprecision(6);
	out << "\nTime to process a range of " << vec.size()
		<< " elements with std::vector : " << elapsed << " s";
	gettimeofday(&start, NULL);
	PmergeMe::mergeInsertionSort(deq);
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
	out << "\nTime to process a range of " << deq.size()
		<< " elements with std::deque : " << elapsed << " s";
	return (out);
}
